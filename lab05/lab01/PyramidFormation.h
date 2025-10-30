#pragma once

#include "AbstractFormation.h"

class PyramidFormation : public AbstractFormation
{
public:
	virtual int addNewPoint() override;
	virtual void movePosition(sf::Vector2f t_newPos, float t_newAngle) override;
private:
	int m_runningPyramidWidth = 0;
	int m_currentWidth = 0;
	int m_height = 0;

	float height = 280.0f;
	float angle = 45.0f;
	float width = 280.0f;
};

