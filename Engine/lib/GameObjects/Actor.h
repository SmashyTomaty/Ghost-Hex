#pragma once
#include "CustomMath.h"
#include <vector>

namespace Engine
{
	class Actor
	{
	public:
		enum State 
		{
			EActive,
			EPaused,
			EDead
		};

		Actor(class Game* game);
		virtual ~Actor();

		void Update(float deltaTime);
		void UpdateComponents(float deltaTime);
		// Actor Specific Code
		virtual void UpdateActor(float deltaTime);

		void ProcessInput(const uint8_t* keyState);
		virtual void ActorInput(const uint8_t* keyState);

		const Vector2& GetPos() const { return m_Position; }
		void SetPos(const Vector2& pos) { m_Position = pos; }
		float GetScale() const { return m_Scale; }
		void SetScale(float scale) { m_Scale = scale; }
		float GetRota() const { return m_Rotation; }
		void SetRota(float rotation) { m_Rotation = rotation; }

		Vector2 GetForward()
		{
			return Vector2(CustomMath::Cos(m_Rotation),
				-CustomMath::Sin(m_Rotation));
		}

		State GetState() const { return m_State; }
		void SetState(State state) { m_State = state; }

		class Game* GetGame() { return m_Game; }

		void AddComponent(class Component* component);
		void RemoveComponent(class Component* component);

	private:
		State m_State;

		Vector2 m_Position;
		float m_Scale;
		float m_Rotation; //RADS

		std::vector<class Component*> m_Components;
		class Game* m_Game;
	};
}