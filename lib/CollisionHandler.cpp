#include "CollisionHandler.hpp"
#include "CircleRenderer.hpp"
#include "GameObject.hpp"
#include "raymath.h"
#include <raylib.h>
#include <vector>

using namespace std;

Vector2 CircleToCicleMTV(Circle* start, Circle* target){
	Vector2 collisionDirection = Vector2Normalize(
			Vector2Subtract(target->GetPosition(), start->GetPosition())
			);
	float requiredDistance = start->GetRadius() + target->GetRadius();
	float currentDistance = Vector2Distance(target->GetPosition(), start->GetPosition());
	float penetration = requiredDistance - currentDistance;
	Vector2 mtv = Vector2Scale(collisionDirection, penetration);

	return mtv;
}

void CollisionHandlerV2(vector<GameObject*> gameObjects){
	for(int i = 0; i < gameObjects.size(); i++){
		for(int j = i + 1; j < gameObjects.size(); j++){
			GameObject* objectA = gameObjects[i];
			GameObject* objectB = gameObjects[j];

			CircleRenderer* circleA = dynamic_cast<CircleRenderer*>(objectA->GetDrawable());
			CircleRenderer* circleB = dynamic_cast<CircleRenderer*>(objectB->GetDrawable());

			if(circleA != nullptr && circleB != nullptr){
				if(CheckCollisionCircles(
							objectB->GetGameTransform()->GetPosition(),
							circleB->GetRadius(),
							objectA->GetGameTransform()->GetPosition(),
							circleA->GetRadius()
						)
					){
					circleB->SetColor(RED);
				}else{
					circleB->SetColor(WHITE);
				}
			}
		}
	}
}

void CollisionHandler(vector<Circle *> circles, vector<Rect*> rectangles){
	CircleCircleCollision(circles);
	RectangleCircleCollision(rectangles, circles);
}

void CircleCircleCollision(vector<Circle*> circles) {
	for(int i = 0; i < circles.size(); i++){
		for(int j = i + 1; j < circles.size(); j++){

			if(CheckCollisionCircles(
						circles[i]->GetPosition(), circles[i]->GetRadius(),
						circles[j]->GetPosition(), circles[j]->GetRadius()
						)
				){

				Vector2 mtv = CircleToCicleMTV(circles[i], circles[j]);
				Vector2 newPos = Vector2Add(circles[j]->GetPosition(), mtv);

				circles[j]->SetPosition(newPos);
			}
		}
	}
}

void RectangleCircleCollision(vector<Rect *> rectangles, vector<Circle *> circles){
	for(int i = 0; i < rectangles.size(); i++){
		for(int j = 0; j < circles.size(); j++){
			Circle* circleRef = circles[j];
			Rect* rectRef = rectangles[i];

			Rectangle rec = {
				rectRef->GetPosition().x,
				rectRef->GetPosition().y,
				rectRef->GetWidth(),
				rectRef->GetHeight()
			};

			if(CheckCollisionCircleRec(
				circleRef->GetPosition(),
				circleRef->GetRadius(),
				rec
			)){
				Vector2 circlePos = circleRef->GetPosition();

				float closeX = clamp(circlePos.x, rec.x, rec.x + rec.width);
				float closeY = clamp(circlePos.y, rec.y, rec.y + rec.height);

				float dx = circlePos.x - closeX;
				float dy = circlePos.y - closeY;

				float distance = sqrt((dx * dx) + (dy * dy));

				if(distance == 0){
					float left = circlePos.x - rec.x;
					float right = rec.x + rec.width - circlePos.x;
					float top = circlePos.y - rec.y;
					float bottom = rec.y + rec.height - circlePos.y;

					float minDistance = min({left, right, top, bottom});

					Vector2 collisionDirection;

					if(minDistance == left){
						collisionDirection = {-1, 0};
					}else if(minDistance == right){
						collisionDirection = {1, 0};
					}else if(minDistance == top){
						collisionDirection = {0, -1};
					}else{
						collisionDirection = {0, 1};
					}

					float penetration = circleRef->GetRadius() + minDistance;

					Vector2 mtv = Vector2Scale(
						collisionDirection,
						penetration
					);

					circleRef->SetPosition(
						Vector2Add(circlePos, mtv)
					);

					continue;
				}

				Vector2 collisionDirection = Vector2Normalize({dx, dy});
				float penetration = circleRef->GetRadius() - distance;

				Vector2 mtv = Vector2Scale(
					collisionDirection,
					penetration
				);

				circleRef->SetPosition(
					Vector2Add(circlePos, mtv)
				);
			}
		}
	}
}
