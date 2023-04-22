#pragma once
#include "Component.h"

namespace Engine {
	class MoveComponent : public Component 
	{
	public: 
		MoveComponent(class Actor* owner, int updateOrder = 10);
		void Update(float deltaTime) override;

		float getAngularSpeed() const { return m_AngularSpeed; }
		float getForwardSpeed() const { return m_ForwardSpeed; }
		void setAngularSpeed(float speed) { m_AngularSpeed = speed; }
		void setForwardSpeed(float speed) { m_ForwardSpeed = speed; }
	private:
		float m_AngularSpeed;
		float m_ForwardSpeed;
	};
}