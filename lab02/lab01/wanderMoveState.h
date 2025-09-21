#pragma once
#include "abstractMoveState.h"

class wanderMoveState : public abstractMoveState
{
public:
	wanderMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed) override;
private:

};

