#include "NPC.h"
#include "Game.h"
#include "RenderObject.h"
#include "math.h"

void NPC::update()
{
	if (math::distancebetweenPoints(body->getPosition(), m_points.at(m_pos)) <= 3.0f)
	{
		m_pos++;
		if (m_pos >= m_points.size())
		{
			m_pos = m_points.size() - 1;
		}
	}
	body->move(math::displacement(body->getPosition(), m_points.at(m_pos)) * m_speed * Game::deltaTime);
}

void NPC::init()
{
	body = std::make_shared<sf::CircleShape>(3.0f);
	body->setOrigin(sf::Vector2f(3.f, 3.f));
	body->setPosition(m_points.at(0));
	body->setFillColor(sf::Color(225, 225, 80, 255));
	RenderObject::getInstance().addNewRenderObject(body, 6);
}
