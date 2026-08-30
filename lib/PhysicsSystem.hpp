#pragma once
#include "../components/gameObject/GameObject.hpp"
#include <unordered_map>
#include <vector>

/**
 * @brief Integrates motion (gravity + velocity) and resolves collision momentum.
 *
 * PhysicsSystem is both a system and an ICollisionListener: at
 * construction it registers itself on every collider, and whenever
 * CollisionSystem fires a collision-enter event it rewrites the
 * velocities of the Dynamic bodies involved using perfectly inelastic
 * momentum resolution. Integration is a separate per-frame pass in
 * PhysicsHandler().
 */
class PhysicsSystem : public ICollisionListener{
	private:
		vector<GameObject*> gameObjects;
		unordered_map<ICollider*, Rigidbody*> collRbMap;
		float gravityAcceleration = 150;

		/**
		 * @brief Final velocity of a perfectly inelastic collision along one axis.
		 *
		 * Momentum is conserved — m1*v1 + m2*v2 — while both bodies end
		 * up moving together at the same velocity, hence the division by
		 * the total mass.
		 * @param mass1 Mass of the first body.
		 * @param velocity1 Velocity of the first body along this axis.
		 * @param mass2 Mass of the second body.
		 * @param velocity2 Velocity of the second body along this axis.
		 * @return The shared post-collision velocity.
		 */
		float ResolveInelasticCollision(float mass1, float velocity1, float mass2, float velocity2) const;

	public:
		/**
		 * @brief Registers the system as a collision listener and maps colliders to rigidbodies.
		 *
		 * Only colliders belonging to objects that also have a Rigidbody
		 * appear in the map — collisions involving objects without one
		 * simply produce no momentum change.
		 * @param gameObject The objects to simulate. Non-owning.
		 */
		PhysicsSystem(vector<GameObject*> gameObject);

		/**
		 * @brief Advances the simulation by one frame.
		 *
		 * For every Dynamic body: applies gravity by setting its vertical
		 * velocity to gravityAcceleration * the body's gravity multiplier
		 * * frame time, then integrates its position by its velocity.
		 * Objects without a Rigidbody, and Static/Kinematic bodies (which
		 * are moved only by gameplay code or not at all), are skipped
		 * entirely.
		 */
		void PhysicsHandler();

		/**
		 * @brief Resolves the momentum exchange of a collision (called through the listener interface).
		 *
		 * Per axis, computes the shared post-collision velocity of a
		 * perfectly inelastic collision — (m1*v1 + m2*v2) / (m1 + m2),
		 * conserving momentum while equalizing both velocities — and
		 * applies it to whichever of the two bodies are Dynamic.
		 * Static/Kinematic bodies keep their velocity, so they act as
		 * immovable for the exchange.
		 *
		 * @param self The collider of the first body involved.
		 * @param other The collider of the second body involved.
		 */
		void OnCollisionEnter(ICollider* self, ICollider* other) const override;
		/**
		 * @brief No-op: momentum is exchanged on enter, so collision exit needs no physics handling.
		 */
		void OnCollisionExit(ICollider* self, ICollider* other) const override;
};
