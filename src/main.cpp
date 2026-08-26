#include "collider/circleCollider/CircleCollider.hpp"
#include "raylib.h"
#include <utility>
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
	unique_ptr<CircleCollider> circleCollider =
		make_unique<CircleCollider>(transform.get(), circleRenderer->GetRadius(), true);

	GameObject circleObject(std::move(transform), std::move(circleRenderer), std::move(circleCollider));

	// mouse circle
	unique_ptr<GameTransform> transform0 =
		make_unique<GameTransform>();
	unique_ptr<CircleRenderer> circleRenderer0 =
		make_unique<CircleRenderer>(transform0.get(), 20);
	unique_ptr<CircleCollider> circleCollider0 =
		make_unique<CircleCollider>(transform0.get(), circleRenderer0->GetRadius(), true);

	GameObject mouseObject(std::move(transform0), std::move(circleRenderer0), std::move(circleCollider0));

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

