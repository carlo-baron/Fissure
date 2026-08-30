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
		/**
		 * @brief Creates a rectangle renderer bound to a transform.
		 *
		 * The renderer keeps only this narrow reference and reads its
		 * position from it — it does not know its GameObject.
		 * @param transform The object's transform. Non-owning.
		 * @param width Width of the drawn rectangle, before scale.
		 * @param height Height of the drawn rectangle, before scale.
		 * @param color Color to draw with.
		 */
		RectangleRenderer(IGameTransform* transform, float width = 10, float height = 10, Color color = WHITE);

		/**
		 * @brief Draws the rectangle outline at the transform's position, scaled by the transform's scale.
		 */
		void Draw() const override;
		Color GetColor() const override;
		void SetColor(Color color) override;
};
