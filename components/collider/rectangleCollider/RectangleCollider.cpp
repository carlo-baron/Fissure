#include "RectangleCollider.hpp"
#include "../circleCollider/CircleCollider.hpp"
#include "../../../lib/CollisionHandler.hpp"
#include <raymath.h>

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

void RectangleCollider::OnCollisionEnter(ICollider* other) const {
	for(ICollisionListener* listener : this->listeners){
		listener->OnCollision(other);
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

void RectangleCollider::CollideWith(ICollider* other) {
	CircleCollider* circle = dynamic_cast<CircleCollider*>(other);
	if(circle){
		auto mtv = CircleRectangleCollision(circle, this);
		if(mtv){
			this->SetPosition(Vector2Add(this->GetPosition(), *mtv));
		}
	}else{
		RectangleCollider* rect = dynamic_cast<RectangleCollider*>(other);
		if(rect){
			auto mtv = RectangleRectangleCollision(this, rect);
			if(mtv){
				this->SetPosition(Vector2Add(this->GetPosition(), *mtv));
			}
		}
	}
}
