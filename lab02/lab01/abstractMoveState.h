#pragma once
#include "Library.h"

class abstractMoveState
{
public:
	abstractMoveState(std::shared_ptr<sf::Vector2f> t_position)
	{
		m_position = t_position;
	}
	virtual void init(){ }

	virtual sf::Vector2f moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed) = 0;

	sf::Angle getAngle()
	{
		return sf::degrees(m_angle + 90.0f);
	}

	void changeMaxSpeed(float newMax)
	{
		m_maxSpeed = newMax;
	}
protected:
	void increaseSpeed();
	void decreaseSpeed();
	void changeAngle(int t_direction);

	float m_angle = 0.0f;
	float m_angleChange = 100.0f;

	float m_speed = 100.0f;
	float m_maxSpeed = 500.0f;
	float m_speedIncreaseFactor = 100.0f;
	std::shared_ptr<sf::Vector2f> m_position;
};
