#include "GameObject.hpp"
#include "IDrawable.hpp"
#include <queue>
#include <raylib.h>
#include <raymath.h>
#include <utility>

GameObject::GameObject(
	unique_ptr<GameTransform> transform,
	unique_ptr<IDrawable> drawable,
	unique_ptr<ICollider> collider,
	unique_ptr<Rigidbody> rigidbody,
	vector<unique_ptr<ICustomBehaviour>> customBehaviours
){
	this->transform = std::move(transform);
	this->drawable = std::move(drawable);
	this->collider = std::move(collider);
	this->rigidbody = std::move(rigidbody);
	this->customBehaviours = std::move(customBehaviours);

	if(this->transform){
		this->transform->Start(this);
	}

	for(auto& customBehaviour : this->customBehaviours){
		customBehaviour->Start(this);
	}
}

void GameObject::Draw(){
	drawable->Draw();
	if(collider){
		collider->GetDrawable()->Draw();
	}
}

void GameObject::Update(){
	for(auto& customBehaviour : this->customBehaviours){
		customBehaviour->Update();
	}
}

void GameObject::Destroy(){
	queue<GameTransform*> q;
	q.push(this->transform.get());

	while(q.size() != 0){
		int nodeCount = q.size();

		for(int i = 0; i < nodeCount; i++){
			GameTransform* curr = q.front();
			q.pop();

			curr->GetGameObject()->markForDestruction = true;
			for(GameTransform* child : curr->GetChildren()){
				q.push(child);
			}			
		}
	}
}

bool GameObject::IsMarkedForDestruction(){ return this->markForDestruction; }
