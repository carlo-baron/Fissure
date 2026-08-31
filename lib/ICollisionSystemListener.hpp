#pragma once

#include "collider/ICollider.hpp"
class ICollisionSystemListener{
	public:
		virtual void OnCollisionSystemEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) const = 0;
		virtual void OnCollisionSystemExit(ICollider* colliderA, ICollider* colliderB) const = 0;

		~ICollisionSystemListener(){};
};
