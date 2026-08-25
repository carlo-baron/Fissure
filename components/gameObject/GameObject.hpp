#pragma once
#include <memory>
#include "../transform/IGameTransform.hpp"
#include "../IDrawable.hpp"

using namespace std;

class GameObject{
	private:
		unique_ptr<IGameTransform> transform;
		unique_ptr<IDrawable> drawable;

	public:
		GameObject(unique_ptr<IGameTransform> transform, unique_ptr<IDrawable> drawable);

		IGameTransform* GetGameTransform();

		IDrawable* GetDrawable();

		void Update();
};
