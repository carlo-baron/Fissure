#include "GameWorld.hpp"
#include <algorithm>

GameWorld::GameWorld() : 
	collisionSystem(gameObjects),
	physicsSystem(gameObjects, &collisionSystem)
{
	
}

void GameWorld::Update(){
	collisionSystem.CollisionHandler();
	physicsSystem.PhysicsHandler();

	for(auto& obj : gameObjects){
		obj->Draw();
		obj->Update();	
	}

	for(auto& obj : gameObjects){
		if(obj->IsMarkedForDestruction()){
			ICollider* collider = obj->GetComponent<ICollider>();
			if(collider){
				physicsSystem.RemoveTrackedCollider(collider);
				collisionSystem.RemoveTrackedCollider(collider);
			}
		}
	}

	gameObjects.erase(
			std::remove_if(gameObjects.begin(), gameObjects.end(),
				[](const unique_ptr<GameObject>& obj){ return obj->IsMarkedForDestruction(); }),
			gameObjects.end()
			);

}

void GameWorld::AddObject(unique_ptr<GameObject> gameObject){
	physicsSystem.RegisterObject(gameObject.get());
	gameObjects.push_back(std::move(gameObject));
}
