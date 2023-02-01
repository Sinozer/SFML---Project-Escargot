#include "stdafx.h"

namespace Snail
{
	MainState::MainState(GameDataRef data) : m_data(data)
	{
		m_physicBodyManager = PhysicBodyManager(data);
	}

	void MainState::Init()
	{
		m_data->assetManager.LoadTexture("STATE_JOIN_BACKGROUND", STATE_JOIN_BACKGROUND_FILEPATH);
		m_background.setTexture(m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND"));

		m_player = Player(m_data);
		m_player.Init();

		m_physicBodyManager.AddPhysicBody("PLAYER", m_player.m_physicBodyRef);

		// ground
		m_physicBodyManager.AddPhysicBody("GROUND", PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(1000.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, 650.f), 1.f, true
		)));

		// dummy box
		m_physicBodyManager.AddPhysicBody("BOX", PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(100.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 4.f), 0.f, false
		)));
	}

	void MainState::HandleInput()
	{
		sf::Event event;

		while (m_data->window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				m_data->window.close();
				break;
			}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_data->stateManager.RemoveState();

		m_player.HandleInput();
	}

	void MainState::Update(float dt)
	{
		m_physicBodyManager.Update(dt);
		m_player.Update(dt);
	}

	void MainState::Draw(float dt)
	{
		m_data->window.draw(m_background);
		if (!m_physicBodyManager.IsEmpty())
			m_physicBodyManager.Draw();
	}
}