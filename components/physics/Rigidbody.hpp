#pragma once
#include "raylib.h"

/**
 * @brief How the physics simulation treats a body.
 *
 * PhysicsSystem handles each type differently during integration and
 * collision response (see PhysicsSystem::PhysicsHandler() and
 * PhysicsSystem::OnCollisionEnter()):
 *
 * - Static: immovable world geometry. Never integrated, and its velocity
 *   is never rewritten by collisions.
 * - Kinematic: moved by gameplay code (SetPosition/SetVelocity) rather
 *   than by the simulation. Like Static it is excluded from integration
 *   and momentum rewrites, but it still fully participates in collisions.
 * - Dynamic: fully simulated. Gravity and velocity integration every
 *   frame, and its velocity is rewritten on collision by the inelastic
 *   momentum resolution.
 */
enum class RigidbodyType{
	Static,
	Dynamic,
	Kinematic
};

class Rigidbody{
	private: 
		float mass;
		Vector2 velocity;
		RigidbodyType type;
		float bounciness;
		float gravity;

	public:
		/**
		 * @brief Creates a rigidbody with the given physical properties.
		 * @param velocity Initial velocity.
		 * @param mass Mass used by collision momentum resolution.
		 * @param gravity Per-object gravity multiplier (see GetGravity()).
		 * @param type How the physics simulation treats this body.
		 */
		Rigidbody(Vector2 velocity = {0, 0}, float mass = 1, RigidbodyType type = RigidbodyType::Dynamic, float bounciness = 0, float gravity = 1);

		Vector2 GetVelocity();
		void SetVelocity(Vector2 velocity);

		RigidbodyType GetType();
		void SetType(RigidbodyType type);

		float GetMass();
		void SetMass(float mass);

		float GetBounciness();
		void SetBounciness(float bounciness);

		/**
		 * @brief Per-object gravity multiplier applied by PhysicsSystem.
		 *
		 * PhysicsSystem scales its system-wide gravityAcceleration by
		 * this value, and applies gravity only while the multiplier is
		 * greater than zero — objects that shouldn't fall set it to 0.
		 */
		float GetGravity();
		/**
		 * @brief Sets the gravity multiplier.
		 * @param gravity Multiplier of the global gravity acceleration (0 disables gravity).
		 */
		void SetGravity(float gravity);
};
