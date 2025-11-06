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
	void initBody();

	std::shared_ptr<sf::RectangleShape> rect;
	std::shared_ptr<sf::Sprite> centerBody;
	TileItem tileItem;
	Player player;
	bool occupied = false;
};

class TileManager
{
public:
	void Start();
	void Update();

	static sf::Texture FrogTexture;
	static sf::Texture SnakeTexture;
	static sf::Texture DonkeyTexture;
private:
	std::vector<Tile> m_tiles;

	sf::Vector2f m_startPositionOffset = { 700.0f,50.0f };
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
