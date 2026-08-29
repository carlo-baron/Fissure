#pragma once

class ICollider;

class ICollisionListener{
	public:
		virtual void OnCollisionEnter(ICollider* other) const = 0;
		virtual void OnCollisionExit(ICollider* other) const = 0;

		virtual ~ICollisionListener(){};
};
