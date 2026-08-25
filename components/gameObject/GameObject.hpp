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
		GameObject(unique_ptr<IGameTransform> transform, unique_ptr<IDrawable> drawable){
			this->transform = std::move(transform);
			this->drawable = std::move(drawable);
		}

		void Update(){
			drawable->Draw();
		}
};
