#pragma once

#include "../IDrawable.hpp"
#include "raylib.h"
#include "../transform/IGameTransform.hpp"

class CircleRenderer : public IDrawable{
	private:
		IGameTransform* transform;
		float radius;
		Color color;

	public: 
		CircleRenderer(IGameTransform* transform, float radius = 5, Color color = WHITE);

		void Draw() const override;
		
		float GetRadius();

		void SetColor(Color color);
};
