#include "PyramidFormation.h"
#include "math.h"
#include "RenderObject.h"

int PyramidFormation::addNewPoint()
{
	FormationPoint newPoint;
	float rotation = 0.0f;
	sf::Vector2f position = { 800.f,800.f };

	if (m_points.size() == 0)
	{
		m_height++;
	}
	else
	{
		if (m_currentWidth == m_runningPyramidWidth)
		{
			sf::Vector2f offset = (math::degreesToDisplacement(m_points.at(0).getRotation() - 180.0f + angle) * (height * m_height));
			position = (m_points.at(0).getPosition()) + offset;
			m_height++;
			m_runningPyramidWidth++;
			m_currentWidth = 0;
		}
		else
		{
			sf::Vector2f offset = (math::degreesToDisplacement(m_points.at(m_points.size() - 1).getRotation() + 90.0f) * (width));
			position = (m_points.at(m_points.size() - 1).getPosition()) + offset;
			m_currentWidth++;
		}
	}
	newPoint.moveTargetPoint(position, rotation);
	m_points.push_back(newPoint);

	std::shared_ptr<sf::CircleShape> circ = std::make_shared<sf::CircleShape>(10.0f);
	circ->setPosition(position);
	RenderObject::getInstance().addNewRenderObject(circ, 5);
	m_pointVisuals.push_back(circ);

	return m_points.size() - 1;
}

void PyramidFormation::movePosition(sf::Vector2f t_newPos, float t_newAngle)
{
	m_currentWidth = 0;
	m_height = 0;
	m_runningPyramidWidth = 0;

	float rotation = t_newAngle;
	sf::Vector2f position = t_newPos;

	for (int i = 0; i < m_points.size(); i++)
	{

		if (i == 0)
		{
			m_height++;
		}
		else
		{
			if (m_currentWidth == m_runningPyramidWidth)
			{
				sf::Vector2f offset = (math::degreesToDisplacement(m_points.at(0).getRotation() - 180.0f + angle) * (height * m_height));
				position = (m_points.at(0).getPosition()) + offset;
				m_height++;
				m_runningPyramidWidth++;
				m_currentWidth = 0;
			}
			else
			{
				sf::Vector2f offset = (math::degreesToDisplacement(m_points.at(m_points.size() - 1).getRotation() + 90.0f) * (width));
				position = (m_points.at(i - 1).getPosition()) + offset;
				m_currentWidth++;
			}
		}
		m_points.at(i).moveTargetPoint(position, rotation);

		m_pointVisuals.at(i)->setPosition(position);
	}
}
