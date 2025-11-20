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
			newTile.position = sf::Vector2i(x, y);
			newTile.tilePlaceValue = std::make_shared<sf::Text>(Game::m_jerseyFont);
			newTile.tilePlaceValue->setPosition(newTile.rect->getPosition());
			newTile.tilePlaceValue->setCharacterSize(24u);
			RenderObject::getInstance().addNewRenderObject(newTile.tilePlaceValue, 4);

			m_tiles.push_back(newTile);
		}
	}

	m_decision = std::make_shared<AiDecisionAbstract>();
	m_decision->init();

	Update::append([this]() { this->Update(); });
}

void TileManager::Update()
{
	if (gameOverCheck)
	{
		if (winner == Player::One)
		{
			std::cout << "GAME OVER PLAYER 1 WINS\n";
		}
		else if (winner == Player::Two)
		{
			std::cout << "GAME OVER PLAYER 2 WINS\n";
		}
	}

	//for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	//{
	//	if (m_tiles.at(i).occupied)
	//	{
	//		m_tiles.at(i).rect->setOutlineColor(sf::Color::Red);
	//	}
	//	else
	//	{
	//		m_tiles.at(i).rect->setOutlineColor(sf::Color::White);
	//
	//	}
	//}

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

// returns the player that wins
Player TileManager::checkWinState(std::vector<Tile> & t_tiles)
{
	int foundAmtPlayer = 0;
	int foundAmtEnemy = 0;
	int horizontalCheck = 0;

	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (t_tiles.at(i).occupied)
		{
			// cover wrap around
			if (i % TILES_SIZE == 0)
			{
				foundAmtPlayer = 0;
				foundAmtEnemy = 0;
			}
			if (t_tiles.at(i).player == Player::One)
			{
				foundAmtPlayer++;
				foundAmtEnemy = 0;

				horizontalCheck = 0;
				// CHECK LEFT / RIGHT
				for (int v = i; v < TILES_SIZE * TILES_SIZE; v += TILES_SIZE)
				{
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::One)
						{
							horizontalCheck++;

							if (horizontalCheck == 4)
							{
								return Player::One;
							}
							continue;
						}
					}
					break;
				}
				horizontalCheck = 0;

				for (int v = i; v >= 0; v -= TILES_SIZE)
				{
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::One)
						{
							horizontalCheck++;

							if (horizontalCheck == 4)
							{
								return Player::One;
							}
							continue;
						}
					}
					break;
				}
				horizontalCheck = 0;


				for (int v = i; v < TILES_SIZE * TILES_SIZE; v += TILES_SIZE + 1)
				{
					if (v % TILES_SIZE == 0)
					{
						if (v != 0 && v != 1)
							break;
					}
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::One)
						{
							horizontalCheck++;
							
							if (horizontalCheck == 4)
							{
								return Player::One;
							}
							continue;
						}
					}
					break;
				}
				horizontalCheck = 0;

				for (int v = i; v >= 0; v -= TILES_SIZE - 1)
				{
					if (v % TILES_SIZE == 0)
					{
						if(v != 0 && v != 1)
							break;
					}
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::One)
						{
							horizontalCheck++;

							if (horizontalCheck == 4)
							{
								return Player::One;
							}
							continue;
						}
					}
					break;
				}

				if (foundAmtPlayer == 4)
				{
					return Player::One;
				}

				continue;
			}
			else
			{
				foundAmtPlayer = 0;
			}



			if (t_tiles.at(i).player == Player::Two)
			{
				foundAmtEnemy++;
				foundAmtPlayer = 0;

				horizontalCheck = 0;
				// CHECK LEFT / RIGHT
				for (int v = i; v < TILES_SIZE * TILES_SIZE; v += TILES_SIZE)
				{
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::Two)
						{
							horizontalCheck++;

							if (horizontalCheck == 4)
							{
								return Player::Two;
							}
							continue;
						}
					}
					break;
				}
				horizontalCheck = 0;

				for (int v = i; v >= 0; v -= TILES_SIZE)
				{
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::Two)
						{
							horizontalCheck++;

							if (horizontalCheck == 4)
							{
								return Player::Two;
							}
							continue;
						}
					}
					break;
				}
				horizontalCheck = 0;


				for (int v = i; v < TILES_SIZE * TILES_SIZE; v += TILES_SIZE + 1)
				{
					if (v % TILES_SIZE == 0)
					{
						if (v != 0 && v != 1)
							break;
					}
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::Two)
						{
							horizontalCheck++;

							if (horizontalCheck == 4)
							{
								return Player::Two;
							}
							continue;
						}
					}
					break;
				}
				horizontalCheck = 0;

				for (int v = i; v >= 0; v -= TILES_SIZE - 1)
				{
					if (v % TILES_SIZE == 0)
					{
						if (v != 0 && v != 1)
							break;
					}
					if (t_tiles.at(v).occupied)
					{
						if (t_tiles.at(v).player == Player::Two)
						{
							horizontalCheck++;

							if (horizontalCheck == 4)
							{
								return Player::Two;
							}
							continue;
						}
					}
					break;
				}

				if (foundAmtEnemy == 4)
				{
					return Player::Two;
				}

				continue;
			}
			else
			{
				foundAmtEnemy = 0;
			}
		}
		foundAmtPlayer = 0;
		foundAmtEnemy = 0;
	}
	return Player::none;
}

void TileManager::gameOver(Player t_winner)
{
	winner = t_winner;
	gameOverCheck = true;

	Game::getInstance().winner = t_winner;
	Game::getInstance().GameOver();
}

void TileManager::PlaceTiles(int t_pos)
{
	if (!m_tiles.at(t_pos).occupied && Game::selectedItem != TileItem::none)
	{
		m_tiles.at(t_pos).tileItem = Game::selectedItem;
		m_tiles.at(t_pos).enemyOccupied = (!Game::playerOneTurn) ? false : true;
		m_tiles.at(t_pos).initBody(Player::One);

		
		Player winningPlayer = checkWinState(m_tiles);
		if (winningPlayer != Player::none) gameOver(winningPlayer);

		Game::getInstance().PlacedTile();

		// HANDLE THE AI HERE

		auto t = m_decision->DecidePlacement(m_tiles, [this](std::vector<Tile>& t_tiles) { return this->checkWinState(t_tiles); });

		// handle actual placement
		m_tiles.at(t.placementPosition).tileItem = t.placementType;
		m_tiles.at(t.placementPosition).enemyOccupied = (!Game::playerOneTurn) ? false : true;
		m_tiles.at(t.placementPosition).initBody(Player::Two);

		// handle next move
		bool nextGameState = t.allPlaced;

		if (nextGameState)
		{
			Game::getInstance().changeGameState(Game::GameState::move);
		}

		winningPlayer = checkWinState(m_tiles);
		if (winningPlayer != Player::none) gameOver(winningPlayer);
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
		// moving Player token
		bool moved = false;
		for (int i = 0; i < m_selectable.size(); i++)
		{
			if (t_pos == m_selectable.at(i))
			{
				// handle moving here
				std::cout << "MOVING FROM " << selectedTile << " TO " << t_pos << "\n";

				m_tiles.at(t_pos).tileItem = m_tiles.at(selectedTile).tileItem;
				m_tiles.at(t_pos).initBody(Player::One);

				m_tiles.at(selectedTile).clearBody();
				moved = true;

				Player winningPlayer = checkWinState(m_tiles);
				if (winningPlayer != Player::none) gameOver(winningPlayer);

				break;
			}
		}
		if (moved)
		{
			// moving ai token
			auto AiMove = m_decision->DecideMovement(m_tiles, [this](std::vector<int>& a, std::vector<bool>& b, int c) { this->findTraversable(a, b, c); }, [this](std::vector<Tile>& t_tiles) { return this->checkWinState(t_tiles); });

			m_tiles.at(AiMove.destination).tileItem = m_tiles.at(AiMove.currentPos).tileItem;
			m_tiles.at(AiMove.destination).enemyOccupied = true;
			m_tiles.at(AiMove.destination).initBody(Player::Two);

			m_tiles.at(AiMove.currentPos).clearBody();
			moved = false;

			m_selectable.clear();
			selectedTile = -1;

			Player winningPlayer = checkWinState(m_tiles);
			if (winningPlayer != Player::none) gameOver(winningPlayer);

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

		// Hops
		t_tile.emplace_back(t_pos - 2);
		t_tile.emplace_back(t_pos + 2);
		t_tile.emplace_back(t_pos - (TILES_SIZE * 2));
		t_tile.emplace_back(t_pos - (TILES_SIZE * 2) - 2);
		t_tile.emplace_back(t_pos - (TILES_SIZE * 2) + 2);
		t_tile.emplace_back(t_pos + (TILES_SIZE * 2));
		t_tile.emplace_back(t_pos + (TILES_SIZE * 2) - 2);
		t_tile.emplace_back(t_pos + (TILES_SIZE * 2) + 2);
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

		if (m_tiles.at(t_tile.at(i)).occupied)
		{
			t_traversable.emplace_back(false);
			continue;
		}

		int srcX = t_pos % TILES_SIZE;
		int srcY = t_pos / TILES_SIZE;
		int candX = t_tile.at(i) % TILES_SIZE;
		int candY = t_tile.at(i) / TILES_SIZE;

		if (std::abs(srcX - candX) > 2 || std::abs(srcY - candY) > 2)
		{
			t_traversable.emplace_back(false);
			continue;
		}

		if (std::abs(srcX - candX) == 2 || std::abs(srcY - candY) == 2)
		{

			if (t_tile.at(i) == t_pos - 2)
			{
				if (!m_tiles.at(t_pos - 1).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}
			if (t_tile.at(i) == t_pos + 2)
			{
				if (!m_tiles.at(t_pos + 1).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}
			if (t_tile.at(i) == t_pos - (TILES_SIZE * 2))
			{
				if (!m_tiles.at(t_pos - TILES_SIZE).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}
			if (t_tile.at(i) == t_pos - (TILES_SIZE * 2) - 2)
			{
				if (!m_tiles.at(t_pos - (TILES_SIZE) - 1).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}
			if (t_tile.at(i) == t_pos - (TILES_SIZE * 2) + 2)
			{
				if (!m_tiles.at(t_pos - (TILES_SIZE) + 1).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}
			if (t_tile.at(i) == t_pos + (TILES_SIZE * 2))
			{
				if (!m_tiles.at(t_pos + (TILES_SIZE)).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}
			if (t_tile.at(i) == t_pos + (TILES_SIZE * 2) - 2)
			{
				if (!m_tiles.at(t_pos + (TILES_SIZE) - 1).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}
			if (t_tile.at(i) == t_pos + (TILES_SIZE * 2) + 2)
			{
				if (!m_tiles.at(t_pos + (TILES_SIZE) + 1).occupied)
				{
					t_traversable.emplace_back(false);
					continue;
				}
			}

			t_traversable.emplace_back(true);
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
		if (t_pos >= (TILES_SIZE * TILES_SIZE) - TILES_SIZE)
		{
			if (t_tile.at(i) == t_pos + TILES_SIZE)
			{
				t_traversable.emplace_back(false);
				continue;
			}
		}

		t_traversable.emplace_back(true);
	}
}

void Tile::initBody(Player owner)
{
	if (tileItem == TileItem::none)
	{
		clearBody();
		return;
	}
	centerBody = std::make_shared<sf::Sprite>(getTexture(tileItem));

	centerBody->setPosition(rect->getPosition());
	centerBody->setScale(sf::Vector2f(3.f, 3.f));

	player = owner;

	switch (owner)
	{
	case Player::One:
		// dont change colour
		enemyOccupied = false;
		break;
	case Player::Two:
		centerBody->setColor(sf::Color::Red);
		enemyOccupied = true;
		break;
	}

	RenderObject::getInstance().addNewRenderObject(centerBody, 2);

	occupied = true;
}

void Tile::clearBody()
{
	centerBody = nullptr;
	occupied = false;
	enemyOccupied = false;
	tileItem = TileItem::none;
	player = Player::none;
}
