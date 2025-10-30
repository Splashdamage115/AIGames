#pragma once
#include "abstractMoveState.h"
class PursueMoveState : public abstractMoveState
{
public:
	PursueMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed) override;
private:
	float lookAheadTime = 0.5f;
	float arriveDistance = 50.0f;

	std::shared_ptr<sf::CircleShape> m_seekPoint;
};

