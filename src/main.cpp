#include "raylib.h"
#include <vector>
#include <memory>
#include "../components/circle/CircleRenderer.hpp"
#include "../components/transform/GameTransform.hpp"
#include "../components/gameObject/GameObject.hpp"
#include "../lib/CollisionHandler.hpp"

using namespace std;

int main(){
	InitWindow(500, 500, "GeometryFPS");
	SetTargetFPS(60);

	Vector2 center = {
		GetScreenWidth() / 2.0f,
		GetScreenHeight() / 2.0f
	};



	// make factory for this after making a rectangle shape
	
	// circle dummy
	unique_ptr<GameTransform> transform =
		make_unique<GameTransform>(center);
	unique_ptr<CircleRenderer> circleRenderer =
		make_unique<CircleRenderer>(transform.get(), 50);
	GameObject circleObject(std::move(transform), std::move(circleRenderer));

	// mouse circle
	unique_ptr<GameTransform> transform0 =
		make_unique<GameTransform>();
	unique_ptr<CircleRenderer> circleRenderer0 =
		make_unique<CircleRenderer>(transform0.get(), 20);
	GameObject mouseObject(std::move(transform0), std::move(circleRenderer0));

	vector<GameObject*> gameObjects;
	gameObjects.push_back(&mouseObject);
	gameObjects.push_back(&circleObject);


	while(!WindowShouldClose()){
		Vector2 mousePos = GetMousePosition();
		mouseObject.GetGameTransform()->SetPosition(mousePos);

		CollisionHandlerV2(gameObjects);

		BeginDrawing();
			ClearBackground(BLACK);

			circleObject.Update();
			mouseObject.Update();

		EndDrawing();
	}

	CloseWindow();
}

