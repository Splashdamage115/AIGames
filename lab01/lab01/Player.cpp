#include "Player.h"
#include "Game.h"
#include "RenderObject.h"
#include "math.h"

Player::Player()
{
}

void Player::start()
{
	float angle = rand() % 360;
	std::cout << angle << std::endl;
	m_moveDirection = math::degreesToDisplacement(angle);

	m_body = std::make_shared<sf::CircleShape>();

	m_body->setRadius(30.f);
	m_body->setPosition(sf::Vector2f(100.f, 100.f));
	m_body->setFillColor(sf::Color::White);

	RenderObject::getInstance().addNewRenderObject(m_body, 1);
}

void Player::update()
{
	m_body->move(m_moveDirection * Game::deltaTime * 100.f);

	outOfBounds();
}

void Player::outOfBounds()
{
	sf::Vector2f playerPos = m_body->getPosition();
	sf::Vector2u screenSize = RenderObject::getInstance().getWindow().getSize();
	if (playerPos.x < 0.f - m_body->getRadius() * 2.f)
	{
		m_body->setPosition(sf::Vector2f(screenSize.x, playerPos.y));
	}
	if (playerPos.y < 0.f - m_body->getRadius() * 2.f)
	{
		m_body->setPosition(sf::Vector2f(playerPos.x, screenSize.y));
	}
	if (playerPos.x > screenSize.x)
	{
		m_body->setPosition(sf::Vector2f(0.f - m_body->getRadius() * 2.f, playerPos.y));
	}
	if (playerPos.y > screenSize.y)
	{
		m_body->setPosition(sf::Vector2f(playerPos.x, 0.f - m_body->getRadius() * 2.f));
	}
}
