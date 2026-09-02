#include "GameObject.hpp"
#include "IDrawable.hpp"
#include <raylib.h>
#include <raymath.h>
#include <utility>

GameObject::GameObject(
	unique_ptr<IGameTransform> transform,
	unique_ptr<IDrawable> drawable,
	unique_ptr<ICollider> collider,
	unique_ptr<Rigidbody> rigidbody,
	vector<unique_ptr<ICustomBehaviour>> customBehaviours,
	GameObject* parent,
	vector<unique_ptr<GameObject>> children
){
	this->transform = std::move(transform);
	this->drawable = std::move(drawable);
	this->collider = std::move(collider);
	this->rigidbody = std::move(rigidbody);
	this->customBehaviours = std::move(customBehaviours);
	this->parent = parent;
	this->children = std::move(children);

	for(auto& customBehaviour : this->customBehaviours){
		customBehaviour->Start(this);
	}

	if(parent){
		this->transform->SetPosition(Vector2Add(this->transform->GetPosition(), parent->transform->GetPosition()));
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

GameObject* GameObject::GetParent(){
	return this->parent;
}

void GameObject::SetParent(GameObject* parent){
	this->parent = parent;
}

vector<GameObject*> GameObject::GetChildren(){
	vector<GameObject*> result;

	for(auto& gameObject : this->children){
		result.push_back(gameObject.get());
	}

	return result;
}

void GameObject::AddChild(unique_ptr<GameObject> child){
	child->SetParent(this);
	this->children.push_back(std::move(child));
}

void GameObject::RemoveChild(GameObject* child)
{
	for (auto it = children.begin(); it != children.end(); ++it)
	{
		if (it->get() == child)
		{
			child->SetParent(nullptr);
			children.erase(it);
			return;
		}
	}
}
