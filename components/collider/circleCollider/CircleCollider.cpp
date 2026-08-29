#include "CircleCollider.hpp"
#include "../rectangleCollider/RectangleCollider.hpp"
#include "../../../lib/CollisionHandler.hpp"
#include <optional>
#include <raymath.h>

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

Vector2 CircleCollider::GetPosition() const{
	return this->transform->GetPosition();
}

void CircleCollider::SetPosition(Vector2 position){
	this->transform->SetPosition(position);
}

float CircleCollider::GetRadius(){
	return this->radius;
}

Color CircleCollider::GetColor() const {
	return this->color;
}

void CircleCollider::SetColor(Color color){
	this->color = color;
}

void CircleCollider::OnCollisionEnter(ICollider* other) const {
	for(ICollisionListener* listener : this->listeners){
		listener->OnCollision(other);
	}
}

void CircleCollider::AddListener(ICollisionListener* listener){
	this->listeners.push_back(listener);
}

void CircleCollider::CollideWith(ICollider* other) {
	CircleCollider* circle = dynamic_cast<CircleCollider*>(other);
	if(circle){
		auto mtv = CircleCircleCollision(this, circle);
		if(mtv){
			circle->SetPosition(Vector2Add(circle->GetPosition(), *mtv));
		}
	}else{
		RectangleCollider* rect = dynamic_cast<RectangleCollider*>(other);
		if(rect){
			CircleRectangleCollision(this, rect);
		}
	}
}
