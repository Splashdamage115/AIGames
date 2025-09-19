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
	m_npc.start(NPC::MoveState::seek);
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
	m_npc.update(m_player.getPosition());
}


