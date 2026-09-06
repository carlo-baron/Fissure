#include "../Fissure/Fissure.hpp"
#include "rectangle/RectangleBehaviour.hpp"
#include <string>
#include "raylib.h"

using namespace std;

int main(){
	InitWindow(500, 500, "Fissure");
	SetTargetFPS(60);

	Vector2 center = {
		GetScreenWidth() / 2.0f,
		GetScreenHeight() / 2.0f
	};

	// Game Objects
	unique_ptr<GameTransform> transform =
		make_unique<GameTransform>(Vector2{center.x, 0});
	unique_ptr<CircleRenderer> circleRenderer =
		make_unique<CircleRenderer>(transform.get(), 50);
	unique_ptr<CircleCollider> circleCollider =
		make_unique<CircleCollider>(transform.get(), 50);
	unique_ptr<Rigidbody> rb = make_unique<Rigidbody>();
	rb->SetVelocity(Vector2{0, 0});
	rb->SetBounciness(0);
	rb->SetMass(20);

	unique_ptr< GameObject > circleObject = make_unique<GameObject>(
			std::move(transform),
			std::move(circleRenderer),
			std::move(circleCollider),
			std::move(rb)
		);

	unique_ptr<GameTransform> transform1 =
		make_unique<GameTransform>(center, Vector2{25, 25}); // 50 is width and height

	unique_ptr<RectangleRenderer> rectangleRenderer =
		make_unique<RectangleRenderer>(transform1.get(), 50, 50);

	unique_ptr<RectangleCollider> rectangleCollider =
		make_unique<RectangleCollider>(transform1.get(), 50, 50);

	unique_ptr<Rigidbody> rbRect = make_unique<Rigidbody>();
	rbRect->SetType(RigidbodyType::Static);
	rbRect->SetGravity(0);
	rbRect->SetVelocity(Vector2{0, 0});

	unique_ptr<RectangleBehaviour> rectBehaviour = make_unique<RectangleBehaviour>();

	vector<unique_ptr<ICustomBehaviour>> rectangleBehaviours;
	rectangleBehaviours.push_back(std::move(rectBehaviour));

	unique_ptr<GameObject> rectangleObject = make_unique<GameObject>(
			std::move(transform1),
			std::move(rectangleRenderer),
			std::move(rectangleCollider),
			std::move(rbRect),
			std::move(rectangleBehaviours)
		);

	GameWorld world;
	world.AddObject(std::move(circleObject));
	world.AddObject(std::move(rectangleObject));
	
	while(!WindowShouldClose()){
		int fps = GetFPS();

		BeginDrawing();
			ClearBackground(BLACK);

			DrawText(to_string(fps).c_str(), 465, 5, 24, GREEN);

			world.Update();

			EndDrawing();
	}

	CloseWindow();
}

