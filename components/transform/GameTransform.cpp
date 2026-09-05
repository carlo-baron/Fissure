#include "GameTransform.hpp"
#include <algorithm>
#include <raymath.h>

GameTransform::GameTransform(Vector2 position, Vector2 origin, Vector2 rotation, float scale){
	this->origin = origin;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->localPosition = position;
}

Vector2 GameTransform::GetPosition() {
	if (!this->parent) {
		return this->position;
	}

	Vector2 parentPos = this->parent->GetPosition();
	float parentScale = this->parent->GetScale();
	return Vector2{
		parentPos.x + this->localPosition.x * parentScale,
		parentPos.y + this->localPosition.y * parentScale
	};
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

GameTransform* GameTransform::GetParent(){
	return this->parent;
}

void GameTransform::SetParent(GameTransform* parent){
	if(parent == this) return;
	if(this->parent == parent) return;

	Vector2 currentWorldPos = this->GetPosition();

	if(this->parent != nullptr){
		auto& siblings = this->parent->children;
		auto it = std::find(siblings.begin(), siblings.end(), this);
		if(it != siblings.end()){
			siblings.erase(it);
		}
	}

	this->parent = parent;

	if(parent){
		parent->children.push_back(this);
		Vector2 parentWorldPos = parent->GetPosition();
		float parentScale = parent->GetScale();
		this->localPosition = Vector2{
			(currentWorldPos.x - parentWorldPos.x) / parentScale,
				(currentWorldPos.y - parentWorldPos.y) / parentScale
		};
	} else {
		this->position = currentWorldPos;
	}
}

GameTransform* GameTransform::GetChild(int index){
	return this->children.at(index);
}

int GameTransform::GetChildCount(){
	return this->children.size();
}

Vector2 GameTransform::GetOrigin(){
	return this->origin;
}

void GameTransform::SetOrigin(Vector2 origin){
	this->origin = origin;
}
