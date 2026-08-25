#pragma once
#include "raylib.h"

class Rect{
	private: 
		Vector2 position;
		float width;
		float height;
		Color color;
		Vector2 velocity;
		bool hasGravity;

	public:
		Rect(Vector2 position, float width, float height, Color color = WHITE, Vector2 velocity = {0, 0}, bool hasGravity = false);

		void Draw();

		Vector2 GetPosition();
		void SetPosition(Vector2 position);

		float GetWidth();
		void SetWidth(float width);

		float GetHeight();
		void SetHeight(float width);

		Color GetColor();
		void SetColor(Color color);

		Vector2 GetVelocity();
		void SetVelocity(Vector2 velocity);
};
