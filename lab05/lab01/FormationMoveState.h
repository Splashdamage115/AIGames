#pragma once

#include "abstractMoveState.h"
#include "AbstractFormation.h"

class FormationMoveState : public abstractMoveState
{
public:
	FormationMoveState(std::shared_ptr<sf::Vector2f> t_position);
	void init() override;
	sf::Vector2f moveVector(sf::Vector2f t_centerPos, float t_faceAngle, float t_) override;

private:
	float arriveDistance = 0.0f;
	float closeDistance = 30.0f;

	void arrive(sf::Vector2f t_playerPos);

	int m_formationPosition = 0;

	std::shared_ptr<AbstractFormation> m_formation;
};

