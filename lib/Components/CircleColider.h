#pragma once
#include "Component.h"
#include "CustomMath.h"

namespace Engine 
{
	class CircleColider : public Component 
	{
	public:
		CircleColider(class Actor* owner);

		void SetRadius(float radius) { m_Radius = radius; }
		float getRadius() const;

		const Vector2& GetCenter() const;

		static bool Intersect(const CircleColider& a, const CircleColider& b);
	private:
		float m_Radius;
	};
}