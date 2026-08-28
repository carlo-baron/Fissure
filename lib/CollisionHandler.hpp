#pragma once
#include "../components/gameObject/GameObject.hpp"
#include <vector>

using namespace std;

void CollisionHandler(vector<GameObject*> gameObject);
void CircleCircleCollision(GameObject* objectA, GameObject* objectB);
void CircleRectangleCollision(GameObject* objectA, GameObject* objectB);
