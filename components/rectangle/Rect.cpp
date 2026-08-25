#include "Rect.hpp"
#include <raylib.h>

Rect::Rect(Vector2 position, float width, float height, Color color, Vector2 velocity, bool hasGravity){
	this->position = position;
	this->width = width;
	this->height = height;
	this->color = color;
	this->velocity = velocity;
	this->hasGravity = hasGravity;
}

void Rect::Draw(){
	DrawRectangleLines(position.x, position.y, width, height, color);
}

Vector2 Rect::GetPosition(){
	return position;
}

void Rect::SetPosition(Vector2 position){
	this->position = position;
}

float Rect::GetWidth(){
	return width;
}

void Rect::SetWidth(float width){
	this->width = width;
}

float Rect::GetHeight(){
	return height;
}

void Rect::SetHeight(float height){
	this->height = height;
}

Color Rect::GetColor() {
	return this->color;
}

void Rect::SetColor(Color color) {
	this->color = color;
}

Vector2 Rect::GetVelocity(){
	return this->velocity;
}

void Rect::SetVelocity(Vector2 velocity){
	this->velocity = velocity;
}
