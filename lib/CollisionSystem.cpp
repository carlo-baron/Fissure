#include "CollisionSystem.hpp"
#include "GameObject.hpp"
#include "ICollisionSystemListener.hpp"
#include "collider/circleCollider/CircleCollider.hpp"
#include "collider/rectangleCollider/RectangleCollider.hpp"
#include "raymath.h"
#include <algorithm>
#include <optional>
#include <raylib.h>
#include <vector>

using namespace std;

CollisionSystem::CollisionSystem(vector<GameObject*> gameObjects){
	this->gameObjects = gameObjects; 
}

void CollisionSystem::CollisionHandler(){
	for(int i = 0; i < (int)gameObjects.size(); i++){
		for(int j = i + 1; j < (int)gameObjects.size(); j++){
			ICollider* colliderA = gameObjects[i]->GetComponent<ICollider>();
			ICollider* colliderB = gameObjects[j]->GetComponent<ICollider>();
			if(!colliderA || !colliderB) continue;

			ShapeType shapeA = colliderA->GetShapeType();
			ShapeType shapeB = colliderB->GetShapeType();

			if(shapeA == ShapeType::Circle && shapeB == ShapeType::Circle){
				CircleCollider* circleA = dynamic_cast<CircleCollider*>(colliderA);
				CircleCollider* circleB = dynamic_cast<CircleCollider*>(colliderB);
				auto mtv = CircleCircleCollision(circleA, circleB);
				NotifyListeners(circleA, circleB, mtv);

			}else if(shapeA == ShapeType::Circle && shapeB == ShapeType::Rectangle){
				CircleCollider* circle = dynamic_cast<CircleCollider*>(colliderA);
				RectangleCollider* rect = dynamic_cast<RectangleCollider*>(colliderB);
				auto mtv = CircleRectangleCollision(circle, rect);
				if(mtv) *mtv = Vector2Negate(*mtv);
				NotifyListeners(circle, rect, mtv);

			}else if(shapeA == ShapeType::Rectangle && shapeB == ShapeType::Circle){
				RectangleCollider* rect = dynamic_cast<RectangleCollider*>(colliderA);
				CircleCollider* circle = dynamic_cast<CircleCollider*>(colliderB);
				auto mtv = CircleRectangleCollision(circle, rect);
				NotifyListeners(rect, circle, mtv);

			}else if(shapeA == ShapeType::Rectangle && shapeB == ShapeType::Rectangle){
				RectangleCollider* rectA = dynamic_cast<RectangleCollider*>(colliderA);
				RectangleCollider* rectB = dynamic_cast<RectangleCollider*>(colliderB);
				auto mtv = RectangleRectangleCollision(rectA, rectB);
				if(mtv) *mtv = Vector2Negate(*mtv);
				NotifyListeners(rectA, rectB, mtv);
			}
		}
	}
}

bool CollisionSystem::AddActiveColliders(ICollider* colliderA, ICollider* colliderB){
	return this->activeCollisions.insert({colliderA, colliderB}).second;
}

int CollisionSystem::RemoveActiveColliders(ICollider* colliderA, ICollider* colliderB){
	return this->activeCollisions.erase({colliderA, colliderB});
}

optional<Vector2> CollisionSystem::RectangleRectangleCollision(RectangleCollider *rectA, RectangleCollider *rectB){
	if(!rectA || !rectB) return nullopt;
	if(!rectA->IsEnabled() || !rectB->IsEnabled()) return nullopt;

	Vector2 originA = rectA->GetOrigin();
	Vector2 originB = rectB->GetOrigin();

	float leftA = rectA->GetPosition().x - originA.x;
	float rightA = leftA + rectA->GetWidth() + originB.x;
	float topA = rectA->GetPosition().y - originA.y;
	float bottomA = topA + rectA->GetHeight() + originA.y;

	float leftB = rectB->GetPosition().x - originB.x;
	float rightB = leftB + rectB->GetWidth() + originB.x;
	float topB = rectB->GetPosition().y - originB.y;
	float bottomB = topB + rectB->GetHeight() + originB.y;

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

optional<Vector2> CollisionSystem::CircleRectangleCollision(CircleCollider* circle, RectangleCollider* rect){
	if(!circle || !rect) return nullopt;
	if(!circle->IsEnabled() || !rect->IsEnabled()) return nullopt;

	Vector2 rectOrigin = rect->GetOrigin();

	float closeX = clamp(circle->GetPosition().x, rect->GetPosition().x - (rectOrigin.x), rect->GetPosition().x + rectOrigin.x);
	float closeY = clamp(circle->GetPosition().y, rect->GetPosition().y - rectOrigin.y, rect->GetPosition().y + rectOrigin.y);
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

optional<Vector2> CollisionSystem::CircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB) {
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

void CollisionSystem::NotifyListeners(ICollider* colliderA, ICollider* colliderB, optional<Vector2> mtv){
	if(mtv){
		bool isNew = AddActiveColliders(colliderA, colliderB);
		if(isNew){
			NotifyListenersEnter(colliderA, colliderB, *mtv);
		}else{
			NotifyListenersStay(colliderA, colliderB, *mtv);
		}
	}else{
		if(RemoveActiveColliders(colliderA, colliderB) != 0){
			NotifyListenersExit(colliderA, colliderB);
		}
	}
}

void CollisionSystem::AddListener(ICollisionSystemListener* listener){
	this->listeners.push_back(listener);
}

void CollisionSystem::NotifyListenersEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv){
	for(ICollisionSystemListener* listener: listeners){
		listener->OnCollisionSystemEnter(colliderA, colliderB, mtv);
	}
}

void CollisionSystem::NotifyListenersStay(ICollider* colliderA, ICollider* colliderB, Vector2 mtv){
	for(ICollisionSystemListener* listener: listeners){
		listener->OnCollisionSystemStay(colliderA, colliderB, mtv);
	}
}

void CollisionSystem::NotifyListenersExit(ICollider* colliderA, ICollider* colliderB){
	for(ICollisionSystemListener* listener: listeners){
		listener->OnCollisionSystemExit(colliderA, colliderB);
	}
}

