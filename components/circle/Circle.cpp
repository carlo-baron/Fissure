#include "Circle.hpp"
#include "raylib.h"
#include <raymath.h>

Circle::Circle(int radius, Vector2 position, Color color, Vector2 velocity, bool hasGravity) {
	this->radius = radius;
	this->position = position;
	this->color = color;
	this->velocity = velocity;
	this->hasGravity = hasGravity;
}

void Circle::Draw() {
	velocity = Vector2Add(velocity, {0, (9.8f * GetFrameTime())});
	position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime()));
	DrawCircleLinesV(position, radius, color);
}

int Circle::GetRadius() {
	return this->radius;
}

void Circle::SetRadius(int radius) {
	this->radius = radius;
}

Vector2 Circle::GetPosition() {
	return this->position;
}

void Circle::SetPosition(Vector2 position) {
	this->position = position;
}

Color Circle::GetColor() {
	return this->color;
}

void Circle::SetColor(Color color) {
	this->color = color;
}

Vector2 Circle::GetVelocity(){
	return this->velocity;
}

void Circle::SetVelocity(Vector2 velocity){
	this->velocity = velocity;
}
