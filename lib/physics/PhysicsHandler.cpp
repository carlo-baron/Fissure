#include "PhysicsHandler.hpp"
#include <raylib.h>
#include <raymath.h>

PhysicsSystem::PhysicsSystem(vector<GameObject *> gameObjects){
	this->gameObjects = gameObjects;

	for(GameObject* gameObject : gameObjects){
		ICollider* collider = gameObject->GetComponent<ICollider>();
		if(collider){
			collider->AddListener(this);
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

		if(!rb || rb->GetType() == RigidbodyType::Static) continue;

		IGameTransform* transform = object->GetComponent<IGameTransform>();

		if(rb->GetGravity() > 0){
			rb->SetVelocity({ rb->GetVelocity().x, this->gravityAcceleration * rb->GetGravity() * GetFrameTime()});
		}

		transform->SetPosition(Vector2Add(transform->GetPosition(), rb->GetVelocity()));
	}
}

void PhysicsSystem::OnCollisionEnter(ICollider* self, ICollider* other) const {
	auto itA = collRbMap.find(self);
	auto itB = collRbMap.find(other);
	if(itA == collRbMap.end() || itB == collRbMap.end()) return;

	// impulse-momentum
	Rigidbody* rbA = collRbMap.at(self);
	Rigidbody* rbB = collRbMap.at(other);

	if(!rbA || !rbB) return;

	float finalVelocityX = ResolveInelasticCollision(rbA->GetMass(), rbA->GetVelocity().x, rbB->GetMass(), rbB->GetVelocity().x);
	float finalVelocityY = ResolveInelasticCollision(rbA->GetMass(), rbA->GetVelocity().y, rbB->GetMass(), rbB->GetVelocity().y);

	rbA->SetVelocity({finalVelocityX, finalVelocityY});
	rbB->SetVelocity({finalVelocityX, finalVelocityY});
}

void PhysicsSystem::OnCollisionExit(ICollider* self, ICollider* other) const {

}

float PhysicsSystem::ResolveInelasticCollision(float mass1, float velocity1, float mass2, float velocity2) const {
	float numerator = (mass1 * velocity1) + (mass2 * velocity2);
	float denominator = mass1 + mass2;

	return numerator / denominator;
}
