#pragma once

class ICollider;

class ICollisionListener{
	public:
		virtual void OnCollision(ICollider* other) const = 0;

		virtual ~ICollisionListener(){};
};
