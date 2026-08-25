#pragma once
#include "raylib.h"

class Circle{
	private: 
		int radius;
		Vector2 position;
		Color color;
		Vector2 velocity;
		bool hasGravity;

	public:
		Circle(int radius, Vector2 position, Color color = WHITE, Vector2 velocity = {0, 0}, bool hasGravity = false);

		void Draw();

		int GetRadius();
		void SetRadius(int radius);

		Vector2 GetPosition();
		void SetPosition(Vector2 position);

		Color GetColor();
		void SetColor(Color color);

		Vector2 GetVelocity();
		void SetVelocity(Vector2 velocity);
};
