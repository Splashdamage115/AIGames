#include "NPC.h"
#include "Game.h"
#include "RenderObject.h"
#include "math.h"
#include "wanderMoveState.h"
#include "seekMoveState.h"
#include "ArriveMoveState.h"
#include "PursueMoveState.h"
#include "SwarmMoveState.h"

NPC::NPC()
{
}

void NPC::start(MoveState t_moveType, sf::Vector2f t_position)
{
	if (!m_texture.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";
	m_sprite = std::make_shared<sf::Sprite>(m_texture);

	m_line = std::make_shared<sf::VertexArray>(sf::PrimitiveType::LineStrip, 2);

	int corners = 6;
	m_cone = std::make_shared<sf::VertexArray>(sf::PrimitiveType::TriangleFan, corners);

	m_cone->operator[](0).color = sf::Color(255, 0, 0, 220);
	for (int i = 1; i < corners; i++)
	{
		m_cone->operator[](i).color = sf::Color(255, 0, 0, 60);
	}
	


	//RenderObject::getInstance().addNewRenderObject(m_cone, 1);

	RenderObject::getInstance().addNewRenderObject(m_line, 1);


	m_position = std::make_shared<sf::Vector2f>();

	m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().size / 2.f));
	m_sprite->setScale(sf::Vector2f(0.08f, 0.08f));
	m_sprite->setPosition(t_position);
	//RenderObject::getInstance().addNewRenderObject(m_sprite, 2);

	m_body = std::make_shared<sf::CircleShape>();

	m_body->setRadius(30.f);
	m_body->setOrigin(sf::Vector2f(m_body->getRadius(), m_body->getRadius()));
	m_body->setPosition(m_sprite->getPosition());
	m_body->setFillColor(sf::Color::Red);

	RenderObject::getInstance().addNewRenderObject(m_body, 1);

	m_stateType = std::make_shared<sf::Text>(Game::m_jerseyFont);

	m_stateType->setCharacterSize(16u);
	m_stateType->setFillColor(sf::Color::White);

	// choose the move type
	switch (t_moveType)
	{
	case NPC::MoveState::none:
		m_moveState = std::make_shared<wanderMoveState>(m_position);
		m_stateType->setString("Wander");
		break;
	case NPC::MoveState::seek:
		m_moveState = std::make_shared<seekMoveState>(m_position);
		m_stateType->setString("Seek");
		break;
	case NPC::MoveState::arrive:
		m_moveState = std::make_shared<ArriveMoveState>(m_position);
		m_stateType->setString("Arrive");
		break;
	case NPC::MoveState::wander:
		m_moveState = std::make_shared<wanderMoveState>(m_position);
		m_stateType->setString("Wander");
		break;
	case NPC::MoveState::pursue:
		m_moveState = std::make_shared<PursueMoveState>(m_position);
		m_stateType->setString("Pursue");
		break;
	case NPC::MoveState::swarm:
		m_moveState = std::make_shared<SwarmMoveState>(m_position);
		//m_sprite->setScale(sf::Vector2f(0.2f,0.2f));
		m_body->setRadius(10.0f);
		m_stateType->setString("Swarm");
		break;
	default:
		m_moveState = std::make_shared<wanderMoveState>(m_position);
		m_stateType->setString("Wander");
		break;
	}

	RenderObject::getInstance().addNewRenderObject(m_stateType, 3);
	m_moveState->init();
	m_sprite->setRotation(m_moveState->getAngle());
}

void NPC::update(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed)
{
	m_sprite->move(m_moveState->moveVector(t_playerPos, t_playerAngle, t_speed));
	m_sprite->setRotation(m_moveState->getAngle());

	sf::Vector2f center = m_body->getPosition() - sf::Vector2f(m_body->getRadius() + 10.0f, m_body->getRadius() + 10.0f);

	m_line->operator[](0).position = center;
	m_line->operator[](1).position = center + (math::degreesToDisplacement(m_body->getRotation().asDegrees() - 90.0f) * 300.0f);

	outOfBounds();
	m_position->x = center.x;
	m_position->y = center.y;

	m_stateType->setPosition(*m_position + sf::Vector2f(30.0f, 30.0f));

	m_cone->operator[](0).position = center;
	m_cone->operator[](1).position = center + (math::degreesToDisplacement(m_body->getRotation().asDegrees() - 90.0f - 20.0f) * 300.0f);
	m_cone->operator[](2).position = center + (math::degreesToDisplacement(m_body->getRotation().asDegrees() - 90.0f - 10.0f) * 300.0f);
	m_cone->operator[](3).position = center + (math::degreesToDisplacement(m_body->getRotation().asDegrees() - 90.0f) * 300.0f);
	m_cone->operator[](4).position = center + (math::degreesToDisplacement(m_body->getRotation().asDegrees() - 90.0f + 10.0f) * 300.0f);
	m_cone->operator[](5).position = center + (math::degreesToDisplacement(m_body->getRotation().asDegrees() - 90.0f + 20.0f) * 300.0f);

	sf::ConvexShape tempCone(3);
	tempCone.setPoint(0, m_cone->operator[](0).position);
	tempCone.setPoint(1, m_cone->operator[](1).position);
	tempCone.setPoint(2, m_cone->operator[](5).position);

	sf::FloatRect playerBox;
	playerBox.position = t_playerPos;
	playerBox.size = sf::Vector2f(10.f, 10.f);

	bool insideCone = math::coneIntersectsBox(tempCone, playerBox);
	int corners = 6;
	if (insideCone)
	{
		m_cone->operator[](0).color = sf::Color(255, 255, 0, 220);
		for (int i = 1; i < corners; i++)
		{
			m_cone->operator[](i).color = sf::Color(255, 255, 0, 60);
		}
	}
	else
	{
		m_cone->operator[](0).color = sf::Color(255, 0, 0, 220);
		for (int i = 1; i < corners; i++)
		{
			m_cone->operator[](i).color = sf::Color(255, 0, 0, 60);
		}
	}

}

void NPC::changeMaxMoveSpeed(float t_newMaxMove)
{
	m_moveState->changeMaxSpeed(t_newMaxMove);
}

void NPC::changeMoveSpeed(float t_newMaxMove)
{
	m_moveState->changeSpeed(t_newMaxMove);
}

sf::Vector2f NPC::getPos()
{
	return sf::Vector2f() ;
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

