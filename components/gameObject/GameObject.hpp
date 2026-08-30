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

		void Draw();
		void Update();

		template<typename T>
		T* GetComponent();
};


template<typename T>
T* GameObject::GetComponent() {
	return nullptr;
}

template<>
inline IGameTransform* GameObject::GetComponent<IGameTransform>() {
	return transform.get();
}

template<>
inline IDrawable* GameObject::GetComponent<IDrawable>() {
	return drawable.get();
}

template<>
inline ICollider* GameObject::GetComponent<ICollider>() {
	return collider.get();
}

template<>
inline Rigidbody* GameObject::GetComponent<Rigidbody>() {
	return rigidbody.get();
}

template<>
inline ICustomBehaviour* GameObject::GetComponent<ICustomBehaviour>() {
	return customBehaviour.get();
}
