#pragma once

#include "Tile.h"

class TileManager
{
public:

	enum class setType
	{
		obstacle, goal, start, search
	};

	void init();
	void mouseClicked();
	void update();
	void progressType();
	setType getState() { return m_currentType; }

	void setHeatMap();
	std::vector<sf::Vector2f> getPoints();

	void changeCost(bool t_active);
	void changeInt(bool t_active);

private:
	setType m_currentType;
	std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;

	sf::Vector2i goal;
	sf::Vector2i start;
	bool traversed = false;
};

