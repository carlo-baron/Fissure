#pragma once
#include "../components/gameObject/GameObject.hpp"
#include "../components/collider/circleCollider/CircleCollider.hpp"
#include "../components/collider/rectangleCollider/RectangleCollider.hpp"
#include <optional>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class CollisionSystem{
	private:
		set<pair<ICollider*, ICollider*>> activeCollisions;

	public:
	void CollisionHandler(vector<GameObject*> gameObject);
	optional<Vector2> CircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB);
	optional<Vector2> CircleRectangleCollision(CircleCollider* circle, RectangleCollider* rect);
	optional<Vector2> RectangleRectangleCollision(RectangleCollider* rectA, RectangleCollider* rectB);

	bool WasActive(ICollider* colliderA, ICollider* colliderB);
	void AddActiveColliders(ICollider* colliderA, ICollider* colliderB);
	int RemoveActiveColliders(ICollider* colliderA, ICollider* colliderB);
	void ResolveCollision(ICollider* mover, ICollider* colliderA, ICollider* colliderB, optional<Vector2> mtv);
};
