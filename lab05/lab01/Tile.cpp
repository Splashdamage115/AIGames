#include "Tile.h"
#include "RenderObject.h"

void Tile::init(sf::Vector2i t_tileNum)
{
	m_tileNum = t_tileNum;
	m_tile = std::make_shared<sf::RectangleShape>(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	m_tile->setFillColor(sf::Color::Transparent);
	m_tile->setOutlineColor(sf::Color::White);
	m_tile->setOutlineThickness(1.f);
	m_tile->setPosition(sf::Vector2f(m_tileNum.x * TILE_SIZE, m_tileNum.y * TILE_SIZE));
	RenderObject::getInstance().addNewRenderObject(m_tile, 2);
}
