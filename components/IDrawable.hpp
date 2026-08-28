#pragma once
#include "raylib.h"

class IDrawable{
	public:
		virtual void Draw() const = 0;

		virtual Color GetColor() const = 0;
		virtual void SetColor(Color color) = 0;

		virtual ~IDrawable() {};
};
