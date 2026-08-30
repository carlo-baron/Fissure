#pragma once

#include "IDrawable.hpp"
#include "raylib.h"
#include "ICollisionListener.hpp"

enum class ShapeType { Circle, Rectangle };

/**
 * @brief A collision shape attached to a GameObject.
 *
 * Colliders are detected against each other by CollisionSystem, and
 * each collider is also the Subject of the collision Observer pattern:
 * when CollisionSystem decides a collision started or ended it calls
 * OnCollisionEnter/OnCollisionExit here, and the collider fans the
 * event out to every registered ICollisionListener (PhysicsSystem for
 * momentum resolution, custom behaviours for gameplay reactions, ...).
 */
class ICollider{
	public:
		/**
		 * @brief Whether this collider currently takes part in collision detection.
		 */
		virtual bool IsEnabled() const = 0;
		/**
		 * @brief Enables or disables collision detection for this collider.
		 *
		 * Disabled colliders are skipped entirely by CollisionSystem's
		 * resolver functions — they neither produce nor react to overlaps.
		 * @param enabled The new enabled state.
		 */
		virtual void SetEnabled(bool enabled) = 0;
		/**
		 * @brief This collider as a drawable, used to render its debug outline.
		 *
		 * A collider needs no separate debug-draw component: it implements
		 * IDrawable itself and returns itself here. GameObject::Draw()
		 * draws this outline, which is only visible while the collider's
		 * internal show flag is set.
		 */
		virtual IDrawable* GetDrawable() const = 0;

		/**
		 * @brief The collider's position, read from the transform it was built with.
		 */
		virtual Vector2 GetPosition() const = 0;
		/**
		 * @brief Moves the collider by writing to its shared transform (moving the whole object).
		 * @param position The new position.
		 */
		virtual void SetPosition(Vector2 position) = 0;

		/**
		 * @brief The shape of this collider, used by CollisionSystem to pick a resolver.
		 *
		 * Collision detection lives in CollisionSystem and dispatches on
		 * the shape pair (Circle/Rectangle combinations) instead of each
		 * collider implementing CollideWith() against every other shape.
		 * That keeps all collision math in one place: adding a new shape
		 * means adding one resolver to CollisionSystem, and existing
		 * collider classes stay untouched.
		 */
		virtual ShapeType GetShapeType() const = 0;
		/**
		 * @brief Notifies all registered listeners that a collision with other has started.
		 *
		 * Called by CollisionSystem — never by the collider itself —
		 * every frame the overlap persists. The collider forwards the
		 * event to its listeners.
		 * @param self This collider, i.e. the one the listener was registered on.
		 * @param other The collider that collided with self.
		 */
		virtual void OnCollisionEnter(ICollider* self, ICollider* other) const = 0;
		/**
		 * @brief Notifies all registered listeners that a collision with other has ended.
		 *
		 * Called by CollisionSystem exactly once per contact, when a
		 * previously colliding pair no longer overlaps (see
		 * CollisionSystem's active-collision tracking).
		 * @param self This collider, i.e. the one the listener was registered on.
		 * @param other The collider that collided with self.
		 */
		virtual void OnCollisionExit(ICollider* self, ICollider* other) const = 0;
		/**
		 * @brief Registers a listener to be notified on collision enter/exit.
		 * @param listener The listener to notify. Non-owning.
		 */
		virtual void AddListener(ICollisionListener* listener) = 0;

		virtual ~ICollider() {};
};
