#include "FormationPoint.h"

void FormationPoint::moveTargetPoint(sf::Vector2f t_newTarget, float t_newRotation)
{
	m_targetPoint = t_newTarget;
	m_rotation = t_newRotation;
}
