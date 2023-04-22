#include "MoveComponent.h"
#include "CustomMath.h"
#include "Actor.h"

namespace Engine
{
	MoveComponent::MoveComponent(Actor* owner, int updateOrder) :
		Component(owner, updateOrder),
		m_AngularSpeed(0.0f),
		m_ForwardSpeed(0.0f)
	{
	}

	void MoveComponent::Update(float deltaTime)
	{
		if (!CustomMath::NearZero(m_AngularSpeed))
		{
			float rot = m_Owner->GetRota();
			rot += m_AngularSpeed * deltaTime;
			m_Owner->SetRota(rot);
		}

		if (!CustomMath::NearZero(m_ForwardSpeed))
		{
			Vector2 pos = m_Owner->GetPos();
			pos += m_Owner->GetForward() * m_ForwardSpeed * deltaTime;

			m_Owner->SetPos(pos);
		}
	}
}