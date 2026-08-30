#include "GameTransform.hpp"

GameTransform::GameTransform(Vector2 position, Vector2 rotation, float scale){
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Vector2 GameTransform::GetPosition() const {
	return this->position;
}
void GameTransform::SetPosition(Vector2 position){
	this->position = position;
}

Vector2 GameTransform::GetRotation() const{
	return this->rotation;
}
void GameTransform::SetRotation(Vector2 rotation){
	this->rotation = rotation;
 }

float GameTransform::GetScale() const{
	return this->scale;
}
void GameTransform::SetScale(float scale){
	this->scale = scale;
}
