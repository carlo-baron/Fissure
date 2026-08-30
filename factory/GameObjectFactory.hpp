#pragma once

#include "raylib.h"
#include "../components/gameObject/GameObject.hpp"

/**
 * @brief Builds ready-to-use GameObjects out of matching components.
 *
 * Each factory method wires a GameTransform, renderer, collider and
 * Rigidbody together so callers don't have to assemble components by
 * hand (see main.cpp).
 */
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

		/**
		 * @brief Creates a GameObject with Rectangle Renderer and Rectangle Collider
		 *
		 * @param position The initial position of the GameObject
		 * @param width The width of Rectangle Renderer and Rectangle Collider
		 * @param height The height of Rectangle Renderer and Rectangle Collider
		 * @return A Pre-made GameObject with RectangleRenderer and Rectangle Collider
		 */
		GameObject RectangleObject(Vector2 position, float width, float height);
};

