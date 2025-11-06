#include "Tile.h"
#include "RenderObject.h"
#include "Game.h"
#include "Update.h"

sf::Texture TileManager::FrogTexture;
sf::Texture TileManager::SnakeTexture;
sf::Texture TileManager::DonkeyTexture;

void TileManager::Start()
{
	if (!FrogTexture.loadFromFile("./ASSETS/IMAGES/FrogLowPixel.png"))
	{
		std::cout << "COULDNT LOAD FROG TEXTURE\n";
	}
	if (!SnakeTexture.loadFromFile("./ASSETS/IMAGES/SnakeLowPixel.png"))
	{
		std::cout << "COULDNT LOAD SNAKE TEXTURE\n";
	}
	if (!DonkeyTexture.loadFromFile("./ASSETS/IMAGES/DonkeyLowPixel.png"))
	{
		std::cout << "COULDNT LOAD DONKEY TEXTURE\n";
	}

	for (int x = 0; x < TILES_SIZE; x++) 
	{
		for (int y = 0; y < TILES_SIZE; y++) 
		{
			// initilise the body
			std::shared_ptr<sf::RectangleShape> tile = std::make_shared<sf::RectangleShape>(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			tile->setPosition(sf::Vector2f((TILE_SIZE + TILE_OFFSET) * x, (TILE_SIZE + TILE_OFFSET) * y) + m_startPositionOffset);
			tile->setFillColor(sf::Color::Transparent);
			tile->setOutlineColor(sf::Color::White);
			tile->setOutlineThickness(1.f);
			RenderObject::getInstance().addNewRenderObject(tile, 1);

			Tile newTile;
			newTile.rect = tile;

			m_tiles.push_back(newTile);
		}
	}

	Update::append([this]() { this->Update(); });
}

void TileManager::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
		{
			if (m_tiles.at(i).rect->getGlobalBounds().contains(sf::Vector2f(static_cast<float>(Game::mousePosition.x), static_cast<float>(Game::mousePosition.y))))
			{
				if (!m_tiles.at(i).occupied)
				{
					m_tiles.at(i).tileItem = static_cast<TileItem>((rand() % 3) + 1);
					m_tiles.at(i).initBody();

					Game::playerOneTurn = !Game::playerOneTurn;
				}
			}
		}
	}
}

void Tile::initBody()
{
	if (tileItem == TileItem::none)
	{
		centerBody = nullptr;
		occupied = false;
	}
	centerBody = std::make_shared<sf::Sprite>(getTexture(tileItem));

	centerBody->setPosition(rect->getPosition());
	centerBody->setScale(sf::Vector2f(3.f, 3.f));

	player = (!Game::playerOneTurn) ? Player::One : Player::Two;

	switch (player)
	{
	case Player::One:
		// dont change colour
		break;
	case Player::Two:
		centerBody->setColor(sf::Color::Red);
		break;
	}

	RenderObject::getInstance().addNewRenderObject(centerBody, 2);

	occupied = true;
}
