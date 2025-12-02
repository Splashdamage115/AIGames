#include "CharacterSelection.h"
#include "RenderObject.h"
#include "Game.h"
#include "Update.h"

void CharacterSelection::Start()
{
	for (int i = 0; i < 5; i++)
	{
		// initilise the body
		std::shared_ptr<sf::RectangleShape> tile = std::make_shared<sf::RectangleShape>(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		tile->setPosition(sf::Vector2f(0.0f, (TILE_SIZE + TILE_OFFSET) * i) + m_startPositionOffset);
		tile->setFillColor(sf::Color::Transparent);
		tile->setOutlineColor(sf::Color::White);
		tile->setOutlineThickness(1.f);
		RenderObject::getInstance().addNewRenderObject(tile, 1);

		Tile newTile;
		newTile.rect = tile;

		m_selectionTiles.push_back(newTile);
	}

	m_selectionTiles.at(0).tileItem = TileItem::Frog;
	m_selectionTiles.at(1).tileItem = TileItem::Snake;
	m_selectionTiles.at(2).tileItem = TileItem::Donkey;
	m_selectionTiles.at(3).tileItem = TileItem::Donkey;
	m_selectionTiles.at(4).tileItem = TileItem::Donkey;

	for (int i = 0; i < 5; i++)
	{
		m_selectionTiles.at(i).initBody(Player::One);
	}

	Update::append([this]() {this->Update(); });
}

void CharacterSelection::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		for (int i = 0; i < 5; i++)
		{
			if (m_selectionTiles.at(i).rect->getGlobalBounds().contains(sf::Vector2f(static_cast<float>(Game::mousePosition.x), static_cast<float>(Game::mousePosition.y))))
			{
				if (m_selectionTiles.at(i).tileItem == TileItem::none) continue;

				m_selectionTiles.at(i).rect->setFillColor(sf::Color(255, 255, 255, 60));
				Game::selectedItem = m_selectionTiles.at(i).tileItem;
				m_selectedTile = i;
			}
			else
			{
				m_selectionTiles.at(i).rect->setFillColor(sf::Color::Transparent);
			}
		}
	}
}

void CharacterSelection::ChangedItem()
{
	if (m_selectedTile == -1) return;
	m_selectionTiles.at(m_selectedTile).clearBody();
	m_selectedTile = -1;
}
