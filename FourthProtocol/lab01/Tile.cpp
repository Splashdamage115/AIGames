#include "Tile.h"
#include "RenderObject.h"
#include "Game.h"
#include "Update.h"

sf::Texture TileManager::FrogTexture;
sf::Texture TileManager::SnakeTexture;
sf::Texture TileManager::DonkeyTexture;

void TileManager::moveGameState()
{
	m_moveGameState = true;
}

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

	for (int i = 0; i < 5; i++)
		m_availableItems.emplace_back(true);
}

void TileManager::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
		{
			if (m_tiles.at(i).rect->getGlobalBounds().contains(sf::Vector2f(static_cast<float>(Game::mousePosition.x), static_cast<float>(Game::mousePosition.y))))
			{
				if (m_moveGameState)
				{
					moveItems(i);
				}
				else
				{
					PlaceTiles(i);
				}
			}
		}
	}
}

void TileManager::PlaceTiles(int t_pos)
{
	if (!m_tiles.at(t_pos).occupied && Game::selectedItem != TileItem::none)
	{
		m_tiles.at(t_pos).tileItem = Game::selectedItem;
		m_tiles.at(t_pos).enemyOccupied = (!Game::playerOneTurn) ? false : true;
		m_tiles.at(t_pos).initBody(true);

		Game::getInstance().PlacedTile();

		// HANDLE THE AI HERE
		int chosenSpot = 0;
		do {
			chosenSpot = rand() % (TILES_SIZE * TILES_SIZE);
		} while (m_tiles.at(chosenSpot).occupied);

		int chosenItem = 0;
		do {
			chosenItem = rand() % 5;
		} while (!m_availableItems.at(chosenItem));

		m_availableItems.at(chosenItem) = false;

		TileItem item = TileItem::Donkey;
		if (chosenItem == 0) item = TileItem::Frog;
		if (chosenItem == 1) item = TileItem::Snake;
		
		m_tiles.at(chosenSpot).tileItem = item;
		m_tiles.at(chosenSpot).enemyOccupied = (!Game::playerOneTurn) ? false : true;
		m_tiles.at(chosenSpot).initBody(false);

		bool nextGameState = true;

		for (int i = 0; i < m_availableItems.size(); i++)
		{
			if (m_availableItems.at(i))
				nextGameState = false;
		}

		if (nextGameState)
		{
			Game::getInstance().changeGameState(Game::GameState::move);
		}
	}
}

void TileManager::moveItems(int t_pos)
{
	if (m_tiles.at(t_pos).occupied && !m_tiles.at(t_pos).enemyOccupied)
	{
		selectedTile = t_pos;

		for (int i = 0; i < m_tiles.size(); i++)
		{
			m_tiles.at(i).rect->setFillColor(sf::Color::Transparent);
		}

		std::vector<int> moveTiles;
		std::vector<bool> checkable;

		findTraversable(moveTiles, checkable, t_pos);

		m_selectable.clear();
		for (int i = 0; i < moveTiles.size(); i++)
		{
			if (checkable.at(i))
			{
				m_tiles.at(moveTiles.at(i)).rect->setFillColor(sf::Color(255, 255, 255, 80));
				m_selectable.emplace_back(moveTiles.at(i));
			}
		}
	}
	else
	{
		bool moved = false;
		for (int i = 0; i < m_selectable.size(); i++)
		{
			if (t_pos == m_selectable.at(i))
			{
				// handle moving here
				std::cout << "MOVING FROM " << selectedTile << " TO " << t_pos << "\n";

				m_tiles.at(t_pos).tileItem = m_tiles.at(selectedTile).tileItem;
				m_tiles.at(selectedTile).tileItem = TileItem::none;
				m_tiles.at(selectedTile).initBody(false);
				m_tiles.at(t_pos).initBody(true);
				moved = true;
				break;
			}
		}
		if (moved)
		{
			int foundAmt = 0;
			int skips = rand() % 5;
			for (int i = 0; i < m_tiles.size(); i++)
			{
				if (m_tiles.at(i).tileItem == TileItem::none) continue;
				if (!m_tiles.at(i).enemyOccupied) continue;

				if (foundAmt == skips)
				{
					std::vector<int> moveTiles;
					std::vector<bool> checkable;
					findTraversable(moveTiles, checkable, i);

					int traversableAmt = 0;
					for (int j = 0; j < moveTiles.size(); j++)
					{
						if(checkable.at(j))
							traversableAmt++;
					}

					int selected = rand() % traversableAmt;

					m_tiles.at(moveTiles.at(selected)).tileItem = m_tiles.at(i).tileItem;
					m_tiles.at(i).tileItem = TileItem::none;
					m_tiles.at(moveTiles.at(selected)).initBody(false);
					m_tiles.at(i).initBody(false);
					moved = false;
					return;
				}
				else
				{
					foundAmt++;
				}
			}
			moved = false;
		}
	}
}

void TileManager::findTraversable(std::vector<int>& t_tile, std::vector<bool>& t_traversable, int t_pos)
{
	switch (m_tiles.at(t_pos).tileItem)
	{
	case TileItem::none:
		std::cout << "ERRRRORRR\n";
		break;
	case TileItem::Frog:
		t_tile.emplace_back(t_pos - 1);
		t_tile.emplace_back(t_pos + 1);
		t_tile.emplace_back(t_pos - TILES_SIZE);
		t_tile.emplace_back(t_pos - TILES_SIZE - 1);
		t_tile.emplace_back(t_pos - TILES_SIZE + 1);
		t_tile.emplace_back(t_pos + TILES_SIZE);
		t_tile.emplace_back(t_pos + TILES_SIZE - 1);
		t_tile.emplace_back(t_pos + TILES_SIZE + 1);
		break;
	case TileItem::Snake:
		t_tile.emplace_back(t_pos - 1);
		t_tile.emplace_back(t_pos + 1);
		t_tile.emplace_back(t_pos - TILES_SIZE);
		t_tile.emplace_back(t_pos - TILES_SIZE - 1);
		t_tile.emplace_back(t_pos - TILES_SIZE + 1);
		t_tile.emplace_back(t_pos + TILES_SIZE);
		t_tile.emplace_back(t_pos + TILES_SIZE - 1);
		t_tile.emplace_back(t_pos + TILES_SIZE + 1);
		break;
	case TileItem::Donkey:
		t_tile.emplace_back(t_pos - 1);
		t_tile.emplace_back(t_pos + 1);
		t_tile.emplace_back(t_pos - TILES_SIZE);
		t_tile.emplace_back(t_pos + TILES_SIZE);
		break;
	default:
		break;
	}

	for (int i = 0; i < t_tile.size(); i++)
	{
		if (t_tile.at(i) < 0 || t_tile.at(i) >= TILES_SIZE * TILES_SIZE)
		{
			t_traversable.emplace_back(false);
			continue;
		}
		if (t_pos % TILES_SIZE == 0)
		{
			if (t_tile.at(i) == t_pos - 1)
			{
				t_traversable.emplace_back(false);
				continue;
			}
		}
		if (t_pos % TILES_SIZE == TILES_SIZE - 1)
		{
			if (t_tile.at(i) == t_pos + 1)
			{
				t_traversable.emplace_back(false);
				continue;
			}
		}

		if (t_pos < TILES_SIZE)
		{
			if (t_tile.at(i) == t_pos - TILES_SIZE)
			{
				t_traversable.emplace_back(false);
				continue;
			}
		}
		if (t_pos > (TILES_SIZE * TILES_SIZE) - TILES_SIZE)
		{
			if (t_tile.at(i) == t_pos + TILES_SIZE)
			{
				t_traversable.emplace_back(false);
				continue;
			}
		}

		if (m_tiles.at(t_tile.at(i)).occupied)
		{
			t_traversable.emplace_back(false);
			continue;
		}

		t_traversable.emplace_back(true);
	}
}

void Tile::initBody(bool t_player)
{
	if (tileItem == TileItem::none)
	{
		centerBody = nullptr;
		occupied = false;
		return;
	}
	centerBody = std::make_shared<sf::Sprite>(getTexture(tileItem));

	centerBody->setPosition(rect->getPosition());
	centerBody->setScale(sf::Vector2f(3.f, 3.f));

	player = (t_player) ? Player::One : Player::Two;

	switch (player)
	{
	case Player::One:
		// dont change colour
		break;
	case Player::Two:
		centerBody->setColor(sf::Color::Red);
		enemyOccupied = true;
		break;
	}

	RenderObject::getInstance().addNewRenderObject(centerBody, 2);

	occupied = true;
}
