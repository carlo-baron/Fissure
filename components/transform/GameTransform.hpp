#pragma once
#include "raylib.h"
class GameObject;

class GameTransform{
	private:
		Vector2 position;
		Vector2 localPosition;
		Vector2 rotation;
	  float scale;
		GameObject* gameObject;


	public:
		/**
		 * @brief Creates a transform with the given values (position {0,0}, rotation {0,0}, scale 1 by default).
		 * @param position Initial world position.
		 * @param rotation Initial rotation.
		 * @param scale Initial scale multiplier.
		 */
		GameTransform(Vector2 position = {0, 0}, Vector2 rotation = {0, 0}, float scale = 1);

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
};
