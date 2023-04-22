#include "Game.h"
#include "Actor.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SpriteComp.h"
#include "TextComponent.h"
#include "Grid.h"
#include "UI.h"
#include "Player.h"
#include "Unit.h"

namespace Engine {

	Game::Game() : m_Window(nullptr), m_Running(true)
	{

	}

	bool Game::Start() {
		int sdlResult = SDL_Init(SDL_INIT_VIDEO);
		srand(time(0));

		if (sdlResult != 0) {
			SDL_Log("Can't Start!: %s", SDL_GetError());
			return false;
		}

		// Title, WindowX, WindowY, Width, Height, 0
		m_Window = SDL_CreateWindow(
			"Ghost Hex", 100, 100, 1152, 720, 0);

		if (!m_Window) {
			SDL_Log("Can't Make Window!!: %s", SDL_GetError());
			return false;
		}

		m_Render = SDL_CreateRenderer(
			m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (IMG_Init(IMG_INIT_PNG) == 0) {
			SDL_Log("SDL_Image Don't Work: %s: ", SDL_GetError());
			return false;
		}

		if (TTF_Init() < 0) {
			SDL_Log("Font issues: %s", TTF_GetError());
			return false;
		}

		LoadData();

		m_TicksCount = SDL_GetTicks();
		return true;
	}

	void Game::End() {

		UnloadData();
		IMG_Quit();

		SDL_DestroyRenderer(m_Render);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Game::AddActor(Actor* actor) {

		if (m_UpdatingActors) {
			m_PendingActors.emplace_back(actor);
		}
		else {
			m_Actors.emplace_back(actor);
		}
	}

	void Game::RemoveActor(Actor* actor) {
		auto iter = std::find(m_PendingActors.begin(), m_PendingActors.end(), actor);
		if (iter != m_PendingActors.end()) {
			std::iter_swap(iter, m_PendingActors.end() - 1);
			m_PendingActors.pop_back();
		}

		auto itera = std::find(m_Actors.begin(), m_Actors.end(), actor);
		if (itera != m_Actors.end()) {
			std::iter_swap(itera, m_Actors.end() - 1);
			m_Actors.pop_back();
		}
	}

	void Game::AddSprite(SpriteComp* sprite)
	{
		int myDrawOrder = sprite->GetDrawOrder();
		auto iter = m_Sprites.begin();
		for (; iter != m_Sprites.end(); ++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		m_Sprites.insert(iter, sprite);
	}

	void Game::RemoveSprite(SpriteComp* sprite)
	{
		auto iter = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);
		m_Sprites.erase(iter);
	}

	void Game::AddText(TextComponent* sprite)
	{
		int myDrawOrder = sprite->GetDrawOrder();
		auto iter = m_Texts.begin();
		for (; iter != m_Texts.end(); ++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder())
			{
				break;
			}
		}

		m_Texts.insert(iter, sprite);
	}

	void Game::RemoveText(TextComponent* sprite)
	{
		auto iter = std::find(m_Texts.begin(), m_Texts.end(), sprite);
		m_Texts.erase(iter);
	}

	SDL_Texture* Game::GetTexture(const std::string& fileName)
	{
		SDL_Texture* tex = nullptr;
		auto iter = m_Textures.find(fileName);
		if (iter != m_Textures.end()) {
			tex = iter->second;
		}
		else {
			SDL_Surface* surf = IMG_Load(fileName.c_str());
			if (!surf) {
				SDL_Log("Can't load: %s: ", SDL_GetError());
				return nullptr;
			}

			tex = SDL_CreateTextureFromSurface(m_Render, surf);
			SDL_FreeSurface(surf);

			if (!tex) {
				SDL_Log("Can't Make Surface: %s: ", SDL_GetError());
				return nullptr;
			}

			m_Textures.emplace(fileName.c_str(), tex);
		}

		return tex;
	}
	
	void Game::RunLoop() {
		while (m_Running) {
			GetInputs();
			UpdateGame();
			GetOutput();
		}
	}

	void Game::GetInputs() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				m_Running = false;
				break;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_ESCAPE]) {
			m_Running = false;
		}

		if (m_Turn == Turn::PLAYER) {

			if (state[SDL_SCANCODE_R]) {
				if (cooldown < 0) {
					m_Turn = Turn::ENEMY;
					cooldown = 90;
				}
			}

			if (state[SDL_SCANCODE_1]) {
				m_Grid->SetBType(Grid::ENeCrow);
				m_Select->SetPos(Vector2(51, 670));
				m_Grid->setGridPrice(50);
			}

			if (state[SDL_SCANCODE_2]) {
				m_Grid->SetBType(Grid::ECrow);
				m_Select->SetPos(Vector2(128, 670));
				m_Grid->setGridPrice(300);
			}

			if (state[SDL_SCANCODE_3]) {
				m_Grid->SetBType(Grid::ETomb);
				m_Select->SetPos(Vector2(205, 670));
				m_Grid->setGridPrice(300);
			}

			if (state[SDL_SCANCODE_4]) {
				m_Grid->SetBType(Grid::EGhost);
				m_Select->SetPos(Vector2(282, 670));
				m_Grid->setGridPrice(100);
			}

			if (state[SDL_SCANCODE_5]) {
				m_Grid->SetBType(Grid::EFire);
				m_Select->SetPos(Vector2(380, 670));
				m_Grid->setGridPrice(400);
			}

			int x, y;
			Uint8 buttons = SDL_GetMouseState(&x, &y);
			if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT) {
				m_Grid->CheckClick(x, y);
			}

			if (state[SDL_SCANCODE_B]) {
				if (m_Grid->getBType() != Grid::EDef && m_Human->GetSpirit() >= m_Grid->getGridPrice()) {
					m_Grid->BuildUnit();
					m_Grid->addEnemyToList(m_AI);
					m_HumanSpirit->UpdateText(std::to_string(m_Human->GetSpirit()));
				}
			}
		}

		m_UpdatingActors = true;
		for (auto actor : m_Actors) {
			actor->ProcessInput(state);
		}
	}

	void Game::UpdateGame() {

		while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 16));

		WaitForNext = false;
		--cooldown;

		float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;
		m_TicksCount = SDL_GetTicks();

		if (deltaTime > 0.05f) {
			deltaTime = 0.05f;
		}

		m_UpdatingActors = true;
		for (auto actor : m_Actors)
		{
			actor->Update(deltaTime);
		}
		m_UpdatingActors = false;

		for (auto pending : m_PendingActors)
		{
			m_Actors.emplace_back(pending);
		}
		m_PendingActors.clear();

		std::vector<Actor*> deadActors;
		for (auto actor : m_Actors)
		{
			if (actor->GetState() == Actor::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}

		for (auto actor : deadActors)
		{
			delete actor;
		}

		if (m_Turn == Turn::ENEMY) {

			if (!once2) {
				if (m_AI->GetSpirit() > 50) {
					Grid::buildType whatB = m_AI->whatBuild();
					if (whatB != Grid::EDef) {
						m_Grid->BuildAI(whatB, m_AI->getOPos(), m_AI->getEPos(), m_AI, true);
						WaitForNext = true;
					}
				}
				once2 = true;
			}
			
			m_AISpirit->UpdateText(std::to_string(m_AI->GetSpirit()));
			if (!WaitForNext) {
				m_Turn = Turn::SHOOT;
				once2 = false;
			}
		}

		if (m_Turn == Turn::SHOOT) {

			if (!once) {
				for (Unit* u : m_Units) {
					m_Human->AddSpirit(u->DoTurn(false));
					m_AI->AddSpirit(u->DoTurn(true));
					m_HumanSpirit->UpdateText(std::to_string(m_Human->GetSpirit()));
					m_AISpirit->UpdateText(std::to_string(m_AI->GetSpirit()));
				}
				once = true;
			}

			if (m_Bullets.empty()) {
				//Check for Win or Lose.
				once = false;

				if (balance < 17 && balance > 0) {
					m_Turn = Turn::PLAYER;
					m_Human->AddSpirit(25);
					m_AI->AddSpirit(25);
					m_HumanSpirit->UpdateText(std::to_string(m_Human->GetSpirit()));
					m_AISpirit->UpdateText(std::to_string(m_AI->GetSpirit()));
				}
				else {
					Finish();
				}

				m_Dot->SetPos(Vector2(343 + (26 * balance), 27));

			}
		}

	}

	void Game::Finish() {
		m_Turn = Turn::END;

		m_Prices->SetPos(Vector2(10000, 10000));

		m_AISpirit->SetPos(Vector2(10000, 10000));

		m_HumanSpirit->SetPos(Vector2(576, 360));

		if (balance > 8) {
			m_HumanSpirit->UpdateText("You Win!");
		}
		else {
			m_HumanSpirit->UpdateText("You Lose!");
		}

	}


	void Game::GetOutput(){
		SDL_SetRenderDrawColor(
			m_Render,
			0,
			0,
			0, 
			1 
		);
		SDL_RenderClear(m_Render);

		if (m_Turn != Turn::END) {
			for (auto sprite : m_Sprites) {
				sprite->Draw(m_Render);
			}
		}

		for (auto text : m_Texts) {
			text->Draw(m_Render);
		}

		SDL_RenderPresent(m_Render);
	}


	void Game::LoadData()
	{
		m_Grid = new Grid(this);

		m_UI = new UI(this);

		m_Select = new Selector(this);

		m_Dot = new Dot(this);

		m_Human = new Player(this);
		m_Human->AddSpirit(100);
		m_Grid->SetPlayer(m_Human);

		m_AI = new Player(this);
		m_AI->AddSpirit(100);

		m_HumanSpirit = new TextPlate(this);
		m_HumanSpirit->SetPos(Vector2(130, 35));
		m_HumanSpirit->UpdateText(std::to_string(m_Human->GetSpirit()));

		m_AISpirit = new TextPlate(this);
		m_AISpirit->SetPos(Vector2(1010, 35));
		m_AISpirit->UpdateText(std::to_string(m_AI->GetSpirit()));

		m_Prices = new TextPlate(this);
		m_Prices->SetPos(Vector2(200, 610));
		m_Prices->IncreaseWidth(390);
		m_Prices->UpdateText(" 50 300 300 100 400");	

		m_Turn = Turn::PLAYER;
	}

	void Game::UnloadData()
	{
		while (!m_Actors.empty()) {
			delete m_Actors.back();
		}

		for (auto e : m_Textures) {
			SDL_DestroyTexture(e.second);
		}
		m_Textures.clear();
	}
}