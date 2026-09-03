#include "GameObject.hpp"
#include "IDrawable.hpp"
#include <raylib.h>
#include <raymath.h>
#include <utility>

GameObject::GameObject(
	unique_ptr<GameTransform> transform,
	unique_ptr<IDrawable> drawable,
	unique_ptr<ICollider> collider,
	unique_ptr<Rigidbody> rigidbody,
	vector<unique_ptr<ICustomBehaviour>> customBehaviours
){
	this->transform = std::move(transform);
	this->drawable = std::move(drawable);
	this->collider = std::move(collider);
	this->rigidbody = std::move(rigidbody);
	this->customBehaviours = std::move(customBehaviours);

	for(auto& customBehaviour : this->customBehaviours){
		customBehaviour->Start(this);
	}
}

void GameObject::Draw(){
	drawable->Draw();
	if(collider){
		collider->GetDrawable()->Draw();
	}
}

void GameObject::Update(){
	for(auto& customBehaviour : this->customBehaviours){
		customBehaviour->Update();
	}
}
