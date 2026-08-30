#pragma once
#include "raylib.h"

/**
 * @brief Anything that can render itself with raylib.
 *
 * Exposes the drawable's color so that reactions (such as a custom
 * behaviour flashing red on collision) can restyle any IDrawable
 * without knowing its concrete type.
 */
class IDrawable{
	public:
		/**
		 * @brief Renders the component every frame.
		 */
		virtual void Draw() const = 0;

		/**
		 * @brief The color this drawable is currently rendered with.
		 */
		virtual Color GetColor() const = 0;
		/**
		 * @brief Sets the color used by Draw().
		 * @param color The new render color.
		 */
		virtual void SetColor(Color color) = 0;

		virtual ~IDrawable() {};
};
