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
		CircleCollider(IGameTransform* transform, float radius = 10, bool enabled = true, bool show = false);

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
		void OnCollisionEnter(ICollider* self, ICollider* other) const override;
		void OnCollisionExit(ICollider* self, ICollider* other) const override;
		void AddListener(ICollisionListener* listener) override;
};
