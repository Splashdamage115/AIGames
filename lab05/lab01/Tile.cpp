#include "Tile.h"
#include "RenderObject.h"
#include "Game.h"

void Tile::init(sf::Vector2i t_tileNum)
{
	m_tileNum = t_tileNum;
	m_tile = std::make_shared<sf::RectangleShape>(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	m_tile->setFillColor(sf::Color::Transparent);
	m_tile->setOutlineColor(sf::Color(255,255,255,100));
	m_tile->setOutlineThickness(1.f);
	m_tile->setPosition(sf::Vector2f(m_tileNum.x * TILE_SIZE, m_tileNum.y * TILE_SIZE));
	RenderObject::getInstance().addNewRenderObject(m_tile, 2);

	m_color = sf::Color::Transparent;

	m_costT = std::make_shared<sf::Text>(Game::m_jerseyFont);
	m_costT->setCharacterSize(12u);
	m_costT->setFillColor(sf::Color::Transparent);
	m_costT->setPosition(sf::Vector2f(m_tileNum.x * TILE_SIZE, m_tileNum.y * TILE_SIZE));
	m_costT->setString("0");

	RenderObject::getInstance().addNewRenderObject(m_costT, 3);

	m_intT = std::make_shared<sf::Text>(Game::m_jerseyFont);
	m_intT->setCharacterSize(12u);
	m_intT->setFillColor(sf::Color::Transparent);
	m_intT->setPosition(sf::Vector2f(m_tileNum.x * TILE_SIZE, m_tileNum.y * TILE_SIZE));
	m_intT->setString("0");

	RenderObject::getInstance().addNewRenderObject(m_intT, 3);
}

void Tile::setCost(int t_cost)
{
	// already set as an obstacle, so skip
	if (m_cost == 99999 || end)
	{
		return;
	}
	// obstacle
	if (t_cost == -2)
	{
		m_cost = 99999;
		m_color = sf::Color::White;
		m_tile->setFillColor(sf::Color::White);
		m_costT->setString(std::to_string(999));
		return;
	}
	// end
	else if (t_cost == -3)
	{
		m_cost = 0;
		m_color = sf::Color::Red;
		m_tile->setFillColor(sf::Color::Red);
		m_costT->setString("0");
		end = true;
		return;
	}
	// normal Tile
	else
	{
		m_color = sf::Color(std::clamp(255 - (t_cost * 10), 0, 130), 0, std::clamp((t_cost * 10), 0, 255), 255);
		m_tile->setFillColor(m_color);
	}

	// start
	if (t_cost == -4)
	{
		m_color = sf::Color::Green;
		m_tile->setFillColor(sf::Color::Green);
		return;
	}
	if (t_cost == -5)
	{
		m_costT->setString(std::to_string(m_cost));
		m_color = sf::Color(std::clamp(255 - (m_cost * 10), 0, 130), 0, std::clamp((m_cost * 10), 0, 255), 255);
		m_tile->setFillColor(m_color);
		return;
	}
	m_cost = t_cost;
	m_costT->setString(std::to_string(m_cost));
}

void Tile::setInt(int t_dist)
{
	m_integration = m_cost + t_dist;
	m_intT->setString(std::to_string(m_integration));
}

void Tile::highlight(bool t_highlight)
{
	if (t_highlight)
	{
		m_tile->setFillColor(sf::Color(255,255,255,125));
	}
	else
	{
		m_tile->setFillColor(m_color);
	}
}

void Tile::path(bool t_path)
{
	
	if (t_path)
	{
		if (!end && m_cost != -4) 
		{
			m_ncolor = m_tile->getFillColor();
			m_color = sf::Color(255, 255, 0, 125);
			m_tile->setFillColor(m_color);
		}
	}
	
	if(!t_path)
	{
		m_color = m_ncolor;
		m_tile->setFillColor(m_color);
	}
}

bool Tile::checkIntersect()
{
	return m_tile->getGlobalBounds().contains(sf::Vector2f(Game::mousePosition.x, Game::mousePosition.y));
}

bool Tile::costSet() 
{ 
	if (end) return true;
	if (m_cost == -4) return false;
	return (m_cost != 0);
}

void Tile::drawNext()
{
	m_direction = std::make_shared<sf::VertexArray>(sf::PrimitiveType::Lines, 2u);
	m_direction->operator[](0).position = m_tile->getGeometricCenter() + m_tile->getPosition();
	m_direction->operator[](0).color = sf::Color(255,255,0,100);
	sf::Vector2i point = m_tileNum - next;
	float length = 10.0f;
	m_direction->operator[](1).position = m_tile->getPosition() + m_tile->getGeometricCenter() - sf::Vector2f(point.x * length, point.y * length);
	m_direction->operator[](1).color = sf::Color(255, 255, 0, 225);
	RenderObject::getInstance().addNewRenderObject(m_direction, 4);
}
