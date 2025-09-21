#include "abstractMoveState.h"
#include "Game.h"

void abstractMoveState::increaseSpeed()
{
	m_speed += m_speedIncreaseFactor * Game::deltaTime;

	if (m_speed > m_maxSpeed)
	{
		m_speed = m_maxSpeed;
	}
}

void abstractMoveState::decreaseSpeed()
{
	m_speed -= m_speedIncreaseFactor * Game::deltaTime;

	if (m_speed < 0.f)
	{
		m_speed = 0.f;
	}
}

void abstractMoveState::changeAngle(int t_direction)
{
	m_angle += (m_angleChange * Game::deltaTime) * t_direction;

	if (m_angle < 0.f)
		m_angle = 360.f + m_angle;
	if (m_angle > 360.f)
	{
		m_angle = m_angle - 360.f;
	}
}