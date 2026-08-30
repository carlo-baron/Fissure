#include "Rigidbody.hpp"

Rigidbody::Rigidbody(Vector2 velocity, float mass, float gravity, RigidbodyType type){
	this->velocity = velocity;
	this->mass = mass;
	this->gravity = gravity;
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

float Rigidbody::GetMass(){
	return this->mass;
}
void Rigidbody::SetMass(float mass){
	this->mass = mass;
}

float Rigidbody::GetGravity(){
	return this->gravity;
}

void Rigidbody::SetGravity(float gravity){
	if(gravity < 0){
		this->gravity = 0;
	}

	this->gravity = gravity;
}
