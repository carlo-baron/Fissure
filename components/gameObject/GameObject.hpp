#pragma once
#include <memory>
#include "../transform/IGameTransform.hpp"
#include "../IDrawable.hpp"
#include "../collider/ICollider.hpp"
#include "../physics/Rigidbody.hpp"

using namespace std;

class GameObject : public ICollisionListener {
	private:
		unique_ptr<IGameTransform> transform;
		unique_ptr<IDrawable> drawable;
		unique_ptr<ICollider> collider;
		unique_ptr<Rigidbody> rigidbody;

	public:
		GameObject(
			unique_ptr<IGameTransform> transform,
			unique_ptr<IDrawable> drawable,
			unique_ptr<ICollider> collider = nullptr,
			unique_ptr<Rigidbody> rigidbody = nullptr
		);

		IGameTransform* GetGameTransform();

		IDrawable* GetDrawable();

		ICollider* GetCollider();

		Rigidbody* GetRigidbody();

		void OnCollisionEnter(ICollider* other) const override;
		void OnCollisionExit(ICollider* other) const override;

		void Update();
};
