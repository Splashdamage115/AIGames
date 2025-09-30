#pragma once

#include "abstractMoveState.h"

class SwarmMoveState : public abstractMoveState
{
public:
	SwarmMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_other, float t_, float t_2) override;

	sf::Vector2f getPosition();

private:
	float A = 10.f;
	float B = 10.f;
	float N = 10.f;
	float M = 10.f;
};

