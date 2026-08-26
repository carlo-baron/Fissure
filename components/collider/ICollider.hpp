#pragma once

#include "IDrawable.hpp"
class ICollider{
	public:
		virtual bool IsEnabled() const = 0;
		virtual void SetEnabled(bool enabled) = 0;
		virtual IDrawable* GetDrawable() const = 0;

		virtual ~ICollider() {};
};
