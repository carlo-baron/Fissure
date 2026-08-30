#pragma once

class ICollider;

/**
 * @brief Observer of collision events, registered on an ICollider.
 *
 * Implementors register via ICollider::AddListener(). Both
 * CollisionSystem-driven responses (PhysicsSystem resolving momentum)
 * and GameObject-level reactions (custom behaviours changing colors,
 * spawning effects, ...) are implemented as collision listeners.
 */
class ICollisionListener{
	public:
		/**
		 * @brief Called when the collider this listener is registered on starts colliding with another.
		 * @param self The collider that fired the event — the one this listener was added to.
		 * @param other The collider it collided with.
		 */
		virtual void OnCollisionEnter(ICollider* self, ICollider* other) const = 0;
		/**
		 * @brief Called when the collider this listener is registered on stops colliding with another.
		 * @param self The collider that fired the event — the one this listener was added to.
		 * @param other The collider it collided with.
		 */
		virtual void OnCollisionExit(ICollider* self, ICollider* other) const = 0;

		virtual ~ICollisionListener(){};
};
