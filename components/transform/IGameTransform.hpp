#pragma once

#include "raylib.h"

class IGameTransform {
	public: 
		virtual Vector2 GetPosition() const = 0;
		virtual void SetPosition(Vector2 position) = 0;

		virtual Vector2 GetRotation() const = 0;
		virtual void SetRotation(Vector2 rotation) = 0;

		virtual float GetScale() const = 0;
		virtual void SetScale(float scale) = 0;

		virtual ~IGameTransform() {}
};
