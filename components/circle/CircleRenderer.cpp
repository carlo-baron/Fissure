#include "CircleRenderer.hpp"
#include <raylib.h>

CircleRenderer::CircleRenderer(IGameTransform* transform, float radius, Color color){
	this->transform = transform;
	this->radius = radius;
	this->color = color;
}

void CircleRenderer::Draw() const {
	DrawCircleLinesV(transform->GetPosition(), this->radius * transform->GetScale(), this->color);
}

float CircleRenderer::GetRadius(){
	return this->radius;
}

void CircleRenderer::SetColor(Color color){
	this->color = color;
}
