#pragma once

#include "collider/ICollider.hpp"
class ICollisionSystemListener{
	public:
		virtual void OnCollisionSystemEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) = 0;
		virtual void OnCollisionSystemStay(ICollider* colliderA, ICollider* colliderB, Vector2 mtv) = 0;
		virtual void OnCollisionSystemExit(ICollider* colliderA, ICollider* colliderB) = 0;

		~ICollisionSystemListener(){};
};
