#pragma once
#include <memory>
#include "../transform/IGameTransform.hpp"
#include "../IDrawable.hpp"
#include "../collider/ICollider.hpp"
#include "../physics/Rigidbody.hpp"
#include "../ICustomBehaviour.hpp"

using namespace std;

class GameObject{
	private:
		unique_ptr<IGameTransform> transform;
		unique_ptr<IDrawable> drawable;
		unique_ptr<ICollider> collider;
		unique_ptr<Rigidbody> rigidbody;
		unique_ptr<ICustomBehaviour> customBehaviour;

	public:
		GameObject(
			unique_ptr<IGameTransform> transform,
			unique_ptr<IDrawable> drawable,
			unique_ptr<ICollider> collider = nullptr,
			unique_ptr<Rigidbody> rigidbody = nullptr,
			unique_ptr<ICustomBehaviour> customBehaviour = nullptr
		);

		IGameTransform* GetGameTransform();

		IDrawable* GetDrawable();

		ICollider* GetCollider();

		Rigidbody* GetRigidbody();

		void Draw();
};
