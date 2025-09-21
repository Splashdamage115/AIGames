#include "NPC.h"
#include "Game.h"
#include "RenderObject.h"
#include "math.h"
#include "wanderMoveState.h"
#include "seekMoveState.h"
#include "ArriveMoveState.h"
#include "PursueMoveState.h"

NPC::NPC()
{
}

void NPC::start(MoveState t_moveType, sf::Vector2f t_position)
{
	if (!m_texture.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";
	m_sprite = std::make_shared<sf::Sprite>(m_texture);

	m_line = std::make_shared<sf::VertexArray>();

	m_line->append(sf::Vertex());
	m_line->append(sf::Vertex());

	RenderObject::getInstance().addNewRenderObject(m_line, 1);


	m_position = std::make_shared<sf::Vector2f>();

	m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().size / 2.f));
	m_sprite->setScale(sf::Vector2f(0.08f, 0.08f));
	m_sprite->setPosition(t_position);
	RenderObject::getInstance().addNewRenderObject(m_sprite, 2);

	m_body = std::make_shared<sf::CircleShape>();

	m_body->setRadius(30.f);
	m_body->setOrigin(sf::Vector2f(m_body->getRadius(), m_body->getRadius()));
	m_body->setPosition(m_sprite->getPosition());
	m_body->setFillColor(sf::Color::Red);

	//RenderObject::getInstance().addNewRenderObject(m_body, 1);

	// choose the move type
	switch (t_moveType)
	{
	case NPC::MoveState::none:
		m_moveState = std::make_shared<wanderMoveState>(m_position);
		break;
	case NPC::MoveState::seek:
		m_moveState = std::make_shared<seekMoveState>(m_position);
		break;
	case NPC::MoveState::arrive:
		m_moveState = std::make_shared<ArriveMoveState>(m_position);
		break;
	case NPC::MoveState::wander:
		m_moveState = std::make_shared<wanderMoveState>(m_position);
		break;
	case NPC::MoveState::pursue:
		m_moveState = std::make_shared<PursueMoveState>(m_position);
		break;
	default:
		m_moveState = std::make_shared<wanderMoveState>(m_position);
		break;
	}


	m_moveState->init();
	m_sprite->setRotation(m_moveState->getAngle());
}

void NPC::update(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed)
{
	m_sprite->move(m_moveState->moveVector(t_playerPos, t_playerAngle, t_speed));
	m_sprite->setRotation(m_moveState->getAngle());

	m_line->operator[](0).position = m_sprite->getPosition();
	m_line->operator[](1).position = m_sprite->getPosition()+m_moveState->moveVector(t_playerPos, t_playerAngle, t_speed) * 100.0f;

	m_body->setPosition(m_sprite->getPosition());
	outOfBounds();
	m_position->x = m_sprite->getPosition().x;
	m_position->y = m_sprite->getPosition().y;
}

void NPC::changeMoveSpeed(float t_newMaxMove)
{
	m_moveState->changeMaxSpeed(t_newMaxMove);
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

