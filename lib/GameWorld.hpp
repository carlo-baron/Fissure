#pragma once

#include "CollisionSystem.hpp"
#include "GameObject.hpp"
#include "PhysicsSystem.hpp"
#include <memory>

class GameWorld{
	private:
		vector<unique_ptr<GameObject>> gameObjects;
		CollisionSystem collisionSystem;
		PhysicsSystem physicsSystem;

	public:
		GameWorld();
		void Update();

		void AddObject(unique_ptr<GameObject> gameObject);
};
