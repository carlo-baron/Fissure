#include "CollisionHandler.hpp"
#include "GameObject.hpp"
#include "collider/circleCollider/CircleCollider.hpp"
#include "collider/rectangleCollider/RectangleCollider.hpp"
#include "raymath.h"
#include <algorithm>
#include <optional>
#include <raylib.h>
#include <vector>

using namespace std;

void CollisionHandler(vector<GameObject*> gameObjects){
	for(int i = 0; i < (int)gameObjects.size(); i++){
		for(int j = i + 1; j < (int)gameObjects.size(); j++){
			GameObject* objectA = gameObjects[i];
			GameObject* objectB = gameObjects[j];

			objectA->GetCollider()->CollideWith(objectB->GetCollider());
			objectB->GetCollider()->CollideWith(objectA->GetCollider());
		}
	}
}

void CircleRectangleCollision(CircleCollider* circle, RectangleCollider* rect){
	if(!circle || !rect) return;
	if(!circle->IsEnabled() || !rect->IsEnabled()) return;

	float closeX = clamp(circle->GetPosition().x, rect->GetPosition().x, rect->GetPosition().x + rect->GetWidth());
	float closeY = clamp(circle->GetPosition().y, rect->GetPosition().y, rect->GetPosition().y + rect->GetHeight());

	Vector2 displacementVector = Vector2Subtract(circle->GetPosition(), { closeX, closeY });
	float distance = Vector2Distance(circle->GetPosition(), { closeX, closeY });

	if(distance <= circle->GetRadius()){
		rect->OnCollisionEnter(circle);
		circle->OnCollisionEnter(rect);
	}else{
		rect->OnCollisionEnter(nullptr);
		circle->OnCollisionEnter(nullptr);
	}
}

optional<Vector2> CircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB) {
	if(!circleA || !circleB) return nullopt;
	if(!circleA->IsEnabled() || !circleB->IsEnabled()) return nullopt;

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
		
		return mtv;
	}

	return nullopt;
}
