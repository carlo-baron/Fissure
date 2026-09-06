#include "RectangleCollider.hpp"

RectangleCollider::RectangleCollider(GameTransform* transform, float width, float height, bool enabled, bool show, Color color){
	this->transform = transform;
	this->width = width;
	this->height = height;
	this->enabled = enabled;
	this->show = show;
	this->color = color;
	this->origin = Vector2{this->width / 2, this->height / 2};
}

bool RectangleCollider::IsEnabled() const{
	return this->enabled;
}
void RectangleCollider::SetEnabled(bool enabled){ this->enabled = enabled; }

void RectangleCollider::Draw() const {
	if(!this->show) return;

	Vector2 position = transform->GetPosition();
	float scale = transform->GetScale();

	DrawRectangleLines(
		transform->GetPosition().x - origin.x * scale,
		transform->GetPosition().y - origin.y * scale,
		this->width * scale,
		this->height * scale,
		this->color
	);
}

IDrawable* RectangleCollider::GetDrawable() const {
	return const_cast<RectangleCollider*>(this);
}

Vector2 RectangleCollider::GetPosition() const { 
	return this->transform->GetPosition(); 
}
void RectangleCollider::SetPosition(Vector2 position){
	this->transform->SetPosition(position); 
}

float RectangleCollider::GetWidth() { return this->width; }
float RectangleCollider::GetHeight() { return this->height; }

void RectangleCollider::OnCollisionEnter(ICollider* other) const {
	for(ICollisionListener* listener : this->listeners){
		listener->OnCollisionEnter(other);
	}
}

void RectangleCollider::OnCollisionExit(ICollider* other) const {
	for(ICollisionListener* listener : this->listeners){
		listener->OnCollisionExit(other);
	}
}

void RectangleCollider::AddListener(ICollisionListener* listener){
	this->listeners.push_back(listener);
}

Color RectangleCollider::GetColor() const {
	return this->color;
}

void RectangleCollider::SetColor(Color color){
	this->color = color;
}

ShapeType RectangleCollider::GetShapeType() const {
	return ShapeType::Rectangle;
}

Vector2 RectangleCollider::GetOrigin(){
	return this->origin;
}
