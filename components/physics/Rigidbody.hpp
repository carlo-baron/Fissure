#pragma once
#include "raylib.h"

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
		float gravity;

	public:
		Rigidbody(Vector2 velocity = {0, 0}, float mass = 1, float gravity = 1, RigidbodyType type = RigidbodyType::Dynamic);
		
		Vector2 GetVelocity();
		void SetVelocity(Vector2 velocity);

		RigidbodyType GetType();
		void SetType(RigidbodyType type);

		float GetMass();
		void SetMass(float mass);

		float GetGravity();
		void SetGravity(float gravity);
};
