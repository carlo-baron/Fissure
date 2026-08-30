#include "RectangleBehaviour.hpp"

RectangleBehaviour::RectangleBehaviour(){}

void RectangleBehaviour::Start(GameObject* gameObject){
	this->gameObject = gameObject;

	ICollider* collider = this->gameObject->GetCollider();
	if(collider){
		collider->AddListener(this);
	}
}

void RectangleBehaviour::Update(){

}

void RectangleBehaviour::OnCollisionEnter(ICollider* self, ICollider* other) const {
	this->gameObject->GetDrawable()->SetColor(RED);
}

void RectangleBehaviour::OnCollisionExit(ICollider* self, ICollider* other) const {
	this->gameObject->GetDrawable()->SetColor(WHITE);
}
