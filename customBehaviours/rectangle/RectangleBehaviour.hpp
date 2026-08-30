#pragma once
#include "../../components/ICustomBehaviour.hpp"
#include "../../components/collider/ICollisionListener.hpp"
#include "../../components/gameObject/GameObject.hpp"

/**
 * @brief Sample custom behaviour: flashes the object red while it is colliding.
 *
 * Demonstrates both halves of the ICustomBehaviour pattern: holding the
 * owning GameObject* (delivered by Start()) and reacting to collision
 * events as an ICollisionListener registered on the owner's collider.
 */
class RectangleBehaviour : public ICustomBehaviour, public ICollisionListener{
	private:
		GameObject* gameObject;

	public:
		RectangleBehaviour();

		/**
		 * @brief Stores the owning GameObject and registers this behaviour as a collision listener.
		 *
		 * The GameObject* is saved for use by the collision callbacks;
		 * nothing here can run before Start(), which is exactly why the
		 * owner is delivered this way rather than through the constructor.
		 * @param gameObject The owning GameObject. Non-owning.
		 */
		void Start(GameObject* gameObject) override;

		/**
		 * @brief Called every frame by GameObject::Update(); this sample has no per-frame logic.
		 */
		void Update() override;

		/**
		 * @brief Collision reaction: sets the owner's drawable color to RED.
		 * @param self The owner's collider that fired the event.
		 * @param other The collider it collided with.
		 */
		void OnCollisionEnter(ICollider* self, ICollider* other) const override;
		/**
		 * @brief Collision reaction: sets the owner's drawable color back to WHITE.
		 * @param self The owner's collider that fired the event.
		 * @param other The collider it collided with.
		 */
		void OnCollisionExit(ICollider* self, ICollider* other) const override;
};
