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
	
	// Game Objects
	GameObject mouseObject = gameObjectFactory.CircleObject({0, 0}, 20);
	GameObject rectangleObject = gameObjectFactory.RectangleObject(center, 50, 50);

	vector<GameObject*> gameObjects;
	gameObjects.push_back(&mouseObject);
	gameObjects.push_back(&rectangleObject);


	while(!WindowShouldClose()){
		Vector2 mousePos = GetMousePosition();
		mouseObject.GetGameTransform()->SetPosition(mousePos);

		CollisionHandler(gameObjects);

		BeginDrawing();
			ClearBackground(BLACK);

			rectangleObject.Update();
			mouseObject.Update();

		EndDrawing();
	}

	CloseWindow();
}

