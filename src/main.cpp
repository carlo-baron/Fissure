#include "raylib.h"
#include <charconv>
#include <string>
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

	// Factory
	GameObjectFactory gameObjectFactory;

	// Game Objects
	GameObject dummyCircle = gameObjectFactory.CircleObject({ center.x, 70 }, 50);
	GameObject mouseObject = gameObjectFactory.CircleObject({0, 0}, 20);
	GameObject rectangleObject = gameObjectFactory.RectangleObject(center, 100, 100);

	vector<GameObject*> gameObjects;
	gameObjects.push_back(&dummyCircle);
	gameObjects.push_back(&mouseObject);
	gameObjects.push_back(&rectangleObject);

	// Systems
	CollisionSystem collisionSystem(gameObjects);
	PhysicsSystem physicsSystem(gameObjects);
	
	// Variables
	float speed = 30.0f;
	auto recRb = rectangleObject.GetRigidbody();
	auto dummyRb = dummyCircle.GetRigidbody();

	while(!WindowShouldClose()){
		Vector2 mousePos = GetMousePosition();
		mouseObject.GetGameTransform()->SetPosition(mousePos);
		int fps = GetFPS();

		collisionSystem.CollisionHandler();
		physicsSystem.PhysicsHandler();

		if(recRb){
			rectangleObject.GetRigidbody()->SetGravity(0);
		}

		if(dummyRb){
			dummyCircle.GetRigidbody()->SetMass(5);
		}

		BeginDrawing();
			ClearBackground(BLACK);

			DrawText(to_string(fps).c_str(), 465, 5, 24, GREEN);

			dummyCircle.Draw();
			rectangleObject.Draw();
			mouseObject.Draw();

		EndDrawing();
	}

	CloseWindow();
}

