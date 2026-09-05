#include "RectangleRenderer.hpp"
#include "raylib.h"

RectangleRenderer::RectangleRenderer(GameTransform* transform, float width, float height, Color color){
	this->transform = transform;
	this->width = width;
	this->height = height;
	this->color = color;
	this->origin = Vector2{this->width / 2, this->height / 2};
}

void RectangleRenderer::Draw() const {
	Vector2 position = transform->GetPosition();
	float scale = transform->GetScale();
	Rectangle rect = {
		position.x,
		position.y,
		width * scale,
		height * scale
	};

	DrawRectanglePro(
			rect,
			Vector2{origin.x * scale, origin.y * scale},
			0, // rotation
			this->color
			);
}

Color RectangleRenderer::GetColor() const {
	return this->color;
}

void RectangleRenderer::SetColor(Color color){
	this->color = color;
}
