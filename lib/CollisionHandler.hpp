#pragma once
#include "../components/gameObject/GameObject.hpp"
#include "../components/collider/circleCollider/CircleCollider.hpp"
#include "../components/collider/rectangleCollider/RectangleCollider.hpp"
#include <optional>
#include <vector>

using namespace std;

void CollisionHandler(vector<GameObject*> gameObject);
optional<Vector2> CircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB);
void CircleRectangleCollision(CircleCollider* circle, RectangleCollider* rect);
