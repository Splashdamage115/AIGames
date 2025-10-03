#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "RenderObject.h"
#include "math.h"
#include "SimpleButton.h"

float Game::deltaTime = 0.f;
sf::Font Game::m_jerseyFont;
sf::Texture Game::m_shipTexture;

Game::Game()
{
	if (!m_shipTexture.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf")) std::cout << "problem loading arial black font" << std::endl;

	RenderObject::getInstance().start();
	srand(static_cast<unsigned int>(time(nullptr)));
	m_player.start();

	float offsetX = 100.0f;
	float offsetY = 100.0f;
	int Loop = 10;
	int yoff = 0;

	for (int i = 0; i < 5; i++)
	{
		if (i % Loop == Loop - 1)
		{
			yoff++;
		}

		m_npcs.emplace_back();
		m_npcActive.emplace_back();
		m_npcActive.at(i) = true;
		m_npcs.at(i).start(NPC::MoveState::swarm, { 100.0f + (offsetX * (i % Loop)), 100.0f + (offsetY * yoff)});
		m_closestNpc.push_back(0);
	}

	//m_instructions = std::make_shared<sf::Text>(m_jerseyFont);
	//m_instructions->setCharacterSize(42u);
	//m_instructions->setFillColor(sf::Color(255, 255, 255, 125));
	//m_instructions->setPosition(sf::Vector2f(100.f, 100.f));
	//m_instructions->setString("USE KEYS 1-5 TO CHANGE NPC ACTIVE/INACTIVE");

	//RenderObject::getInstance().addNewRenderObject(m_instructions, 0);
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
	//	if (keyPressed->scancode == sf::Keyboard::Scancode::Num1)
	//	{
	//		changeNPC(0);
	//	}
	//	else if (keyPressed->scancode == sf::Keyboard::Scancode::Num2)
	//	{
	//		changeNPC(1);
	//	}
	//	else if (keyPressed->scancode == sf::Keyboard::Scancode::Num3)
	//	{
	//		changeNPC(2);
	//	}
	//	else if (keyPressed->scancode == sf::Keyboard::Scancode::Num4)
	//	{
	//		changeNPC(3);
	//	}
	//	else if (keyPressed->scancode == sf::Keyboard::Scancode::Num5)
	//	{
	//		changeNPC(4);
	//	}
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
	SimpleButtonHolder::getInstance().setMouse(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y)));
	SimpleButtonHolder::getInstance().update();

	Game::deltaTime = t_deltaTime;
	checkKeyboardState();

	m_player.update();

	//calculateClosest();
	std::vector<sf::Vector2f> locals;
	for (unsigned int i = 0; i < m_npcs.size(); i++)
	{
		if (m_npcActive.at(i))
		{
			locals.clear();
			float maxDistance = 1000.0f;
			for (unsigned int j = 0; j < m_npcs.size(); j++)
			{
				if (i == j) continue;

				float currentDistance = math::distance(m_npcs.at(i).getPos(), m_npcs.at(j).getPos());
				if (currentDistance < maxDistance)
				{
					locals.push_back(m_npcs.at(j).getPos());
				}
			}
			m_npcs.at(i).updateGroup(locals);
		}
	}
}

void Game::calculateClosest()
{
	for (int i = 0; i < m_npcs.size(); i++)
	{
		float closestDistance = std::numeric_limits<float>::max();
		int closestIndex = -1;

		for (int j = 0; j < m_npcs.size(); j++)
		{
			if (i == j)
				continue;

			float currentDistance = math::distance(m_npcs.at(i).getPos(), m_npcs.at(j).getPos());

			if (currentDistance < closestDistance)
			{
				closestDistance = currentDistance;
				closestIndex = j;
			}
		}

		m_closestNpc.at(i) = closestIndex;
	}

	std::cout << "Closest NPCs calculated.\n";
}


//void Game::changeNPC(int t_num)
//{
//	if (m_npcActive.at(t_num))
//	{
//		m_npcs.at(t_num) = NPC();
//		m_npcActive.at(t_num) = false;
//	}
//	else
//	{
//		switch (t_num)
//		{
//		case 0:
//			m_npcs.at(t_num).start(NPC::MoveState::wander, { 300.0f, 600.0f });
//			m_npcs.at(t_num).changeMoveSpeed(500.0f);
//			break;
//		case 1:
//			m_npcs.at(t_num).start(NPC::MoveState::seek, { 600.0f, 300.0f });
//			break;
//		case 2:
//			m_npcs.at(t_num).start(NPC::MoveState::pursue, { 800.0f, 600.0f });
//			break;
//		case 3:
//			m_npcs.at(t_num).start(NPC::MoveState::arrive, { 900.0f, 100.0f });
//			break;
//		case 4:
//			m_npcs.at(t_num).start(NPC::MoveState::arrive, { 900.0f, 800.0f });
//			m_npcs.at(t_num).changeMaxMoveSpeed(400.0f);
//			break;
//		default:
//			break;
//		}
//		m_npcActive.at(t_num) = true;
//	}
//}


