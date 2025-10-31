#include "TileManager.h"
#include "Game.h"
#include <queue>

void TileManager::init()
{
	m_tiles.emplace_back();
	for (int x = 0; x < TILE_WIDTH; x++)
	{
		for (int y = 0; y < TILE_WIDTH; y++)
		{
			std::shared_ptr<Tile> newTile = std::make_shared<Tile>();
			newTile->init(sf::Vector2i(x, y));
			m_tiles.at(x).emplace_back(newTile);
		}
		m_tiles.emplace_back();
	}
	m_currentType = setType::obstacle;
}

void TileManager::mouseClicked()
{
	sf::Vector2i tileClicked = Game::mousePosition / static_cast<int>(TILE_SIZE);

	

	if (tileClicked.x > m_tiles.size() || tileClicked.x < 0)
	{
		return;
	}
	if (tileClicked.y > m_tiles.at(tileClicked.x).size() || tileClicked.y < 0)
	{
		return;
	}
	switch (m_currentType)
	{
	case TileManager::setType::obstacle:
		m_tiles.at(tileClicked.x).at(tileClicked.y)->setCost(-2);
		break;
	case TileManager::setType::goal:
		m_tiles.at(tileClicked.x).at(tileClicked.y)->setCost(-3);
		goal = sf::Vector2i(tileClicked.x, tileClicked.y);
		progressType();
		break;
	case TileManager::setType::start:

		if (tileClicked.x > TILE_WIDTH || tileClicked.x < 0 || tileClicked.y > TILE_WIDTH || tileClicked.y < 0)
			return;

		if(traversed){
			m_tiles.at(start.x).at(start.y)->setCost(-5);
			sf::Vector2i pos = m_tiles.at(start.x).at(start.y)->next;
			while (pos != goal)
			{
				m_tiles.at(pos.x).at(pos.y)->path(false);
				pos = m_tiles.at(pos.x).at(pos.y)->next;
			}
		}
		traversed = true;
		m_tiles.at(tileClicked.x).at(tileClicked.y)->setCost(-4);
		start = sf::Vector2i(tileClicked.x, tileClicked.y);
		progressType();
		break;
	case TileManager::setType::search:
		//setHeatMap();
		break;
	default:
		break;
	}
}

void TileManager::update()
{
	sf::Vector2i tileClicked = Game::mousePosition / static_cast<int>(TILE_SIZE);

	for (int x = 0; x < TILE_WIDTH; x++)
	{
		for (int y = 0; y < TILE_WIDTH; y++)
		{
			if (tileClicked.x == x && tileClicked.y == y)
			{
				m_tiles.at(x).at(y)->highlight(true);
			}
			else
			{
				m_tiles.at(x).at(y)->highlight(false);
			}
		}
	}
}

void TileManager::progressType()
{
	if (m_currentType == setType::start)
	{
		sf::Vector2i pos = m_tiles.at(start.x).at(start.y)->next;
		while (pos != goal)
		{
			m_tiles.at(pos.x).at(pos.y)->path(true);
			pos = m_tiles.at(pos.x).at(pos.y)->next;
		}
		return;
	}
	if (m_currentType == setType::goal)
	{
		setHeatMap();
	}
	m_currentType = static_cast<setType>((static_cast<int>(m_currentType)) + 1);
}

void TileManager::setHeatMap()
{
	std::queue<std::pair<sf::Vector2i, int>> unsearched;
	unsearched.push(std::pair<sf::Vector2i, int>(goal, 0));

	while (!unsearched.empty())
	{
		sf::Vector2i pos = unsearched.front().first;
		int cost = unsearched.front().second;
		unsearched.pop();


		if (pos.x - 1 >= 0)
		{
			if (pos.y - 1 >= 0)
			{
				sf::Vector2i t = sf::Vector2i(pos.x - 1, pos.y - 1);
				if (!(m_tiles.at(t.x).at(t.y)->costSet()))
				{
					m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
					unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));

				}
			}
			{
				sf::Vector2i t = sf::Vector2i(pos.x - 1, pos.y);
				if (!(m_tiles.at(t.x).at(t.y)->costSet()))
				{
					m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
					unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));
				}
			}
			if (pos.y + 1 < TILE_WIDTH)
			{
				sf::Vector2i t = sf::Vector2i(pos.x - 1, pos.y + 1);
				if (!(m_tiles.at(t.x).at(t.y)->costSet()))
				{
					m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
					unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));
				}
			}
		}
		if (pos.y - 1 >= 0)
		{
			sf::Vector2i t = sf::Vector2i(pos.x, pos.y - 1);
			if (!(m_tiles.at(t.x).at(t.y)->costSet()))
			{
				m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
				unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));
			}
		}
		if (pos.y + 1 < TILE_WIDTH)
		{
			sf::Vector2i t = sf::Vector2i(pos.x, pos.y + 1);
			if (!(m_tiles.at(t.x).at(t.y)->costSet()))
			{
				m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
				unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));
			}
		}
		if (pos.x + 1 < TILE_WIDTH)
		{
			if (pos.y - 1 >= 0)
			{
				sf::Vector2i t = sf::Vector2i(pos.x + 1, pos.y - 1);
				if (!(m_tiles.at(t.x).at(t.y)->costSet()))
				{
					m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
					unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));
				}
			}
			{
				sf::Vector2i t = sf::Vector2i(pos.x + 1, pos.y);
				if (!(m_tiles.at(t.x).at(t.y)->costSet()))
				{
					m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
					unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));
				}
			}
			if (pos.y + 1 < TILE_WIDTH)
			{
				sf::Vector2i t = sf::Vector2i(pos.x + 1, pos.y + 1);
				if (!(m_tiles.at(t.x).at(t.y)->costSet()))
				{
					m_tiles.at(t.x).at(t.y)->setCost(cost + 1);
					unsearched.push(std::pair<sf::Vector2i, int>(t, cost + 1));
				}
			}
		}
	}

	unsearched.push(std::pair<sf::Vector2i, int>(goal, 0));

	while (!unsearched.empty())
	{
		sf::Vector2i pos = unsearched.front().first;
		int cost = unsearched.front().second;
		unsearched.pop();

		if (pos.x - 1 >= 0)
		{
			if (pos.y - 1 >= 0)
			{
				sf::Vector2i t = sf::Vector2i(pos.x - 1, pos.y - 1);
				if (!m_tiles.at(t.x).at(t.y)->processed)
				{
					m_tiles.at(t.x).at(t.y)->processed = true;
					unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
				}
			}
			{
				sf::Vector2i t = sf::Vector2i(pos.x - 1, pos.y);
				if (!m_tiles.at(t.x).at(t.y)->processed)
				{
					m_tiles.at(t.x).at(t.y)->processed = true;
					unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
				}
			}
			if (pos.y + 1 < TILE_WIDTH)
			{
				sf::Vector2i t = sf::Vector2i(pos.x - 1, pos.y + 1);
				if (!m_tiles.at(t.x).at(t.y)->processed)
				{
					m_tiles.at(t.x).at(t.y)->processed = true;
					unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
				}
			}
		}
		if (pos.y - 1 >= 0)
		{
			sf::Vector2i t = sf::Vector2i(pos.x, pos.y - 1);
			if (!m_tiles.at(t.x).at(t.y)->processed)
			{
				m_tiles.at(t.x).at(t.y)->processed = true;
				unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
			}
		}
		if (pos.y + 1 < TILE_WIDTH)
		{
			sf::Vector2i t = sf::Vector2i(pos.x, pos.y + 1);
			if (!m_tiles.at(t.x).at(t.y)->processed)
			{
				m_tiles.at(t.x).at(t.y)->processed = true;
				unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
			}
		}
		if (pos.x + 1 < TILE_WIDTH)
		{
			if (pos.y - 1 >= 0)
			{
				sf::Vector2i t = sf::Vector2i(pos.x + 1, pos.y - 1);
				if (!m_tiles.at(t.x).at(t.y)->processed)
				{
					m_tiles.at(t.x).at(t.y)->processed = true;
					unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
				}
			}
			{
				sf::Vector2i t = sf::Vector2i(pos.x + 1, pos.y);
				if (!m_tiles.at(t.x).at(t.y)->processed)
				{
					m_tiles.at(t.x).at(t.y)->processed = true;
					unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
				}
			}
			if (pos.y + 1 < TILE_WIDTH)
			{
				sf::Vector2i t = sf::Vector2i(pos.x + 1, pos.y + 1);
				if (!m_tiles.at(t.x).at(t.y)->processed)
				{
					m_tiles.at(t.x).at(t.y)->processed = true;
					unsearched.push(std::pair<sf::Vector2i, int>(t, m_tiles.at(t.x).at(t.y)->m_cost));
				}
			}
		}

		m_tiles.at(pos.x).at(pos.y)->processed = true;
		m_tiles.at(pos.x).at(pos.y)->setInt(cost);
	}

	

	for (int x = 0; x < TILE_WIDTH; x++)
	{
		for (int y = 0; y < TILE_WIDTH; y++)
		{
			sf::Vector2i lowest = sf::Vector2i(x, y);
			int cost = m_tiles.at(x).at(y)->m_cost;

			if (y - 1 >= 0)
			{
				sf::Vector2i t = sf::Vector2i(x, y - 1);
				if (m_tiles.at(t.x).at(t.y)->m_cost < cost)
				{
					lowest = t;
					cost = m_tiles.at(t.x).at(t.y)->m_cost;
				}
			}
			if (y + 1 < TILE_WIDTH)
			{
				sf::Vector2i t = sf::Vector2i(x, y + 1);
				if (m_tiles.at(t.x).at(t.y)->m_cost < cost)
				{
					lowest = t;
					cost = m_tiles.at(t.x).at(t.y)->m_cost;
				}
			}
			if (x - 1 >= 0)
			{
				{
					sf::Vector2i t = sf::Vector2i(x - 1, y);
					if (m_tiles.at(t.x).at(t.y)->m_cost < cost)
					{
						lowest = t;
						cost = m_tiles.at(t.x).at(t.y)->m_cost;
					}
				}
				if (y - 1 >= 0)
				{
					sf::Vector2i t = sf::Vector2i(x - 1, y - 1);
					if (m_tiles.at(t.x).at(t.y)->m_cost < cost)
					{
						lowest = t;
						cost = m_tiles.at(t.x).at(t.y)->m_cost;
					}
				}
				if (y + 1 < TILE_WIDTH)
				{
					sf::Vector2i t = sf::Vector2i(x - 1, y + 1);
					if (m_tiles.at(t.x).at(t.y)->m_cost < cost)
					{
						lowest = t;
						cost = m_tiles.at(t.x).at(t.y)->m_cost;
					}
				}
			}
			if (x + 1 < TILE_WIDTH)
			{
				{
					sf::Vector2i t = sf::Vector2i(x + 1, y);
					if (m_tiles.at(t.x).at(t.y)->m_cost <= cost)
					{
						lowest = t;
						cost = m_tiles.at(t.x).at(t.y)->m_cost;
					}
				}
				if (y - 1 >= 0)
				{
					sf::Vector2i t = sf::Vector2i(x + 1, y - 1);
					if (m_tiles.at(t.x).at(t.y)->m_cost <= cost)
					{
						lowest = t;
						cost = m_tiles.at(t.x).at(t.y)->m_cost;
					}
				}
				if (y + 1 < TILE_WIDTH)
				{
					sf::Vector2i t = sf::Vector2i(x + 1, y + 1);
					if (m_tiles.at(t.x).at(t.y)->m_cost < cost)
					{
						lowest = t;
						cost = m_tiles.at(t.x).at(t.y)->m_cost;
					}
				}
			}

			m_tiles.at(x).at(y)->next = lowest;
			m_tiles.at(x).at(y)->drawNext();
		}
	}
}

std::vector<sf::Vector2f> TileManager::getPoints()
{
	std::vector<sf::Vector2f> points;
	sf::Vector2i pos = start;
	while (pos != goal)
	{
		points.push_back(m_tiles.at(pos.x).at(pos.y)->getCenter());
		pos = m_tiles.at(pos.x).at(pos.y)->next;
	}
	points.push_back(m_tiles.at(goal.x).at(goal.y)->getCenter());
	return points;
}

void TileManager::changeCost(bool t_active)
{
	for (int x = 0; x < TILE_WIDTH; x++)
	{
		for (int y = 0; y < TILE_WIDTH; y++)
		{
			m_tiles.at(x).at(y)->m_costT->setFillColor((t_active) ? sf::Color::Transparent : sf::Color::White);
		}
	}
}

void TileManager::changeInt(bool t_active)
{
	for (int x = 0; x < TILE_WIDTH; x++)
	{
		for (int y = 0; y < TILE_WIDTH; y++)
		{
			m_tiles.at(x).at(y)->m_intT->setFillColor((t_active) ? sf::Color::Transparent : sf::Color::White);
		}
	}
}
