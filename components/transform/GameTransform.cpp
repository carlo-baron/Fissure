#include "GameTransform.hpp"

GameTransform::GameTransform(Vector2 position, Vector2 rotation, float scale){
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	this->localPosition = position;
}

Vector2 GameTransform::GetPosition() {
	return this->position;
}
void GameTransform::SetPosition(Vector2 position){
	this->position = position;
}

Vector2 GameTransform::GetRotation() {
	return this->rotation;
}
void GameTransform::SetRotation(Vector2 rotation){
	this->rotation = rotation;
 }

float GameTransform::GetScale() {
	return this->scale;
}
void GameTransform::SetScale(float scale){
	this->scale = scale;
}

Vector2 GameTransform::GetLocalPosition(){
	return this->localPosition;
}

void GameTransform::SetLocalPosition(Vector2 localPosition){
	this->localPosition = localPosition;
}

void GameTransform::Start(GameObject* owner){
	this->gameObject = owner;
}

GameObject* GameTransform::GetGameObject(){
	return this->gameObject;
}

GameTransform* GetParent(){
	return nullptr;
}
