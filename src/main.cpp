#include "raylib.h"
#include <vector>
#include "../components/gameObject/GameObject.hpp"
#include "../lib/CollisionHandler.hpp"
#include "../factory/gameObject.factory.hpp"

using namespace std;

int main(){
	InitWindow(500, 500, "GeometryFPS");
	SetTargetFPS(60);

	Vector2 center = {
		GetScreenWidth() / 2.0f,
		GetScreenHeight() / 2.0f
	};

	GameObjectFactory gameObjectFactory;
	
	// circle dummy
	GameObject circleObject = gameObjectFactory.CircleObject(center, 50);

	// mouse circle
	GameObject mouseObject = gameObjectFactory.CircleObject({0, 0}, 20);

	vector<GameObject*> gameObjects;
	gameObjects.push_back(&mouseObject);
	gameObjects.push_back(&circleObject);


	while(!WindowShouldClose()){
		Vector2 mousePos = GetMousePosition();
		mouseObject.GetGameTransform()->SetPosition(mousePos);

		CollisionHandler(gameObjects);

		BeginDrawing();
			ClearBackground(BLACK);

			circleObject.Update();
			mouseObject.Update();

		EndDrawing();
	}

	CloseWindow();
}

