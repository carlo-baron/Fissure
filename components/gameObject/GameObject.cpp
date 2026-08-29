#include "GameObject.hpp"
#include "IDrawable.hpp"

GameObject::GameObject(
	unique_ptr<IGameTransform> transform,
	unique_ptr<IDrawable> drawable,
	unique_ptr<ICollider> collider
){
	this->transform = std::move(transform);
	this->drawable = std::move(drawable);
	this->collider = std::move(collider);

	if(this->collider){
		this->collider->AddListener(this);
	}
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

void GameObject::Update(){
	if(collider){
		collider->GetDrawable()->Draw();
	}

	drawable->Draw();
}

void GameObject::OnCollision(ICollider* other) const {
	if(other){
		this->drawable->SetColor(RED);
	}else{
		this->drawable->SetColor(WHITE);
	}
}
