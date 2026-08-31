#pragma once
#include "../components/gameObject/GameObject.hpp"
#include "CollisionSystem.hpp"
#include "ICollisionSystemListener.hpp"
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
class PhysicsSystem : public ICollisionSystemListener{
	private:
		vector<GameObject*> gameObjects;
		unordered_map<ICollider*, Rigidbody*> collRbMap;
		float gravityAcceleration = 150;
		CollisionSystem* collisionSystem;

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
		PhysicsSystem(vector<GameObject*> gameObject, CollisionSystem* collisionSystem);

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

		void OnCollisionSystemEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) const override;
		void OnCollisionSystemExit(ICollider* colliderA, ICollider* colliderB) const override;
};
