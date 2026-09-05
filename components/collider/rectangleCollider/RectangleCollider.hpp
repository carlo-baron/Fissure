#pragma once

#include "IDrawable.hpp"
#include "../transform/GameTransform.hpp"
#include "../ICollider.hpp"
#include <vector>

using namespace std;

class RectangleCollider : public ICollider, public IDrawable{
	private:
		GameTransform* transform;
		float width;
		float height;
		Color color;
		bool enabled;
		bool show;
		Vector2 origin;
		vector<ICollisionListener*> listeners;

	public:
		/**
		 * @brief Creates a rectangle collider bound to a transform.
		 *
		 * The collider keeps only this narrow reference and reads/writes
		 * its position through it — it does not know its GameObject.
		 * @param transform The object's transform. Non-owning.
		 * @param width Collision width.
		 * @param height Collision height.
		 * @param enabled Whether collision detection starts enabled.
		 * @param show Whether the debug outline is drawn (see Draw()).
		 */
		RectangleCollider(
			GameTransform* transform,
			float width = 20,
			float height = 20,
			bool enabled = true,
			bool show = false,
			Color color = GREEN
		);

		bool IsEnabled() const override;
		void SetEnabled(bool enabled) override;

		/**
		 * @brief Draws the debug outline, but only while the show flag is set.
		 *
		 * Intended purely for debugging: the outline (scaled by the
		 * transform) is only rendered if the collider was created with
		 * show = true.
		 */
		void Draw() const override;
		/**
		 * @brief This collider as its own debug drawable (see Draw()).
		 */
		IDrawable* GetDrawable() const override;

		Vector2 GetPosition() const override;
		void SetPosition(Vector2 position) override;

		float GetWidth();
		float GetHeight();

		Color GetColor() const override;
		void SetColor(Color color) override;

		ShapeType GetShapeType() const override;

		void OnCollisionEnter(ICollider* other) const override;
		void OnCollisionExit(ICollider* other) const override;
		void AddListener(ICollisionListener* listener) override;

		Vector2 GetOrigin();
};
