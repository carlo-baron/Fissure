#pragma once

class GameObject;

class ICustomBehaviour{
	public:
		virtual void Start(GameObject* gameObject) = 0;
		virtual void Update() = 0;

		~ICustomBehaviour(){}; 
};
