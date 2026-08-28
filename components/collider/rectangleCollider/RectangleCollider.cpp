#include "RectangleCollider.hpp"

RectangleCollider::RectangleCollider(IGameTransform* transform, float width, float height, bool enabled, bool show){
	this->transform = transform;
	this->width = width;
	this->height = height;
	this->enabled = enabled;
	this->show = show;
}

bool RectangleCollider::IsEnabled() const{
	return this->enabled;
}
void RectangleCollider::SetEnabled(bool enabled){ this->enabled = enabled; }

void RectangleCollider::Draw() const {
	if(!this->show) return;

	DrawRectangleLines(
		transform->GetPosition().x,
		transform->GetPosition().y,
		this->width * transform->GetScale(),
		this->height * transform->GetScale(),
		this->color
	);
}

IDrawable* RectangleCollider::GetDrawable() const {
	return const_cast<RectangleCollider*>(this);
}

Vector2 RectangleCollider::GetPosition() const { return this->transform->GetPosition(); }
void RectangleCollider::SetPosition(Vector2 position){ this->transform->SetPosition(position); }

float RectangleCollider::GetWidth() { return this->width; }
float RectangleCollider::GetHeight() { return this->height; }
