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
		float gravityAcceleration = 5;
		CollisionSystem* collisionSystem;

		tuple<Vector2, Vector2> ResolveCollision(Rigidbody* rb1, Rigidbody* rb2);
		void CancelPenetratingVelocity(ICollider* colliderA, ICollider* colliderB, Rigidbody* rbA, Rigidbody* rbB, Vector2 mtv, bool movableA, bool movableB);
		void CorrectOverlap(ICollider* colliderA, ICollider* colliderB, Vector2 mtv, bool movableA, bool movableB);
		void ResolveMomentum(Rigidbody* rbA, Rigidbody* rbB, RigidbodyType typeA, RigidbodyType typeB);

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

		void OnCollisionSystemEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) override;
		void OnCollisionSystemExit(ICollider* colliderA, ICollider* colliderB) override;
};
