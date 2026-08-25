#pragma once

#include "IDrawable.hpp"
#include "../transform/IGameTransform.hpp"

class RectangleRenderer : public IDrawable{
	private:
		IGameTransform* transform;
		float width;
		float height;
		Color color;

	public:
		RectangleRenderer(IGameTransform* transform, float width = 10, float height = 10, Color color = WHITE);

		void Draw() const override;
};
