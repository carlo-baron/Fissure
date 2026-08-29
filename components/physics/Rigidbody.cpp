#include "Rigidbody.hpp"

Rigidbody::Rigidbody(Vector2 velocity, RigidbodyType type){
	this->velocity = velocity;
	this->type = type;
}

Vector2 Rigidbody::GetVelocity(){
	return this->velocity;
}
void Rigidbody::SetVelocity(Vector2 velocity){
	this->velocity = velocity;
}

RigidbodyType Rigidbody::GetType(){
	return this->type;
}
void Rigidbody::SetType(RigidbodyType type){
	this->type = type;
}
