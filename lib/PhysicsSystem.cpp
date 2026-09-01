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

// why is physics hard, i should've listened to my teacher
void PhysicsSystem::OnCollisionSystemEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) {
	cout << "Called" << endl;
	colliderA->OnCollisionEnter(colliderB);
	colliderB->OnCollisionEnter(colliderA);

	auto itA = collRbMap.find(colliderA);
	auto itB = collRbMap.find(colliderB);

	// checks if these colliders has rigidbody
	bool hasA = itA != collRbMap.end() && itA->second != nullptr;
	bool hasB = itB != collRbMap.end() && itB->second != nullptr;
	if(!hasA && !hasB) return;

	Rigidbody* rbA = hasA ? itA->second : nullptr;
	Rigidbody* rbB = hasB ? itB->second : nullptr;
	RigidbodyType typeA = hasA ? rbA->GetType() : RigidbodyType::Static;
	RigidbodyType typeB = hasB ? rbB->GetType() : RigidbodyType::Static;

	// only dynamic rb's can be moved hence the name 
	bool movableA = hasA && typeA == RigidbodyType::Dynamic;
	bool movableB = hasB && typeB == RigidbodyType::Dynamic;

	// temp solution since i have inconsistent mtv 
	// TODO: fix mtv calculation in collision system to make it always point to collider A
	ShapeType shapeA = colliderA->GetShapeType();
	ShapeType shapeB = colliderB->GetShapeType();
	bool pointsTowardColliderA =
		(shapeA == ShapeType::Circle && shapeB == ShapeType::Rectangle) ||
		(shapeA == ShapeType::Rectangle && shapeB == ShapeType::Rectangle);
	Vector2 separation = pointsTowardColliderA ? Vector2Negate(mtv) : mtv;

	// normal force thing
	if(movableA && !movableB){
		if(Vector2LengthSqr(separation) > 0){
			Vector2 normal = Vector2Normalize(separation);
			float into = Vector2DotProduct(rbA->GetVelocity(), normal);
			if(into > 0){
				rbA->SetVelocity(Vector2Subtract(rbA->GetVelocity(), Vector2Scale(normal, into)));
			}
	}
	}else if(movableB && !movableA){
		Vector2 negSeparation = Vector2Negate(separation);
		if(Vector2LengthSqr(negSeparation) > 0){
			Vector2 normal = Vector2Normalize(negSeparation);
			float into = Vector2DotProduct(rbB->GetVelocity(), normal);
			if(into > 0){
				rbB->SetVelocity(Vector2Subtract(rbB->GetVelocity(), Vector2Scale(normal, into)));
			}
		}
	}

	// position correction mtv
	if(movableA && movableB){
		Vector2 half = Vector2Scale(separation, 0.5f);
		colliderA->SetPosition(Vector2Subtract(colliderA->GetPosition(), half));
		colliderB->SetPosition(Vector2Add(colliderB->GetPosition(), half));
	}else if(movableA){
		colliderA->SetPosition(Vector2Subtract(colliderA->GetPosition(), separation));
	}else if(movableB){
		colliderB->SetPosition(Vector2Add(colliderB->GetPosition(), separation));
	}

	if(!hasA || !hasB) return;

	// conservation of momentum
	Vector2 velocity1, velocity2;
	tie(velocity1, velocity2) = ResolveCollision(rbA, rbB);

	cout << velocity1.x << ", " << velocity2.x << endl;

	if(typeA == RigidbodyType::Dynamic){
		rbA->SetVelocity(velocity1);
	}
	if(typeB == RigidbodyType::Dynamic){
		rbB->SetVelocity(velocity2);
	}
}

tuple<Vector2, Vector2> PhysicsSystem::ResolveCollision(Rigidbody* rb1, Rigidbody* rb2){
	float e = 0; // TODO: bounciness - add to rb and average out 

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
