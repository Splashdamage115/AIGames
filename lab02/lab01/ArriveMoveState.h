#pragma once
#include "abstractMoveState.h"
class ArriveMoveState : public abstractMoveState
{
public:
	ArriveMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed) override;
private:
	float arriveDistance = 120.0f;
	float closeDistance = 80.0f;
	
	void arrive(sf::Vector2f t_playerPos);
};

