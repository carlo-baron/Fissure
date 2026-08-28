#include "gameObject.factory.hpp"
#include <memory>
#include "../components/transform/GameTransform.hpp"
#include "../components/collider/circleCollider/CircleCollider.hpp"
#include "../components/circle/CircleRenderer.hpp"
#include "../components/gameObject/GameObject.hpp"

using namespace std;

GameObjectFactory::GameObjectFactory(){}

GameObject GameObjectFactory::CircleObject(Vector2 position, float radius){
	unique_ptr<GameTransform> transform =
		make_unique<GameTransform>(position);
	unique_ptr<CircleRenderer> circleRenderer =
		make_unique<CircleRenderer>(transform.get(), radius);
	unique_ptr<CircleCollider> circleCollider =
		make_unique<CircleCollider>(transform.get(), radius, true);

	GameObject circleObject(std::move(transform), std::move(circleRenderer), std::move(circleCollider));

	return circleObject;
}
