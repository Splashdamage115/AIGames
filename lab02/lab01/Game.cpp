#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "RenderObject.h"

float Game::deltaTime = 0.f;
sf::Font Game::m_jerseyFont;

Game::Game()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf")) std::cout << "problem loading arial black font" << std::endl;

	RenderObject::getInstance().start();
	srand(static_cast<unsigned int>(time(nullptr)));
	m_player.start();

	for (int i = 0; i < 5; i++)
	{
		m_npcs.emplace_back();
		m_npcActive.emplace_back();
		m_npcActive.at(i) = true;
	}
	m_npcs.at(0).start(NPC::MoveState::wander, { 300.0f, 600.0f });
	m_npcs.at(1).start(NPC::MoveState::seek,   { 600.0f, 300.0f });
	m_npcs.at(2).start(NPC::MoveState::pursue, { 800.0f, 600.0f });
	m_npcs.at(3).start(NPC::MoveState::arrive, { 900.0f, 100.0f });
	m_npcs.at(4).start(NPC::MoveState::arrive, { 900.0f, 800.0f });

	m_npcs.at(0).changeMoveSpeed(500.0f);
	m_npcs.at(4).changeMaxMoveSpeed(400.0f);
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (RenderObject::getInstance().getWindow().isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame.asSeconds()); //60 fps
		}
		RenderObject::getInstance().render();
	}
}

void Game::processEvents()
{
	while (const std::optional newEvent = RenderObject::getInstance().getWindow().pollEvent())
	{
		if (newEvent->is<sf::Event::Closed>())
		{
			RenderObject::getInstance().closeWindow();
		}
		if (newEvent->is<sf::Event::KeyReleased>() || newEvent->is<sf::Event::KeyPressed>()) //user pressed or released a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	if (const auto* keyPressed = t_event->getIf<sf::Event::KeyReleased>())
	{
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num1)
		{
			changeNPC(0);
		}
		else if (keyPressed->scancode == sf::Keyboard::Scancode::Num2)
		{
			changeNPC(1);
		}
		else if (keyPressed->scancode == sf::Keyboard::Scancode::Num3)
		{
			changeNPC(2);
		}
		else if (keyPressed->scancode == sf::Keyboard::Scancode::Num4)
		{
			changeNPC(3);
		}
		else if (keyPressed->scancode == sf::Keyboard::Scancode::Num5)
		{
			changeNPC(4);
		}
	}
}

void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		RenderObject::getInstance().closeWindow();
	}
}

void Game::update(float t_deltaTime)
{
	Game::deltaTime = t_deltaTime;
	checkKeyboardState();

	m_player.update();
	for (int i = 0; i < 5; i++)
	{
		if(m_npcActive.at(i))
			m_npcs.at(i).update(m_player.getPosition(), m_player.getAngle(), m_player.getSpeed());
	}
}

void Game::changeNPC(int t_num)
{
	if (m_npcActive.at(t_num))
	{
		m_npcs.at(t_num) = NPC();
		m_npcActive.at(t_num) = false;
	}
	else
	{
		switch (t_num)
		{
		case 0:
			m_npcs.at(t_num).start(NPC::MoveState::wander, { 300.0f, 600.0f });
			m_npcs.at(t_num).changeMoveSpeed(500.0f);
			break;
		case 1:
			m_npcs.at(t_num).start(NPC::MoveState::seek, { 600.0f, 300.0f });
			break;
		case 2:
			m_npcs.at(t_num).start(NPC::MoveState::pursue, { 800.0f, 600.0f });
			break;
		case 3:
			m_npcs.at(t_num).start(NPC::MoveState::arrive, { 900.0f, 100.0f });
			break;
		case 4:
			m_npcs.at(t_num).start(NPC::MoveState::arrive, { 900.0f, 800.0f });
			m_npcs.at(t_num).changeMaxMoveSpeed(400.0f);
			break;
		default:
			break;
		}
		m_npcActive.at(t_num) = true;
	}
}


