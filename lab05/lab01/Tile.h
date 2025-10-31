#pragma once

#include "Library.h"

class Tile
{
public:
	void init(sf::Vector2i t_tileNum);
	sf::Vector2i getTile() { return m_tileNum; }

	void setCost(int t_cost);
	void setInt(int t_dist);
	void highlight(bool t_highlight);
	void path(bool t_path);
	bool checkIntersect();
	bool costSet();
	void drawNext();
	sf::Vector2f getCenter() { return m_tile->getGeometricCenter() + m_tile->getPosition(); }

	int m_cost = 0;
	bool processed = false;
	sf::Vector2i next;

	std::shared_ptr< sf::Text> m_costT;
	std::shared_ptr< sf::Text> m_intT;

private:
	sf::Color m_color;
	sf::Color m_ncolor;
	std::shared_ptr< sf::RectangleShape> m_tile;
	std::shared_ptr< sf::VertexArray> m_direction;
	sf::Vector2i m_tileNum;

	
	int m_integration = 0;

	bool end = false;
};
