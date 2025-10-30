#pragma once

#include "Library.h"

class Tile
{
public:
	void init(sf::Vector2i t_tileNum);
	sf::Vector2i getTile() { return m_tileNum; }
private:
	std::shared_ptr< sf::RectangleShape> m_tile;
	sf::Vector2i m_tileNum;
};
