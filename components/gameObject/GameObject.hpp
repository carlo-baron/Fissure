#pragma once
#include <memory>
#include <vector>
#include "../transform/IGameTransform.hpp"
#include "../IDrawable.hpp"
#include "../collider/ICollider.hpp"
#include "../physics/Rigidbody.hpp"
#include "../ICustomBehaviour.hpp"
using namespace std;

/**
 * @brief Composition root: a game entity made of components.
 *
 * A GameObject owns at most one component of each kind — a transform and
 * a drawable (required), plus an optional collider, rigidbody and custom
 * behaviour — and owns them exclusively (unique_ptr). Components are
 * fetched through GetComponent<T>().
 */
class GameObject{
	private:
		unique_ptr<IGameTransform> transform;
		unique_ptr<IDrawable> drawable;
		unique_ptr<ICollider> collider;
		unique_ptr<Rigidbody> rigidbody;
		vector<unique_ptr<ICustomBehaviour>> customBehaviours;
		GameObject* parent = nullptr;
		vector<unique_ptr<GameObject>> children;

	public:
		/**
		 * @brief Assembles the object from its components, taking exclusive ownership of them.
		 *
		 * The optional components may be null — the object then simply
		 * doesn't collide, isn't simulated, or runs no custom logic. Once
		 * every component is in place the constructor calls
		 * customBehaviour->Start(this), which is how the behaviour learns
		 * its owner (see ICustomBehaviour::Start()).
		 *
		 * @param transform Position/rotation/scale of the object. Required.
		 * @param drawable How the object renders itself. Required.
		 * @param collider Collision shape. Optional — pass nullptr for none.
		 * @param rigidbody Mass/velocity data for the physics simulation. Optional.
		 * @param customBehaviour Optional per-object logic.
		 */
		GameObject(
			unique_ptr<IGameTransform> transform,
			unique_ptr<IDrawable> drawable,
			unique_ptr<ICollider> collider = nullptr,
			unique_ptr<Rigidbody> rigidbody = nullptr,
			vector<unique_ptr<ICustomBehaviour>> customBehaviours = {},
			GameObject* parent = nullptr,
			vector<unique_ptr<GameObject>> children = {}
		);
 
		/**
		 * @brief Renders the drawable, then the collider's debug outline if a collider is present.
		 */
		void Draw();
		/**
		 * @brief Runs the custom behaviour's per-frame update, if one is present.
		 */
		void Update();

		GameObject* GetParent();
		void SetParent(GameObject* parent);

		vector<GameObject*> GetChildren();
		void AddChild(unique_ptr<GameObject> child);
		void RemoveChild(GameObject* child);

		/**
		 * @brief Returns the requested component, or nullptr if the object doesn't have one.
		 *
		 * @tparam T The component interface to look up (IGameTransform,
		 * IDrawable, ICollider, Rigidbody or ICustomBehaviour). The
		 * specializations below map each interface to its member.
		 * @return A non-owning pointer to the component, or nullptr.
		 */
		template<typename T>
		T* GetComponent();
};


template<typename T>
T* GameObject::GetComponent() {
	if constexpr (std::is_base_of_v<ICustomBehaviour, T>) {
		for(auto& behaviour : customBehaviours) {
			if(auto* component = dynamic_cast<T*>(behaviour.get()))
				return component;
		}
	}

	return nullptr;
}

template<>
inline IGameTransform* GameObject::GetComponent<IGameTransform>() {
	return transform.get();
}

template<>
inline IDrawable* GameObject::GetComponent<IDrawable>() {
	return drawable.get();
}

template<>
inline ICollider* GameObject::GetComponent<ICollider>() {
	return collider.get();
}

template<>
inline Rigidbody* GameObject::GetComponent<Rigidbody>() {
	return rigidbody.get();
}
