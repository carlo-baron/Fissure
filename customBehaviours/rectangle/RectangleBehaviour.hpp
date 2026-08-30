#pragma once
#include "../../components/ICustomBehaviour.hpp"
#include "../../components/collider/ICollisionListener.hpp"
#include "../../components/gameObject/GameObject.hpp"

class RectangleBehaviour : public ICustomBehaviour, public ICollisionListener{
	private:
		GameObject* gameObject;

	public:
		RectangleBehaviour();

		void Start(GameObject* gameObject) override;
		void Update() override;

		void OnCollisionEnter(ICollider* self, ICollider* other) const override;
		void OnCollisionExit(ICollider* self, ICollider* other) const override;
};
