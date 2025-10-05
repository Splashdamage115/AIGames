#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "RenderObject.h"
#include "PyramidFormation.h"

float Game::deltaTime = 0.f;
sf::Font Game::m_jerseyFont;
sf::Texture Game::m_ship;

Game::Game()
{

	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf")) std::cout << "problem loading arial black font" << std::endl;
	if (!m_ship.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";


	RenderObject::getInstance().start();
	srand(static_cast<unsigned int>(time(nullptr)));
	m_player.start();


	m_formation = std::make_shared<PyramidFormation>();

	float offsetX = 100.0f;
	float offsetY = 100.0f;
	int Loop = 10;
	int yoff = 0;

	for (int i = 0; i < 10; i++)
	{
		if (i % Loop == Loop - 1)
		{
			yoff++;
		}
		m_npcs.emplace_back();
		m_npcActive.emplace_back();
		m_npcActive.at(i) = true;
		m_npcs.at(i).start(NPC::MoveState::formation, { 100.0f + (offsetX * (i % Loop)), 100.0f + (offsetY * yoff) });
		m_formation->addNewPoint();
	}

	m_instructions = std::make_shared<sf::Text>(m_jerseyFont);
	m_instructions->setCharacterSize(42u);
	m_instructions->setFillColor(sf::Color(255, 255, 255, 125));
	m_instructions->setPosition(sf::Vector2f(100.f, 100.f));
	m_instructions->setString("Press 1 to Active Pyramid");

	RenderObject::getInstance().addNewRenderObject(m_instructions, 0);
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
			formationActive = !formationActive;

			for (int i = 0; i < m_npcs.size(); i++)
			{
				sf::Vector2f pos = m_npcs.at(i).getPosition();
				float angle = m_npcs.at(i).getAngle();

				m_npcs.at(i).start((formationActive) ? NPC::MoveState::wander : NPC::MoveState::formation, pos);
				m_npcs.at(i).setAngle(angle);
			}
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

	m_formation->movePosition(m_player.getPosition(), m_player.getAngle());

	for (int i = 0; i < m_npcs.size(); i++)
	{
		if(m_npcActive.at(i))
			m_npcs.at(i).update(m_formation->getTarget(i), m_player.getAngle(), m_player.getSpeed());
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


