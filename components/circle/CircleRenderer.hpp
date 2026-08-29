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
		CircleRenderer(IGameTransform* transform, float radius = 10, Color color = WHITE);

		void Draw() const override;
		Color GetColor() const override;
		void SetColor(Color color) override;

		float GetRadius();

};
