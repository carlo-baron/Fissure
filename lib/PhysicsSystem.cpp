#include "PhysicsSystem.hpp"
#include "CollisionSystem.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <tuple>

PhysicsSystem::PhysicsSystem(vector<GameObject *> gameObjects, CollisionSystem* collisionSystem){
	this->gameObjects = gameObjects;
	this->collisionSystem = collisionSystem;

	this->collisionSystem->AddListener(this);

	for(GameObject* gameObject : gameObjects){
		ICollider* collider = gameObject->GetComponent<ICollider>();
		if(collider){
			Rigidbody* rb = gameObject->GetComponent<Rigidbody>();
			if(rb){
				this->collRbMap.insert({collider, rb});
			}
		}
	}
}

void PhysicsSystem::PhysicsHandler(){
	for(int i = 0; i < (int)gameObjects.size(); i++){
		GameObject* object = gameObjects[i];
		Rigidbody* rb = object->GetComponent<Rigidbody>();

		if(!rb || rb->GetType() == RigidbodyType::Static || rb->GetType() == RigidbodyType::Kinematic) continue;

		IGameTransform* transform = object->GetComponent<IGameTransform>();

		// gravity now accumulate
		if(rb->GetGravity() > 0){
			rb->SetVelocity({ 
					rb->GetVelocity().x,
					rb->GetVelocity().y + this->gravityAcceleration * rb->GetGravity() * GetFrameTime()});

		}

		transform->SetPosition(Vector2Add(transform->GetPosition(), rb->GetVelocity()));
	}
}

void PhysicsSystem::OnCollisionSystemEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) {
	colliderA->OnCollisionEnter(colliderB);
	colliderB->OnCollisionEnter(colliderA);

	auto itA = collRbMap.find(colliderA);
	auto itB = collRbMap.find(colliderB);
	bool hasA = itA != collRbMap.end() && itA->second != nullptr;
	bool hasB = itB != collRbMap.end() && itB->second != nullptr;
	if(!hasA && !hasB) return;

	Rigidbody* rbA = hasA ? itA->second : nullptr;
	Rigidbody* rbB = hasB ? itB->second : nullptr;
	RigidbodyType typeA = hasA ? rbA->GetType() : RigidbodyType::Static;
	RigidbodyType typeB = hasB ? rbB->GetType() : RigidbodyType::Static;
	bool movableA = hasA && typeA == RigidbodyType::Dynamic;
	bool movableB = hasB && typeB == RigidbodyType::Dynamic;

	CancelPenetratingVelocity(colliderA, colliderB, rbA, rbB, mtv, movableA, movableB);
	CorrectOverlap(colliderA, colliderB, mtv, movableA, movableB);

	if(!hasA || !hasB) return;

	ResolveMomentum(rbA, rbB, typeA, typeB);
}

void PhysicsSystem::CancelPenetratingVelocity(ICollider* colliderA, ICollider* colliderB, Rigidbody* rbA, Rigidbody* rbB, Vector2 mtv, bool movableA, bool movableB){
	if(movableA && !movableB){
		if(Vector2LengthSqr(mtv) > 0){
			Vector2 normal = Vector2Normalize(mtv);
			float into = Vector2DotProduct(rbA->GetVelocity(), normal);
			if(into > 0){
				rbA->SetVelocity(Vector2Subtract(rbA->GetVelocity(), Vector2Scale(normal, into)));
			}
		}
	}else if(movableB && !movableA){
		Vector2 negSeparation = Vector2Negate(mtv);
		if(Vector2LengthSqr(negSeparation) > 0){
			Vector2 normal = Vector2Normalize(negSeparation);
			float into = Vector2DotProduct(rbB->GetVelocity(), normal);
			if(into > 0){
				rbB->SetVelocity(Vector2Subtract(rbB->GetVelocity(), Vector2Scale(normal, into)));
			}
		}
	}
}

void PhysicsSystem::CorrectOverlap(ICollider* colliderA, ICollider* colliderB, Vector2 mtv, bool movableA, bool movableB){
	if(movableA && movableB){
		Vector2 half = Vector2Scale(mtv, 0.5f);
		colliderA->SetPosition(Vector2Subtract(colliderA->GetPosition(), half));
		colliderB->SetPosition(Vector2Add(colliderB->GetPosition(), half));
	}else if(movableA){
		colliderA->SetPosition(Vector2Subtract(colliderA->GetPosition(), mtv));
	}else if(movableB){
		colliderB->SetPosition(Vector2Add(colliderB->GetPosition(), mtv));
	}
}

void PhysicsSystem::ResolveMomentum(Rigidbody* rbA, Rigidbody* rbB, RigidbodyType typeA, RigidbodyType typeB){
	Vector2 velocity1, velocity2;
	tie(velocity1, velocity2) = ResolveCollision(rbA, rbB);

	if(typeA == RigidbodyType::Dynamic){
		rbA->SetVelocity(velocity1);
	}
	if(typeB == RigidbodyType::Dynamic){
		rbB->SetVelocity(velocity2);
	}
}

tuple<Vector2, Vector2> PhysicsSystem::ResolveCollision(Rigidbody* rb1, Rigidbody* rb2){
	float e = (rb1->GetBounciness() + rb2->GetBounciness()) / 2;

	float v1fX =
		(rb1->GetMass() * rb1->GetVelocity().x
		 + rb2->GetMass() * rb2->GetVelocity().x
		 - rb2->GetMass() * e * (rb1->GetVelocity().x - rb2->GetVelocity().x))
		/ (rb1->GetMass() + rb2->GetMass());
	float v1fY =
		(rb1->GetMass() * rb1->GetVelocity().y
		 + rb2->GetMass() * rb2->GetVelocity().y
		 - rb2->GetMass() * e * (rb1->GetVelocity().y - rb2->GetVelocity().y))
		/ (rb1->GetMass() + rb2->GetMass());

	float v2fX = 
		(rb1->GetMass() * rb1->GetVelocity().x 
		 + rb2->GetMass() * rb2->GetVelocity().x 
		 + rb1->GetMass() * e * (rb1->GetVelocity().x - rb2->GetVelocity().x))
		/ (rb1->GetMass() + rb2->GetMass());
	float v2fY = 
		(rb1->GetMass() * rb1->GetVelocity().y 
		 + rb2->GetMass() * rb2->GetVelocity().y 
		 + rb1->GetMass() * e * (rb1->GetVelocity().y - rb2->GetVelocity().y))
		/ (rb1->GetMass() + rb2->GetMass());

	return {Vector2{v1fX, v1fY}, Vector2{v2fX, v2fY}};
}

void PhysicsSystem::OnCollisionSystemExit(ICollider* colliderA, ICollider* colliderB) {
	colliderA->OnCollisionExit(colliderB);
	colliderB->OnCollisionExit(colliderA);
}
