#include "CircleColider.h"
#include "Actor.h"

namespace Engine {
	CircleColider::CircleColider(Actor* owner) : Component(owner), m_Radius(0)
	{

	}

	float CircleColider::getRadius() const {
		return m_Radius * m_Owner->GetScale();
	}

	const Vector2& CircleColider::GetCenter() const {
		return m_Owner->GetPos();
	}

	bool CircleColider::Intersect(const CircleColider& a, const CircleColider& b)
	{
		Vector2 diff = a.GetCenter() - b.GetCenter();
		float distSq = diff.LengthSq();

		float radiiSq = a.getRadius() + b.getRadius();
		radiiSq *= radiiSq;

		return distSq <= radiiSq;
	}
}
