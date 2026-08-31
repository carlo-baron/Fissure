#include "PhysicsSystem.hpp"
#include "CollisionSystem.hpp"
#include <raylib.h>
#include <raymath.h>

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

		if(rb->GetGravity() > 0){
			rb->SetVelocity({ rb->GetVelocity().x, this->gravityAcceleration * rb->GetGravity() * GetFrameTime()});
		}

		transform->SetPosition(Vector2Add(transform->GetPosition(), rb->GetVelocity()));
	}
}

float PhysicsSystem::ResolveInelasticCollision(float mass1, float velocity1, float mass2, float velocity2) const {
	float numerator = (mass1 * velocity1) + (mass2 * velocity2);
	float denominator = mass1 + mass2;

	return numerator / denominator;
}

void PhysicsSystem::OnCollisionSystemEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) const {
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

	ShapeType shapeA = colliderA->GetShapeType();
	ShapeType shapeB = colliderB->GetShapeType();
	bool pointsTowardColliderA =
		(shapeA == ShapeType::Circle && shapeB == ShapeType::Rectangle) ||
		(shapeA == ShapeType::Rectangle && shapeB == ShapeType::Rectangle);
	Vector2 separation = pointsTowardColliderA ? Vector2Negate(mtv) : mtv;

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

	float finalVelocityX = ResolveInelasticCollision(rbA->GetMass(), rbA->GetVelocity().x, rbB->GetMass(), rbB->GetVelocity().x);
	float finalVelocityY = ResolveInelasticCollision(rbA->GetMass(), rbA->GetVelocity().y, rbB->GetMass(), rbB->GetVelocity().y);

	if(typeA == RigidbodyType::Dynamic){
		rbA->SetVelocity({finalVelocityX, finalVelocityY});
	}
	if(typeB == RigidbodyType::Dynamic){
		rbB->SetVelocity({finalVelocityX, finalVelocityY});
	}
}

void PhysicsSystem::OnCollisionSystemExit(ICollider* colliderA, ICollider* colliderB) const {
	colliderA->OnCollisionExit(colliderB);
	colliderB->OnCollisionExit(colliderA);
}
