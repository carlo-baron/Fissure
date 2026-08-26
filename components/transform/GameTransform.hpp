#pragma once

#include "IGameTransform.hpp"

class GameTransform : public IGameTransform{
	private:
		Vector2 position;
		Vector2 rotation;
	  float scale;

	public:
		GameTransform(Vector2 position = {0, 0}, Vector2 rotation = {0, 0}, float scale = 1);

		Vector2 GetPosition() const override;
		void SetPosition(Vector2 position) override;

		Vector2 GetRotation() const override;
		void SetRotation(Vector2 rotation) override;

		float GetScale() const override;
		void SetScale(float scale) override;
};
