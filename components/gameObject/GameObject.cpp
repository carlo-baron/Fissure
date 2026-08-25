#include "GameObject.hpp"

GameObject::GameObject(unique_ptr<IGameTransform> transform, unique_ptr<IDrawable> drawable){
	this->transform = std::move(transform);
	this->drawable = std::move(drawable);
}

IGameTransform* GameObject::GetGameTransform(){
	return transform.get();
}

IDrawable* GameObject::GetDrawable(){
	return drawable.get();
}

void GameObject::Update(){
	drawable->Draw();
}

