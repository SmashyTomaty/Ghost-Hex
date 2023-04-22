#pragma once
#include <cstdint>

namespace Engine
{
	class Component
	{
	public:
		// Entre menor sea updateOrder, más pronto se actualiza el componente
		Component(class Actor* owner, int updateOrder = 100);
		virtual ~Component();
		virtual void Update(float deltaTime);
		virtual void ProcessInput(const uint8_t* keyState) {}

		int GetUpdateOrder() const { return m_UpdateOrder; }
	protected:
		class Actor* m_Owner;
		int m_UpdateOrder;
	};
}