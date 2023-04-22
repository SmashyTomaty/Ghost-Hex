#include "AIState.h"
#include "AIComponent.h"
#include "SDL_log.h"

// Didn't really need a state machine for this, 
// since the game is turn based. 
// Leaving this here for posterity.

namespace Engine
{
	void AIPatrol::Update(float deltaTime)
	{
		SDL_Log("Updating %s state", GetName());
		bool dead = true;
		if (dead)
		{
			m_Owner->ChangeState("Death");
		}
	}

	void AIPatrol::OnEnter()
	{
		SDL_Log("Entering %s state", GetName());
	}

	void AIPatrol::OnExit()
	{
		SDL_Log("Exiting %s state", GetName());
	}

	void AIDeath::Update(float deltaTime)
	{
		SDL_Log("Updating %s state", GetName());
	}

	void AIDeath::OnEnter()
	{
		SDL_Log("Entering %s state", GetName());
	}

	void AIDeath::OnExit()
	{
		SDL_Log("Exiting %s state", GetName());
	}

	void AIAttack::Update(float deltaTime)
	{
		SDL_Log("Updating %s state", GetName());
	}

	void AIAttack::OnEnter()
	{
		SDL_Log("Entering %s state", GetName());
	}

	void AIAttack::OnExit()
	{
		SDL_Log("Exiting %s state", GetName());
	}
}