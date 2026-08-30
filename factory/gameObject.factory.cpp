#include "gameObject.factory.hpp"
#include <memory>
#include <raylib.h>
#include "../components/transform/GameTransform.hpp"
#include "../components/collider/circleCollider/CircleCollider.hpp"
#include "../components/collider/rectangleCollider/RectangleCollider.hpp"
#include "../components/circle/CircleRenderer.hpp"
#include "../components/gameObject/GameObject.hpp"
#include "../components/rectangle/RectangleRenderer.hpp"

using namespace std;

GameObjectFactory::GameObjectFactory(){}

GameObject GameObjectFactory::CircleObject(Vector2 position, float radius){
	unique_ptr<GameTransform> transform =
		make_unique<GameTransform>(position);
	unique_ptr<CircleRenderer> circleRenderer =
		make_unique<CircleRenderer>(transform.get(), radius);
	unique_ptr<CircleCollider> circleCollider =
		make_unique<CircleCollider>(transform.get(), radius, true);
	unique_ptr<Rigidbody> rb = make_unique<Rigidbody>();

	GameObject circleObject(
			std::move(transform),
			std::move(circleRenderer),
			std::move(circleCollider),
			std::move(rb)
		);

	return circleObject;
}

GameObject GameObjectFactory::RectangleObject(Vector2 position, float width, float height){
	unique_ptr<GameTransform> transform =
		make_unique<GameTransform>(position);

	unique_ptr<RectangleRenderer> rectangleRenderer =
		make_unique<RectangleRenderer>(transform.get(), width, height);

	unique_ptr<RectangleCollider> rectangleCollider =
		make_unique<RectangleCollider>(transform.get(), width, height, true);

	unique_ptr<Rigidbody> rb = make_unique<Rigidbody>();

	GameObject rectangleObject(
			std::move(transform),
			std::move(rectangleRenderer),
			std::move(rectangleCollider),
			std::move(rb)
		);

	return rectangleObject;
}
