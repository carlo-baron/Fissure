#pragma once

#include "../ICollider.hpp"
#include "../../IDrawable.hpp"
#include "raylib.h"
#include "../../transform/IGameTransform.hpp"

class CircleCollider : public ICollider, public IDrawable{
	private:
		IGameTransform* transform;
		float radius;
		Color color = GREEN;
		bool enabled;
		bool show;
	
	public:
		CircleCollider(IGameTransform* transform, float radius = 10, bool enabled = true, bool show = false);

		bool IsEnabled() const override;
		void SetEnabled(bool enabled) override;
		
		void Draw() const override;

		IDrawable* GetDrawable() const override;

		float GetRadius();
};
