#pragma once

#include "Library.h"
#include "Tile.h"

class CharacterSelection
{
public:
	/*! \brief initialise data
	*
	*  initialise the standard data for the visual of the left bar,
	*  this is for the selection of what the player is placing
	*/
	void Start();


	/*! \brief check for clicked item
	*
	*  check all placeable items and highlight one
	*  unhighlight if not selected
	*/
	void Update();


	/*! \brief unselect item
	*
	*  unselect item, called from game loop
	*/
	void ChangedItem();
private:
	sf::Vector2f m_startPositionOffset = { 380.0f, 50.0f };
	std::vector<Tile> m_selectionTiles;
	int m_selectedTile = 0;


};

