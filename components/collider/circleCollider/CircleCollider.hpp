#pragma once

#include "../ICollider.hpp"
#include "../../IDrawable.hpp"
#include "raylib.h"
#include "../../transform/IGameTransform.hpp"
#include <vector>

using namespace std;

class CircleCollider : public ICollider, public IDrawable{
	private:
		IGameTransform* transform;
		float radius;
		Color color = GREEN;
		bool enabled;
		bool show;
		vector<ICollisionListener*> listeners;
	
	public:
		CircleCollider(IGameTransform* transform, float radius = 10, bool enabled = true, bool show = false);

		bool IsEnabled() const override;
		void SetEnabled(bool enabled) override;
		
		void Draw() const override;

		IDrawable* GetDrawable() const override;

		Vector2 GetPosition() const override;
		void SetPosition(Vector2 position) override;

		Color GetColor() const override;
		void SetColor(Color color) override;

		float GetRadius();

		ShapeType GetShapeType() const override;
		void OnCollisionEnter(ICollider* self, ICollider* other) const override;
		void OnCollisionExit(ICollider* self, ICollider* other) const override;
		void AddListener(ICollisionListener* listener) override;
};
