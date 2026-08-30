#include "GameObject.hpp"
#include "IDrawable.hpp"
#include <raylib.h>
#include <raymath.h>

GameObject::GameObject(
	unique_ptr<IGameTransform> transform,
	unique_ptr<IDrawable> drawable,
	unique_ptr<ICollider> collider,
	unique_ptr<Rigidbody> rigidbody,
	unique_ptr<ICustomBehaviour> customBehaviour
){
	this->transform = std::move(transform);
	this->drawable = std::move(drawable);
	this->collider = std::move(collider);
	this->rigidbody = std::move(rigidbody);
	this->customBehaviour = std::move(customBehaviour);
}

IGameTransform* GameObject::GetGameTransform(){
	return transform.get();
}

IDrawable* GameObject::GetDrawable(){
	return drawable.get();
}

ICollider* GameObject::GetCollider(){
	return collider.get();
}

Rigidbody* GameObject::GetRigidbody(){
	return rigidbody.get();
}

void GameObject::Draw(){
	drawable->Draw();

	if(collider){
		collider->GetDrawable()->Draw();
	}

	if(customBehaviour){
		customBehaviour->Update();
	}
}
