#include "RectangleRenderer.hpp"
#include "raylib.h"

RectangleRenderer::RectangleRenderer(GameTransform* transform, float width, float height, Color color){
	this->transform = transform;
	this->width = width;
	this->height = height;
	this->color = color;
}

void RectangleRenderer::Draw() const {
	DrawRectangleLines(
		transform->GetPosition().x,
		transform->GetPosition().y,
		this->width * transform->GetScale(),
		this->height * transform->GetScale(),
		this->color
	);
}

Color RectangleRenderer::GetColor() const {
	return this->color;
}

void RectangleRenderer::SetColor(Color color){
	this->color = color;
}
