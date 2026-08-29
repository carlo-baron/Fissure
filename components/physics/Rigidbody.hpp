#pragma once
#include "raylib.h"

enum class RigidbodyType{
	Static,
	Dynamic,
	Kinematic
};

class Rigidbody{
	private: 
		Vector2 velocity;
		RigidbodyType type;

	public:
		Rigidbody(Vector2 velocity = {0, 0}, RigidbodyType type = RigidbodyType::Kinematic);
		
		Vector2 GetVelocity();
		void SetVelocity(Vector2 velocity);

		RigidbodyType GetType();
		void SetType(RigidbodyType type);
};
