#include "NPC.h"
#include "Game.h"
#include "RenderObject.h"
#include "math.h"

NPC::NPC()
{
}

void NPC::start()
{
	float angle = rand() % 360;
	std::cout << angle << std::endl;
	m_moveDirection = math::degreesToDisplacement(angle);

	if (!m_texture.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";
	m_sprite = std::make_shared<sf::Sprite>(m_texture);


	m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().size / 2.f));
	m_sprite->setScale(sf::Vector2f(0.08f, 0.08f));
	m_sprite->setPosition(sf::Vector2f(600.f, 600.f));
	m_sprite->setRotation(sf::degrees(math::displacementToDegrees(m_moveDirection) + 90.0f));
	RenderObject::getInstance().addNewRenderObject(m_sprite, 2);


	m_body = std::make_shared<sf::CircleShape>();

	m_body->setRadius(30.f);
	m_body->setOrigin(sf::Vector2f(m_body->getRadius(), m_body->getRadius()));
	m_body->setPosition(m_sprite->getPosition());
	m_body->setFillColor(sf::Color::Red);

	RenderObject::getInstance().addNewRenderObject(m_body, 1);
}

void NPC::update()
{
	m_sprite->move(m_moveDirection * Game::deltaTime * m_speed);
	m_body->setPosition(m_sprite->getPosition());
	outOfBounds();
}

void NPC::outOfBounds()
{
	sf::Vector2f npcPos = m_sprite->getPosition();
	sf::Vector2u screenSize = RenderObject::getInstance().getWindow().getSize();
	if (npcPos.x < 0.f - m_sprite->getGlobalBounds().size.x)
	{
		m_sprite->setPosition(sf::Vector2f(screenSize.x, npcPos.y));
	}
	if (npcPos.y < 0.f - m_sprite->getGlobalBounds().size.y)
	{
		m_sprite->setPosition(sf::Vector2f(npcPos.x, screenSize.y));
	}
	if (npcPos.x > screenSize.x)
	{
		m_sprite->setPosition(sf::Vector2f(0.f - m_sprite->getGlobalBounds().size.x, npcPos.y));
	}
	if (npcPos.y > screenSize.y)
	{
		m_sprite->setPosition(sf::Vector2f(npcPos.x, 0.f - m_sprite->getGlobalBounds().size.y));
	}
}
