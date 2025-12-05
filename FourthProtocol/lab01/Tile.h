#pragma once

#include "Library.h"
#include "AiDecisionAbstract.h"

enum class TileItem
{
	none, Frog, Snake, Donkey
};

enum class Player
{
	One, Two, none
};

struct Tile
{
	/*! \brief initialise the box with the correct character
	*
	*  set all the necessary data for the body and use it
	*/
	void initBody(Player owner);

	/*! \brief remove all data
	*
	*  remove all data from the object
	*/
	void clearBody();

	std::shared_ptr<sf::RectangleShape> rect;
	std::shared_ptr<sf::Sprite> centerBody;
	std::shared_ptr<sf::Text> tilePlaceValue;
	TileItem tileItem;
	Player player;
	bool occupied = false;
	bool enemyOccupied = false;
	sf::Vector2i position;
};

class TileManager
{
public:
	/*! \brief set the move game state to true
	*
	*  
	*/
	void moveGameState();

	/*! \brief initialise data for the class
	*
	*  load all assets, and set all data
	*/
	void Start();

	/*! \brief update all objects
	*
	*  update timings, and check for mouse inputs on the board
	*/
	void Update();

	/*! \brief check if anyone has won, and return the winner
	*
	*  loop through all potential 4 in rows and return the winner
	*/
	Player checkWinState(std::vector<Tile>& t_tiles);

	/*! \brief set all data for the game to complete
	*
	*	pass in the winner and set the data for it
	*/
	void gameOver(Player winner);

	bool gameOverCheck = false;

	static sf::Texture FrogTexture;
	static sf::Texture SnakeTexture;
	static sf::Texture DonkeyTexture;
private:
	/*! \brief change the state of the board, by placing an item
	*
	*	handle different player types and place items as the game goes on
	*/
	void PlaceTiles(int t_pos);
	/*! \brief handle the move items game state
	*
	*  move items around the area, and handle the clicks and the ai clicks for this
	*/
	void moveItems(int t_pos);
	/*! \brief find all traversable tiles for the character
	*
	*	return a list of all movement positions, and a boolean wether that position is reachable or not
	*/
	void findTraversable(std::vector<int>& t_tile, std::vector<bool>& t_traversable, int t_pos);
	/*! \brief make a delayed placement for the ai after a certain wait
	*
	*
	*/
	void executeDelayedAIPlacement();
	/*! \brief make a delayed move for the ai after a certain wait
	*
	*
	*/
	void executeDelayedAIMovement();
	/*! \brief make a delayed placement for the player after a certain wait
	*
	*
	*/
	void executeDelayedPlayerAIPlacement();
	/*! \brief make a delayed move for the player after a certain wait
	*
	*
	*/
	void executeDelayedPlayerAIMovement();

	std::shared_ptr<AiDecisionAbstract> m_decision;
	std::shared_ptr<AiDecisionAbstract> m_playerDecision;

	std::vector<Tile> m_tiles;
	std::vector<int>m_selectable;

	sf::Vector2f m_startPositionOffset = { 700.0f,50.0f };

	bool m_moveGameState = false;
	bool m_pendingAIPlacement = false;
	bool m_pendingAIMovement = false;
	bool m_pendingPlayerAIPlacement = false;
	bool m_pendingPlayerAIMovement = false;

	int selectedTile = 0;

	Player winner = Player::none;
};

/*! \brief return the texture needed for the tile
*
*
*/
static sf::Texture& getTexture(TileItem textureType)
{
	switch (textureType)
	{
	case TileItem::none:
		return TileManager::FrogTexture; // Default fallback
	case TileItem::Frog:
		return TileManager::FrogTexture;
	case TileItem::Snake:
		return TileManager::SnakeTexture;
	case TileItem::Donkey:
		return TileManager::DonkeyTexture;
	default:
		return TileManager::FrogTexture; // Default fallback
	}
}
