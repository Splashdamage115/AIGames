#pragma once

#include "Tile.h"

class TileManager
{
public:
	void init();
private:
	std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};

