#pragma once

#include "Library.h"
#include "FormationPoint.h"

class AbstractFormation
{
public:
	virtual int addNewPoint() = 0;

	virtual void setCenterPosition(sf::Vector2f t_centerPos) { m_center = t_centerPos; }

	virtual void movePosition(sf::Vector2f t_newPos, float t_newAngle) = 0;

	sf::Vector2f getTarget(int t_position) { return m_points.at(t_position).getPosition(); }

protected:
	std::vector<FormationPoint> m_points;

	std::vector<std::shared_ptr<sf::CircleShape>> m_pointVisuals;

	sf::Vector2f m_center = { 0.f, 0.f };
};

