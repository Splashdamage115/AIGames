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
	void initBody(Player owner);
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
	void moveGameState();

	void Start();
	void Update();

	Player checkWinState(std::vector<Tile>& t_tiles);
	void gameOver(Player winner);

	bool gameOverCheck = false;

	static sf::Texture FrogTexture;
	static sf::Texture SnakeTexture;
	static sf::Texture DonkeyTexture;
private:
	void PlaceTiles(int t_pos);
	void moveItems(int t_pos);
	void findTraversable(std::vector<int>& t_tile, std::vector<bool>& t_traversable, int t_pos);

	std::shared_ptr<AiDecisionAbstract> m_decision;

	std::vector<Tile> m_tiles;
	std::vector<int>m_selectable;

	sf::Vector2f m_startPositionOffset = { 700.0f,50.0f };

	bool m_moveGameState = false;

	int selectedTile = 0;

	Player winner = Player::none;
};

static sf::Texture& getTexture(TileItem textureType)
{
	switch (textureType)
	{
	case TileItem::none:
		break;
	case TileItem::Frog:
		return TileManager::FrogTexture;
		break;
	case TileItem::Snake:
		return TileManager::SnakeTexture;
		break;
	case TileItem::Donkey:
		return TileManager::DonkeyTexture;
		break;
	default:
		break;
	}
	//return sf::Texture();
}
