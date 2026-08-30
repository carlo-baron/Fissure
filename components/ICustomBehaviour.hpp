#pragma once

class GameObject;

/**
 * @brief Optional per-object custom logic component.
 *
 * Unlike every other component, a behaviour is allowed to reach back
 * into its owning GameObject: custom logic usually needs to fetch
 * arbitrary components or register as a collision listener, so the
 * behaviour receives the owner via Start() rather than through its
 * constructor (see Start()).
 */
class ICustomBehaviour{
	public:
		/**
		 * @brief Initializes the behaviour with its owning GameObject.
		 *
		 * Called by the GameObject constructor once every component has
		 * been moved in and ownership is established. The owner cannot be
		 * passed to the behaviour's constructor: the GameObject creates
		 * and owns the behaviour, so the behaviour exists before the
		 * GameObject does (chicken-and-egg). Start() runs once all
		 * components are in place, which is also the right moment to
		 * fetch components via GetComponent() and to register as a
		 * collision listener.
		 *
		 * @param gameObject The owning GameObject. Non-owning — the
		 * GameObject outlives the behaviour it owns.
		 */
		virtual void Start(GameObject* gameObject) = 0;
		/**
		 * @brief Called once per frame by GameObject::Update().
		 */
		virtual void Update() = 0;

		~ICustomBehaviour(){}; 
};
