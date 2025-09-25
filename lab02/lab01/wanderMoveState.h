#pragma once
#include "abstractMoveState.h"

class wanderMoveState : public abstractMoveState
{
public:
	wanderMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed) override;
private:
	float m_targetAngle = 0.0f;
	float m_targetAngleIncrease = 0.0f;
	const static int m_rotateIncrease = 30;

	const static int m_maxWaitTime = 5;
	float m_currentWaitTimeLeft = 0.0f;
	bool m_randomisePoint = false;

	void setNewWaitTime();
	bool checkTimeUp();
	bool checkFacingPoint();
	void chooseNewPoint();
};

