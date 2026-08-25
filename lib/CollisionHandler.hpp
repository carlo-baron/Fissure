#pragma once
#include "../components/circle/Circle.hpp"
#include "../components/rectangle/Rect.hpp"
#include <vector>

Vector2 CircleToCicleMTV(Circle* start, Circle* target);
void CollisionHandler(std::vector<Circle*> circles, std::vector<Rect *> rectangles);
void CircleCircleCollision(std::vector<Circle*> circles);
void RectangleCircleCollision(std::vector<Rect *> rectangles, std::vector<Circle*> circles);
