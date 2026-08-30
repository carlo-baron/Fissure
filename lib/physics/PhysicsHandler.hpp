#pragma once
#include "../components/gameObject/GameObject.hpp"
#include <unordered_map>
#include <vector>

class PhysicsSystem : public ICollisionListener{
	private:
		vector<GameObject*> gameObjects;
		unordered_map<ICollider*, Rigidbody*> collRbMap;
		float gravityAcceleration = 150;

	public:
		PhysicsSystem(vector<GameObject*> gameObject);

		void PhysicsHandler();

		void OnCollisionEnter(ICollider* self, ICollider* other) const override;
		void OnCollisionExit(ICollider* self, ICollider* other) const override;
};
