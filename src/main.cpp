#include "raylib.h"
#include <vector>
#include "../components/circle/Circle.hpp"
#include "../components/rectangle/Rect.hpp"
#include "../lib/CollisionHandler.hpp"

using namespace std;

int main(){
	InitWindow(500, 500, "Collision Detector");
	SetTargetFPS(60);

	vector<Circle*> circles;
	vector<Rect*> rectangles;

	Vector2 center = {
		GetScreenWidth() / 2.0f,
		GetScreenHeight() / 2.0f
	};

	Circle mouseCircle(10, {0, 0});
	Circle fallingCircle(50, { center.x, 0}, PINK, {0, 100}, true);
	Rect rect1(center, 50, 50);

	circles.push_back(&mouseCircle);
	circles.push_back(&fallingCircle);

	rectangles.push_back(&rect1);

	while(!WindowShouldClose()){
		Vector2 mousePos = GetMousePosition();
		circles[0]->SetPosition(mousePos);

		//handle circle collision
		CollisionHandler(circles, rectangles);

		BeginDrawing();
			ClearBackground(BLACK);

			rect1.Draw();
			for(int i = 0; i < circles.size(); i++){
				circles[i]->Draw();
			}
			for(int i = 0; i < rectangles.size(); i++){
				rectangles[i]->Draw();
			}

		EndDrawing();
	}

	CloseWindow();
}

