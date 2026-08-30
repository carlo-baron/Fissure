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

void CircleCollider::OnCollisionEnter(ICollider* self, ICollider* other) const {
	for(ICollisionListener* listener : this->listeners){
		listener->OnCollisionEnter(self, other);
	}
}

void CircleCollider::OnCollisionExit(ICollider* self, ICollider* other) const {
	for(ICollisionListener* listener : this->listeners){
		listener->OnCollisionExit(self, other);
	}
}

void CircleCollider::AddListener(ICollisionListener* listener){
	this->listeners.push_back(listener);
}

ShapeType CircleCollider::GetShapeType() const {
	return ShapeType::Circle;
}
