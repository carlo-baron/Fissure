#include "GameObject.hpp"


GameObject::GameObject(unique_ptr<IGameTransform> transform, unique_ptr<IDrawable> drawable){
	this->transform = std::move(transform);
	this->drawable = std::move(drawable);
}

void GameObject::Update(){
	drawable->Draw();
}
