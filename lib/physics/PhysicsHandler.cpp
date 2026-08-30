#include "PhysicsHandler.hpp"
#include <raylib.h>
#include <raymath.h>

PhysicsSystem::PhysicsSystem(vector<GameObject *> gameObjects){
	this->gameObjects = gameObjects;

	for(GameObject* gameObject : gameObjects){
		ICollider* collider = gameObject->GetCollider();
		if(collider){
			collider->AddListener(this);
			Rigidbody* rb = gameObject->GetRigidbody();
			this->collRbMap.insert({collider, rb});
		}
	}
}

void PhysicsSystem::PhysicsHandler(){
	for(int i = 0; i < (int)gameObjects.size(); i++){
		GameObject* object = gameObjects[i];
		Rigidbody* rb = object->GetRigidbody();
		if(!rb || rb->GetType() == RigidbodyType::Static) continue;
		IGameTransform* transform = object->GetGameTransform();

		// gravity
		rb->SetVelocity({ rb->GetVelocity().x, this->gravityAcceleration * rb->GetGravity() * GetFrameTime()});

		transform->SetPosition(Vector2Add(transform->GetPosition(), rb->GetVelocity()));
	}
}

void PhysicsSystem::OnCollisionEnter(ICollider* self, ICollider* other) const {
	// impulse-momentum
	Rigidbody* rbA = collRbMap.at(self);
	Rigidbody* rbB = collRbMap.at(other);
}

void PhysicsSystem::OnCollisionExit(ICollider* self, ICollider* other) const {

}
