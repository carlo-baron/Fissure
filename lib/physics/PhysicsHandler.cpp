#include "PhysicsHandler.hpp"
#include <raylib.h>
#include <raymath.h>

void PhysicsHandler(vector<GameObject *> gameObjects){
	for(int i = 0; i < (int)gameObjects.size(); i++){
		GameObject* object = gameObjects[i];
		Rigidbody* rb = object->GetRigidbody();
		if(!rb || rb->GetType() == RigidbodyType::Static) continue;
		IGameTransform* transform = object->GetGameTransform();
		
		transform->SetPosition(Vector2Add(transform->GetPosition(), Vector2Scale(rb->GetVelocity(), GetFrameTime())));
	}}
