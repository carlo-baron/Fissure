#pragma once

#include "IDrawable.hpp"
#include "../transform/IGameTransform.hpp"
#include "../ICollider.hpp"
#include <vector>

using namespace std;

class RectangleCollider : public ICollider, public IDrawable{
	private:
		IGameTransform* transform;
		float width;
		float height;
		Color color;
		bool enabled;
		bool show;
		vector<ICollisionListener*> listeners;

	public:
		RectangleCollider(IGameTransform* transform, float width = 20, float height = 20, bool enabled = true, bool show = false);

		bool IsEnabled() const override;
		void SetEnabled(bool enabled) override;

		void Draw() const override;
		IDrawable* GetDrawable() const override;

		Vector2 GetPosition() const override;
		void SetPosition(Vector2 position) override;

		float GetWidth();
		float GetHeight();

		Color GetColor() const override;
		void SetColor(Color color) override;

		void OnCollisionEnter(ICollider* other) const override;
		void AddListener(ICollisionListener* listener) override;
		void CollideWith(ICollider* other) override;
};
