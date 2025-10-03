#pragma once

#include "abstractMoveState.h"
#include "SimpleButton.h"

class SwarmMoveState : public abstractMoveState
{
public:
	SwarmMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_other, float t_, float t_2) override;
	sf::Vector2f moveWithLocal(std::vector<sf::Vector2f> t_others) override;

private:
	sf::Vector2f calcLJ(sf::Vector2f me, sf::Vector2f other);

	// this works, i dont have the patience to find the exact variables
	float A = 10.f;
	float B = 500.f;
	float N = 1.f;
	float M = 4.f;
};

