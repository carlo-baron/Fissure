#pragma once
#include "raylib.h"
#include <vector>
class GameObject;

class GameTransform{
	private:
		Vector2 position;
		Vector2 origin;
		Vector2 localPosition;
		Vector2 rotation;
	  float scale;
		GameObject* gameObject;
		GameTransform* parent = nullptr;
		std::vector<GameTransform*> children = {};

	public:
		GameTransform(Vector2 position = {0, 0}, Vector2 shapeOrigin = {0, 0}, Vector2 rotation = {0, 0}, float scale = 1);

		Vector2 GetPosition();
		void SetPosition(Vector2 position);

		Vector2 GetRotation();
		void SetRotation(Vector2 rotation);

		float GetScale();
		void SetScale(float scale);

		Vector2 GetLocalPosition();
		void SetLocalPosition(Vector2 localPosition);

		void Start(GameObject* owner);
		GameObject* GetGameObject();

		GameTransform* GetParent();
		void SetParent(GameTransform* parent);
		
		GameTransform* GetChild(int index);
		int GetChildCount();

		Vector2 GetOrigin();
		void SetOrigin(Vector2 origin);
};
