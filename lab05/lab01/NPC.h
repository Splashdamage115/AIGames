#pragma once

#include "Library.h"

class NPC
{
public:
	void update();
	void init();

	std::vector<sf::Vector2f> m_points;
private:
	std::shared_ptr<sf::CircleShape> body;
	int m_pos = 0;
	float m_speed = 100.0f;
};

