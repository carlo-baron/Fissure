#pragma once

#include "../IDrawable.hpp"
#include "GameTransform.hpp"
#include "raylib.h"

class CircleRenderer : public IDrawable{
	private:
		GameTransform* transform;
		float radius;
		Color color;

	public:
		/**
		 * @brief Creates a circle renderer bound to a transform.
		 *
		 * The renderer keeps only this narrow reference and reads its
		 * position from it — it does not know its GameObject.
		 * @param transform The object's transform. Non-owning.
		 * @param radius Radius of the drawn circle, before scale.
		 * @param color Color to draw with.
		 */
		CircleRenderer(GameTransform* transform, float radius = 10, Color color = WHITE);

		/**
		 * @brief Draws the circle outline at the transform's position, scaled by the transform's scale.
		 */
		void Draw() const override;
		Color GetColor() const override;
		void SetColor(Color color) override;

		float GetRadius();

};
