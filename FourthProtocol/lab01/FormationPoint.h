#pragma once

#include "Library.h"

class FormationPoint
{
public:
	void moveTargetPoint(sf::Vector2f t_newTarget, float t_newRotation);
	sf::Vector2f getPosition() { return m_targetPoint; }
	float getRotation() { return m_rotation; }
private:
	sf::Vector2f m_targetPoint = { 0.f,0.f };
	float m_rotation = 0;
};

