#pragma once
#include "../components/circle/Circle.hpp"
#include "../components/rectangle/Rect.hpp"
#include "../components/gameObject/GameObject.hpp"
#include <vector>

using namespace std;

Vector2 CircleToCicleMTV(Circle* start, Circle* target);
void CollisionHandlerV2(vector<GameObject*> gameObjects);
void CollisionHandler(vector<Circle*> circles, vector<Rect *> rectangles);
void CircleCircleCollision(vector<Circle*> circles);
void RectangleCircleCollision(vector<Rect *> rectangles, vector<Circle*> circles);
