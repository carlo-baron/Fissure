#include "CircleCollider.hpp"

CircleCollider::CircleCollider(IGameTransform* transform, float radius, bool enabled, bool show){
	this->transform = transform;
	this->radius = radius;
	this->enabled = enabled;
	this->show = show;
}

void CircleCollider::Draw() const{
	if(show == true){
		DrawCircleLinesV(transform->GetPosition(), this->radius * transform->GetScale(), this->color);
	}
}

bool CircleCollider::IsEnabled() const{
	return this->enabled;
}

void CircleCollider::SetEnabled(bool enabled){
	this->enabled = enabled;
}

IDrawable* CircleCollider::GetDrawable() const {
	return const_cast<CircleCollider*>(this);
}

float CircleCollider::GetRadius(){
	return this->radius;
}
