#include "Rigidbody.hpp"
#include <algorithm>

Rigidbody::Rigidbody(Vector2 velocity, float mass, RigidbodyType type, float bounciness , float gravity){
	this->velocity = velocity;
	this->mass = mass;
	this->type = type;
	this->bounciness = bounciness;
	this->gravity = gravity;
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

float Rigidbody::GetBounciness(){
	return this->bounciness;
}

void Rigidbody::SetBounciness(float bounciness){
	this->bounciness = std::clamp(bounciness, 0.0f, 1.0f);
}

void Rigidbody::SetGravity(float gravity){
	if(gravity < 0){
		this->gravity = 0;
	}

	this->gravity = gravity;
}
