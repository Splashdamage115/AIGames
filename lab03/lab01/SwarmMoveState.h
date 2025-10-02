#pragma once

#include "abstractMoveState.h"
#include "SimpleButton.h"

class SwarmMoveState : public abstractMoveState
{
public:
	SwarmMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_other, float t_, float t_2) override;

private:
	float A = 800.f;
	float B = 2000.f;
	float N = 200.f;
	float M = 1.f;
};

