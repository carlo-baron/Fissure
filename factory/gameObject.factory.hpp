#pragma once

#include "raylib.h"
#include "../components/gameObject/GameObject.hpp"

class GameObjectFactory{
	public:
		GameObjectFactory();

		/**
		 * @brief Creates a GameObject with Circle Renderer and Circle Collider
		 *
		 * @param position The initial position of the GameObject
		 * @param radius The radius inital radius of Circle Renderer and Circle Collider
		 * @return A Pre-made GameObject with CircleRenderer and Circle Collider
		 */
		GameObject CircleObject(Vector2 position, float radius);
};

