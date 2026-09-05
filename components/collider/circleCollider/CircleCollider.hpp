#pragma once

#include "../ICollider.hpp"
#include "../../IDrawable.hpp"
#include "raylib.h"
#include "../../transform/GameTransform.hpp"
#include <vector>

using namespace std;

class CircleCollider : public ICollider, public IDrawable{
	private:
		GameTransform* transform;
		float radius;
		Color color;
		bool enabled;
		bool show;
		vector<ICollisionListener*> listeners;
	
	public:
		/**
		 * @brief Creates a circle collider bound to a transform.
		 *
		 * The collider keeps only this narrow reference and reads/writes
		 * its position through it — it does not know its GameObject.
		 * @param transform The object's transform. Non-owning.
		 * @param radius Collision radius.
		 * @param enabled Whether collision detection starts enabled.
		 * @param show Whether the debug outline is drawn (see Draw()).
		 */
		CircleCollider(GameTransform* transform, float radius = 10, bool enabled = true, bool show = false, Color color = GREEN);

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

		Color GetColor() const override;
		void SetColor(Color color) override;

		float GetRadius();

		ShapeType GetShapeType() const override;
		void OnCollisionEnter(ICollider* other) const override;
		void OnCollisionExit(ICollider* other) const override;
		void AddListener(ICollisionListener* listener) override;
};
