#include "AiDecisionAbstract.h"
#include "Tile.h"

void AiDecisionAbstract::init()
{
	for (int i = 0; i < 5; i++)
		m_availableItems.emplace_back(true);
}

PlacementType AiDecisionAbstract::DecidePlacement(std::vector<Tile>& tiles,
	std::function<Player(std::vector<Tile>&)> t_winFunction)
{
	PlacementType place;

	// handle chosen position here
	int chosenSpot = 0;
	int highestHeurusticValue = -100;
	int bestPosition = 0;
	int currentHeurustic = 0;

	std::vector<Tile> tempBoard = tiles;
	//do {
	//	chosenSpot = rand() % (TILES_SIZE * TILES_SIZE);
	//} while (tiles.at(chosenSpot).occupied);

	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (tiles.at(i).occupied) continue;

		tempBoard = tiles;
		tempBoard.at(i).enemyOccupied = true;
		Player winner = t_winFunction(tempBoard);

		if (winner != Player::Two)
			currentHeurustic = calculateHeurusticValue(tempBoard);
		else
			currentHeurustic = 1000000;

		//std::cout << "Board position : " << i << " cost is : " << currentHeurustic << "\n";

		if (currentHeurustic > highestHeurusticValue)
		{
			bestPosition = i;
			highestHeurusticValue = currentHeurustic;
		}
	}
	chosenSpot = bestPosition;

	// handle choosing of item
	int chosenItem = 0;
	do {
		chosenItem = rand() % 5;
	} while (!m_availableItems.at(chosenItem));

	m_availableItems.at(chosenItem) = false;

	TileItem item = TileItem::Donkey;
	if (chosenItem == 0) item = TileItem::Frog;
	if (chosenItem == 1) item = TileItem::Snake;
	
	place.placementType = item;
	place.placementPosition = chosenSpot;

	AmtPlaceable--;
	if (AmtPlaceable == 0)
		place.allPlaced = true;

	return place;
}

int AiDecisionAbstract::calculateHeurusticValue(std::vector<Tile>& proposedState)
{
	int amtOfNpc = 5 - (AmtPlaceable - 1);
	int value = 1000;

	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (!proposedState.at(i).enemyOccupied) continue;

		for (int j = 0; j < TILES_SIZE * TILES_SIZE; j++)
		{
			if (i == j) continue;
		
			if (!proposedState.at(j).enemyOccupied) continue;
		
			// further distance decreases value more
			value -= distance(sf::Vector2f(proposedState.at(i).position.x, proposedState.at(i).position.y), sf::Vector2f(proposedState.at(j).position.x, proposedState.at(j).position.y));
		}
		int distanceToCenter = distance(sf::Vector2f(proposedState.at(i).position.x, proposedState.at(i).position.y), sf::Vector2f(2.f, 2.f));
		value -= distanceToCenter; // prefer central positions
	}



	return value;
}

MovementType AiDecisionAbstract::DecideMovement(std::vector<Tile>& tiles, 
	std::function<void(std::vector<int>& , std::vector<bool>&, int)> t_movementFunction,
	std::function<Player(std::vector<Tile>&)> t_winFunction)
{
	MovementType t;

	int foundAmt = 0;
	int skips = rand() % 5;
	int chosenTile = 0;
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i).tileItem == TileItem::none) continue;
		if (!tiles.at(i).enemyOccupied) continue;

		if (foundAmt == skips)
		{
			chosenTile = i;
			std::vector<int> moveTiles;
			std::vector<bool> checkable;
			t_movementFunction(moveTiles, checkable, i);

			int traversableAmt = 0;
			for (int j = 0; j < moveTiles.size(); j++)
			{
				if (checkable.at(j))
					traversableAmt++;
			}

			// error handling if current character has no potential moves
			if (traversableAmt == 0)
			{
				i = 0;
				foundAmt = 0;
				skips = rand() % 5;
				continue;
			}

			// select a move randomly
			int selected = rand() % traversableAmt;
			int chosenIndex = -1;
			int passed = 0;

			for (int j = 0; j < moveTiles.size(); j++)
			{
				if (checkable.at(j))
				{
					if (passed == selected)
					{
						chosenIndex = j;
						break;
					}
					else
					{ 
						passed++;
					}
				}
			}

			t.destination = moveTiles.at(chosenIndex);
			t.currentPos = i;
			break;
		}
		else
		{
			foundAmt++;
		}
	}


	return t;
}
