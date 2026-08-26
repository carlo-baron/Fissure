#pragma once
#include <memory>
#include "../transform/IGameTransform.hpp"
#include "../IDrawable.hpp"
#include "../collider/ICollider.hpp"

using namespace std;

class GameObject{
	private:
		unique_ptr<IGameTransform> transform;
		unique_ptr<IDrawable> drawable;
		unique_ptr<ICollider> collider;

	public:
		GameObject(
			unique_ptr<IGameTransform> transform,
			unique_ptr<IDrawable> drawable,
			unique_ptr<ICollider> collider = nullptr
		);

		IGameTransform* GetGameTransform();

		IDrawable* GetDrawable();

		ICollider* GetCollider();

		void Update();
};
