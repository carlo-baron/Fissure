#include "raylib.h"
#include <memory>
#include "../components/circle/Circle.hpp"
#include "../components/circle/CircleRenderer.hpp"
#include "../components/transform/GameTransform.hpp"
#include "../components/gameObject/GameObject.hpp"

using namespace std;

int main(){
	InitWindow(500, 500, "Collision Detector");
	SetTargetFPS(60);

	Vector2 center = {
		GetScreenWidth() / 2.0f,
		GetScreenHeight() / 2.0f
	};

	Circle mouseCircle(10, {0, 0});

	//make factory for this after making a rectangle shape
	unique_ptr<GameTransform> transform =
		make_unique<GameTransform>(center);
	unique_ptr<CircleRenderer> circleRenderer =
		make_unique<CircleRenderer>(transform.get(), 50);
	GameObject circleObject(std::move(transform), std::move(circleRenderer));

	while(!WindowShouldClose()){
		Vector2 mousePos = GetMousePosition();
		mouseCircle.SetPosition(mousePos);

		//handle circle collision
		// CollisionHandler(circles, rectangles); // modify by getting gameObject

		BeginDrawing();
			ClearBackground(BLACK);

			circleObject.Update();
			mouseCircle.Draw();

		EndDrawing();
	}

	CloseWindow();
}

