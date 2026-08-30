#pragma once

#include "raylib.h"

/**
 * @brief Position, rotation and scale of a GameObject.
 *
 * Renderers and colliders hold an IGameTransform* and read/write their
 * position through it, so one transform per object is shared by every
 * component that needs it instead of duplicating positional state.
 */
class IGameTransform {
	public:
		/**
		 * @brief World position of the object.
		 */
		virtual Vector2 GetPosition() const = 0;
		/**
		 * @brief Moves the object to the given position.
		 * @param position The new position.
		 */
		virtual void SetPosition(Vector2 position) = 0;

		/**
		 * @brief Rotation of the object, stored as a Vector2.
		 */
		virtual Vector2 GetRotation() const = 0;
		/**
		 * @brief Sets the rotation.
		 * @param rotation The new rotation.
		 */
		virtual void SetRotation(Vector2 rotation) = 0;

		/**
		 * @brief Uniform scale multiplier applied when drawing.
		 */
		virtual float GetScale() const = 0;
		/**
		 * @brief Sets the scale multiplier.
		 * @param scale The new scale.
		 */
		virtual void SetScale(float scale) = 0;

		virtual ~IGameTransform() {}
};
