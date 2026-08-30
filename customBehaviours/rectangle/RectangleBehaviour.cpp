#include "RectangleBehaviour.hpp"

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

void RectangleBehaviour::OnCollisionEnter(ICollider* self, ICollider* other) const {
	this->gameObject->GetComponent<IDrawable>()->SetColor(RED);
}

void RectangleBehaviour::OnCollisionExit(ICollider* self, ICollider* other) const {
	this->gameObject->GetComponent<IDrawable>()->SetColor(WHITE);
}
