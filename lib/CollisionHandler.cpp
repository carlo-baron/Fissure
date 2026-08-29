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

optional<Vector2> RectangleRectangleCollision(RectangleCollider *rectA, RectangleCollider *rectB){
	if(!rectA || !rectB) return nullopt;
	if(!rectA->IsEnabled() || !rectB->IsEnabled()) return nullopt;

	float leftA = rectA->GetPosition().x;
	float rightA = leftA + rectA->GetWidth();
	float topA = rectA->GetPosition().y;
	float bottomA = topA + rectA->GetHeight();

	float leftB = rectB->GetPosition().x;
	float rightB = leftB + rectB->GetWidth();
	float topB = rectB->GetPosition().y;
	float bottomB = topB + rectB->GetHeight();

	float overlapX = min(rightA, rightB) - max(leftA, leftB);
	float overlapY = min(bottomA, bottomB) - max(topA, topB);

	if(overlapX > 0 && overlapY > 0){
		if(overlapX < overlapY){
			float centerAX = (leftA + rightA) / 2;
			float centerBX = (leftB + rightB) / 2;
			int dirX = centerAX < centerBX ? -1 : 1;
			return Vector2{(float)dirX * overlapX, 0};
		}else{
			float centerAY = (topA + bottomA) / 2;
			float centerBY = (topB + bottomB) / 2;
			int dirY = centerAY < centerBY ? -1 : 1;
			return Vector2{0, (float)dirY * overlapY};
		}
	}
	return nullopt;
}

optional<Vector2> CircleRectangleCollision(CircleCollider* circle, RectangleCollider* rect){
	if(!circle || !rect) return nullopt;
	if(!circle->IsEnabled() || !rect->IsEnabled()) return nullopt;

	float closeX = clamp(circle->GetPosition().x, rect->GetPosition().x, rect->GetPosition().x + rect->GetWidth());
	float closeY = clamp(circle->GetPosition().y, rect->GetPosition().y, rect->GetPosition().y + rect->GetHeight());
	Vector2 displacementVector = Vector2Subtract(circle->GetPosition(), { closeX, closeY });
	float distance = Vector2Distance(circle->GetPosition(), { closeX, closeY });

	if(distance > circle->GetRadius()) return nullopt;

	if(distance == 0){
		float left = circle->GetPosition().x - rect->GetPosition().x;
		float right = (rect->GetPosition().x + rect->GetWidth()) - circle->GetPosition().x;
		float top = circle->GetPosition().y - rect->GetPosition().y;
		float bottom = (rect->GetPosition().y + rect->GetHeight()) - circle->GetPosition().y;

		float minDist = std::min({left, right, top, bottom});
		Vector2 direction;
		if(minDist == left) direction = {-1, 0};
		else if(minDist == right) direction = {1, 0};
		else if(minDist == top) direction = {0, -1};
		else direction = {0, 1};

		float penetrationDepth = circle->GetRadius() + minDist;
		return Vector2Scale(direction, penetrationDepth);
	}

	Vector2 direction = Vector2Normalize(displacementVector);
	float penetrationDepth = circle->GetRadius() - distance;
	return Vector2Scale(direction, penetrationDepth);
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
