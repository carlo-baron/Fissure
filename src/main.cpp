#include "raylib.h"
#include <vector>
#include "../components/gameObject/GameObject.hpp"
#include "../lib/CollisionHandler.hpp"
#include "../lib/physics/PhysicsHandler.hpp"
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
	GameObject dummyCircle = gameObjectFactory.CircleObject({ center.x, 70 }, 50);
	GameObject mouseObject = gameObjectFactory.CircleObject({0, 0}, 20);
	GameObject rectangleObject = gameObjectFactory.RectangleObject(center, 100, 100);

	vector<GameObject*> gameObjects;
	gameObjects.push_back(&dummyCircle);
	gameObjects.push_back(&mouseObject);
	gameObjects.push_back(&rectangleObject);


	while(!WindowShouldClose()){
		Vector2 mousePos = GetMousePosition();
		mouseObject.GetGameTransform()->SetPosition(mousePos);

		CollisionHandler(gameObjects);
		PhysicsHandler(gameObjects);

		BeginDrawing();
			ClearBackground(BLACK);

			dummyCircle.Update();
			rectangleObject.Update();
			mouseObject.Update();

		EndDrawing();
	}

	CloseWindow();
}

