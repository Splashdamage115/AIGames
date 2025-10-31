#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "RenderObject.h"

float Game::deltaTime = 0.f;
sf::Font Game::m_jerseyFont;
sf::Texture Game::m_ship;
sf::Vector2i Game::mousePosition = { 0,0 };

Game::Game()
{

	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf")) std::cout << "problem loading arial black font" << std::endl;
	if (!m_ship.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";


	RenderObject::getInstance().start();
	srand(static_cast<unsigned int>(time(nullptr)));
	m_instructions = std::make_shared<sf::Text>(m_jerseyFont);
	m_instructions->setCharacterSize(42u);
	m_instructions->setFillColor(sf::Color(255, 255, 255, 215));
	m_instructions->setOutlineColor(sf::Color(0, 0, 0, 255));
	m_instructions->setOutlineThickness(1u);


	m_instructions->setPosition(sf::Vector2f(100.f, 100.f));
	m_instructions->setString("Select Beginning");

	RenderObject::getInstance().addNewRenderObject(m_instructions, 7);

	m_tileManager.init();
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
		if (newEvent->is<sf::Event::MouseButtonReleased>()) //user released a mouse button
		{
			if (m_tileManager.getState() == TileManager::setType::start)
			{
				NPC newNpc;
				newNpc.m_points = m_tileManager.getPoints();
				newNpc.init();
				m_npcs.push_back(newNpc);
			}
			m_tileManager.update();
		}
		if (newEvent->is<sf::Event::MouseMoved>())
		{
			mousePosition = sf::Mouse::getPosition(RenderObject::getInstance().getWindow());

			m_tileManager.update();

			if (m_tileManager.getState() == TileManager::setType::start)
			{
				m_tileManager.mouseClicked();
			}
		}
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	if (const auto* keyPressed = t_event->getIf<sf::Event::KeyReleased>())
	{
		if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
		{
			m_tileManager.progressType();
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num1)
		{
			cost = !cost;
			m_tileManager.changeCost(cost);
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num2)
		{
			integration = !integration;
			m_tileManager.changeInt(integration);
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

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) m_tileManager.mouseClicked();


	for (auto& t : m_npcs)
	{
		t.update();
	}

	switch (m_tileManager.getState())
	{
	case TileManager::setType::obstacle:
		m_instructions->setString("Left Click to Place Obstacles (space to finish)");

		break;
	case TileManager::setType::goal:
		m_instructions->setString("Left Click to place goal");

		break;
	case TileManager::setType::start:
		m_instructions->setString("Left click to place NPC\n1 to toggle cost\n2 to toggle integration");

		break;
	case TileManager::setType::search:
		m_instructions->setString("");

		break;
	default:
		break;
	}
}
