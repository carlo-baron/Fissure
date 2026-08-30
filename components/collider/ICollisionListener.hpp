#pragma once

class ICollider;

class ICollisionListener{
	public:
		virtual void OnCollisionEnter(ICollider* self, ICollider* other) const = 0;
		virtual void OnCollisionExit(ICollider* self, ICollider* other) const = 0;

		virtual ~ICollisionListener(){};
};
