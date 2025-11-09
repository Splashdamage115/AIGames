#pragma once

#include "Library.h"
#include "Tile.h"

class CharacterSelection
{
public:
	void Start();
	void Update();
	void ChangedItem();
private:
	sf::Vector2f m_startPositionOffset = { 380.0f, 50.0f };
	std::vector<Tile> m_selectionTiles;
	int m_selectedTile = 0;
};

