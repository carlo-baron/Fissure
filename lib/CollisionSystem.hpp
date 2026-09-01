#pragma once
#include "../components/gameObject/GameObject.hpp"
#include "../components/collider/circleCollider/CircleCollider.hpp"
#include "../components/collider/rectangleCollider/RectangleCollider.hpp"
#include "ICollisionSystemListener.hpp"
#include <optional>
#include <set>
#include <utility>
#include <vector>

using namespace std;

/**
 * @brief Detects collisions between every pair of objects and resolves them.
 *
 * All overlap detection and response lives here: CollisionHandler()
 * tests each unordered pair once per frame, dispatches to the resolver
 * matching the pair's shapes, applies the returned MTV to push the two
 * colliders apart, and fires collision enter/exit events through the
 * colliders' listeners (the Observer pattern — see ICollider).
 *
 * The resolver functions are pure detectors: they return the correction
 * as an optional<Vector2> instead of applying it, so the response
 * (which collider moves, what events fire) stays the system's decision
 * and the math stays free of side effects.
 */
class CollisionSystem{
	private:
		vector<ICollisionSystemListener*> listeners;
		vector<GameObject*> gameObjects;
		set<pair<ICollider*, ICollider*>> activeCollisions;
		/**
		 * @brief Records a pair as currently colliding.
		 * @return True or False if the pair is newly inserted.
		 */
		bool AddActiveColliders(ICollider* colliderA, ICollider* colliderB);
		/**
		 * @brief Removes a pair from the active set.
		 * @return Number of pairs removed — nonzero means the pair had been colliding.
		 */
		int RemoveActiveColliders(ICollider* colliderA, ICollider* colliderB);
		/**
		 * @brief Applies one pair's collision result: MTV correction plus enter/exit events.
		 *
		 * On overlap: Notifies its listeners about the collision, then record
		 * the pair in activeCollisions and fires OnCollisionEnter on both colliders —
		 * every frame the overlap persists. On separation: fires OnCollisionExit on both,
		 * but only if the pair was recorded as colliding. The set's erase
		 * returns nonzero only the first time, so exit fires exactly once
		 * per contact, and never for pairs that never collided.
		 *
		 * @param colliderA One collider of the pair (also the first to get events).
		 * @param colliderB The other collider of the pair.
		 * @param mtv The separation vector from the resolver, or nullopt when not overlapping.
		 */
		void NotifyListeners(ICollider* colliderA, ICollider* colliderB, optional<Vector2> mtv);

	public:
		/**
		 * @brief Creates the system over the given set of objects.
		 *
		 * The objects are tested for collisions every time
		 * CollisionHandler() is called.
		 * @param gameObjects The objects to test. Non-owning.
		 */
		CollisionSystem(vector<GameObject*> gameObjects);

		/**
		 * @brief Runs collision detection and response for every pair of objects, once per frame.
		 *
		 * Tests each unordered pair of colliders exactly once (i < j) and
		 * dispatches to the resolver matching the pair's ShapeTypes. For
		 * overlapping pairs the MTV is added to the mover's position
		 * (pushing the shapes apart) and OnCollisionEnter is fired on both
		 * colliders every frame the overlap persists; pairs that were
		 * colliding but no longer overlap fire OnCollisionExit exactly
		 * once (see ResolveCollision()).
		 */
		void CollisionHandler();

		/**
		 * @brief Detects an overlap between two circles and computes the separation vector.
		 *
		 * @param circleA First circle.
		 * @param circleB Second circle.
		 * @return If overlapping and both enabled: the minimum translation
		 * vector along the line between the centers, pointing from
		 * circleA toward circleB — meant to be added to circleB's (the
		 * second collider's) position. Otherwise nullopt.
		 */
		optional<Vector2> CircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB);

		/**
		 * @brief Detects an overlap between a circle and a rectangle and computes the separation vector.
		 *
		 * Finds the point of the rectangle closest to the circle's center
		 * and treats that as the contact point.
		 *
		 * @param circle The circle.
		 * @param rect The rectangle.
		 * @return If overlapping and both enabled: the minimum translation
		 * vector pushing the circle out of the rectangle (from the closest
		 * rectangle point toward the circle's center), meant to be added
		 * to the circle's position. Otherwise nullopt.
		 */
		optional<Vector2> CircleRectangleCollision(CircleCollider* circle, RectangleCollider* rect);

		/**
		 * @brief Detects an overlap between two rectangles and computes the separation vector.
		 *
		 * Axis-aligned (AABB) test: the MTV runs along the axis of least
		 * penetration, directed by comparing the rectangles' centers.
		 *
		 * @param rectA First rectangle.
		 * @param rectB Second rectangle.
		 * @return If overlapping and both enabled: the minimum translation
		 * vector, meant to be added to rectA's (the first collider's)
		 * position. Otherwise nullopt.
		 */
		optional<Vector2> RectangleRectangleCollision(RectangleCollider* rectA, RectangleCollider* rectB);

		void AddListener(ICollisionSystemListener* listener);
		void NotifyListenersEnter(ICollider* colliderA, ICollider* colliderB, Vector2 mtv);
		void NotifyListenersStay(ICollider* colliderA, ICollider* colliderB, Vector2 mtv);
		void NotifyListenersExit(ICollider* colliderA, ICollider* colliderB);
};
