#include "NPC.h"
#include "Game.h"
#include "RenderObject.h"
#include "math.h"

NPC::NPC()
{
}

void NPC::start()
{
	m_angle = rand() % 360;

	if (!m_texture.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";
	m_sprite = std::make_shared<sf::Sprite>(m_texture);


	m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().size / 2.f));
	m_sprite->setScale(sf::Vector2f(0.08f, 0.08f));
	m_sprite->setPosition(sf::Vector2f(600.f, 600.f));
	m_sprite->setRotation(sf::degrees(m_angle + 90.0f));
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
	m_sprite->move(math::degreesToDisplacement(m_angle) * Game::deltaTime * m_speed);
	m_body->setPosition(m_sprite->getPosition());
	outOfBounds();
}

void NPC::outOfBounds()
{
	sf::Vector2f playerPos = m_sprite->getPosition();
	sf::Vector2u screenSize = RenderObject::getInstance().getWindow().getSize();
	if (playerPos.x < 0.f - m_sprite->getGlobalBounds().size.x)
	{
		m_sprite->setPosition(sf::Vector2f(screenSize.x, playerPos.y));
	}
	if (playerPos.y < 0.f - m_sprite->getGlobalBounds().size.y)
	{
		m_sprite->setPosition(sf::Vector2f(playerPos.x, screenSize.y));
	}
	if (playerPos.x > screenSize.x)
	{
		m_sprite->setPosition(sf::Vector2f(0.f - m_sprite->getGlobalBounds().size.x, playerPos.y));
	}
	if (playerPos.y > screenSize.y)
	{
		m_sprite->setPosition(sf::Vector2f(playerPos.x, 0.f - m_sprite->getGlobalBounds().size.y));
	}
}

void NPC::increaseSpeed()
{
	m_speed += m_speedIncreaseFactor * Game::deltaTime;

	if (m_speed > m_maxSpeed)
	{
		m_speed = m_maxSpeed;
	}
}

void NPC::decreaseSpeed()
{
	m_speed -= m_speedIncreaseFactor * Game::deltaTime / 2.0f;

	if (m_speed < 0.f)
	{
		m_speed = 0.f;
	}
}

void NPC::changeAngle(int t_direction)
{
	m_angle += (m_angleChange * Game::deltaTime) * t_direction;
	m_sprite->setRotation(sf::degrees(m_angle + 90.0f));
}
