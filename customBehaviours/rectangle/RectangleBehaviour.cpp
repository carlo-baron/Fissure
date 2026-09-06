#include "RectangleBehaviour.hpp"
#include <raylib.h>

RectangleBehaviour::RectangleBehaviour(){}

void RectangleBehaviour::Start(GameObject* gameObject){
	this->gameObject = gameObject;

	ICollider* collider = this->gameObject->GetComponent<ICollider>();
	if(collider){
		collider->AddListener(this);
	}
}

void RectangleBehaviour::Update(){

}

void RectangleBehaviour::OnCollisionEnter(ICollider* other) const {
	if(other){
		gameObject->Destroy();
	}
}
void RectangleBehaviour::OnCollisionExit(ICollider* other) const {}
