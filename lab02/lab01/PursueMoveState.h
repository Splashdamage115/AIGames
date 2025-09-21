#pragma once
#include "abstractMoveState.h"
class PursueMoveState : public abstractMoveState
{
public:
	PursueMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed) override;
private:
	float lookAheadTime = 1.0f;
	float arriveDistance = 80.0f;
};

