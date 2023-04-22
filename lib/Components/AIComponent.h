#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>

namespace Engine
{
	class AIComponent : public Component
	{
	public:
		AIComponent(class Actor* owner);

		void Update(float deltaTime) override;
		void ChangeState(const std::string& name);

		void RegisterState(class AIState* state);
	private:
		// Diccionario para relacionar el nombre del estado con el objeto AIState
		std::unordered_map<std::string, class AIState*> m_StateMap;
		class AIState* m_CurrentState;
	};
}