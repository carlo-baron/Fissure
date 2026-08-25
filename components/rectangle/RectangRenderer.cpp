#include "RectangleRenderer.hpp"
#include "raylib.h"

RectangleRenderer::RectangleRenderer(IGameTransform* transform, float width, float height, Color color){
	this->transform = transform;
	this->width = width;
	this->height = height;
	this->color = color;
}

void RectangleRenderer::Draw() const {
	DrawRectangleLines(
		transform->GetPosition().x,
		transform->GetPosition().y,
		this->width,
		this->height,
		this->color
	);
}
