#include "CollisionHandler.hpp"
#include "GameObject.hpp"
#include "collider/circleCollider/CircleCollider.hpp"
#include "raymath.h"
#include <raylib.h>
#include <vector>

using namespace std;

void CollisionHandler(vector<GameObject*> gameObjects){
	for(int i = 0; i < (int)gameObjects.size(); i++){
		for(int j = i + 1; j < (int)gameObjects.size(); j++){
			GameObject* objectA = gameObjects[i];
			GameObject* objectB = gameObjects[j];

			CircleCircleCollision(objectA, objectB);

		}
	}
}

void CircleCircleCollision(GameObject* objectA, GameObject* objectB) {
	CircleCollider* circleA = dynamic_cast<CircleCollider*>(objectA->GetCollider());
	CircleCollider* circleB = dynamic_cast<CircleCollider*>(objectB->GetCollider());

	if(!circleA || !circleB){
		return;
	}

	if(!circleA->IsEnabled() || !circleA->IsEnabled()){
		return;
	}

	Vector2 displacementVector = Vector2Subtract(
			circleB->GetPosition(),
			circleA->GetPosition()
		);

	float distance = Vector2Distance(
			circleB->GetPosition(),
			circleA->GetPosition()
		);

	float radiusSum = circleB->GetRadius() + circleA->GetRadius();

	if(distance <= radiusSum){
		Vector2 direction = Vector2Normalize(displacementVector);
		float penetrationDepth = radiusSum - distance;
		Vector2 mtv = Vector2Scale(direction, penetrationDepth);

		circleB->SetPosition(Vector2Add(circleB->GetPosition(), mtv));
	}
}
