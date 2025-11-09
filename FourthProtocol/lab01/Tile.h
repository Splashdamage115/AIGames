#pragma once

#include "Library.h"

enum class TileItem
{
	none, Frog, Snake, Donkey
};

enum class Player
{
	One, Two
};

struct Tile
{
	void initBody(bool t_player);

	std::shared_ptr<sf::RectangleShape> rect;
	std::shared_ptr<sf::Sprite> centerBody;
	TileItem tileItem;
	Player player;
	bool occupied = false;
	bool enemyOccupied = false;
};

class TileManager
{
public:
	void moveGameState();

	void Start();
	void Update();

	static sf::Texture FrogTexture;
	static sf::Texture SnakeTexture;
	static sf::Texture DonkeyTexture;
private:
	void PlaceTiles(int t_pos);
	void moveItems(int t_pos);
	void findTraversable(std::vector<int>& t_tile, std::vector<bool>& t_traversable, int t_pos);

	std::vector<Tile> m_tiles;
	std::vector<int>m_selectable;

	sf::Vector2f m_startPositionOffset = { 700.0f,50.0f };

	std::vector<bool> m_availableItems;

	bool m_moveGameState = false;

	int selectedTile = 0;
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
