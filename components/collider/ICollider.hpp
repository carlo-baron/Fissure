#pragma once

#include "IDrawable.hpp"
#include "raylib.h"
#include "ICollisionListener.hpp"

enum class ShapeType { Circle, Rectangle };

class ICollider{
	public:
		virtual bool IsEnabled() const = 0;
		virtual void SetEnabled(bool enabled) = 0;
		virtual IDrawable* GetDrawable() const = 0;

		virtual Vector2 GetPosition() const = 0;
		virtual void SetPosition(Vector2 position) = 0;

		virtual ShapeType GetShapeType() const = 0;
		virtual void OnCollisionEnter(ICollider* other) const = 0;
		virtual void OnCollisionExit(ICollider* other) const = 0;
		virtual void AddListener(ICollisionListener* listener) = 0;

		virtual ~ICollider() {};
};
