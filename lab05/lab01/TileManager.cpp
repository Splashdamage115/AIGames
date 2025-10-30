#include "TileManager.h"

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
}
