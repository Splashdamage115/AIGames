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

	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (tiles.at(i).occupied) continue;

		tempBoard = tiles;
		tempBoard.at(i).enemyOccupied = true;
		tempBoard.at(i).occupied = true;
		tempBoard.at(i).player = Player::Two;

		currentHeurustic = calculateHeurusticValue(tempBoard, t_winFunction, Player::Two);

		Player p = t_winFunction(tempBoard);
		switch (p)
		{
		case Player::One:
			std::cout << "player One to win\n";
			break;
		case Player::Two:
			std::cout << "player Two to win\n";
			break;
		case Player::none:
			break;
		default:
			break;
		}

		//std::cout << "Board position : " << i << " cost is : " << currentHeurustic << "\n";

		if (currentHeurustic > highestHeurusticValue)
		{
			bestPosition = i;
			highestHeurusticValue = currentHeurustic;
		}
		tiles.at(i).tilePlaceValue->setString(std::to_string(currentHeurustic));
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

int AiDecisionAbstract::calculateHeurusticValue(std::vector<Tile>& proposedState, std::function<Player(std::vector<Tile>&)> t_winFunction, Player winnerEval)
{
	// if the next move allows the AI to win, make that move (stop calculating), as it is the most valuable
	if (t_winFunction(proposedState) == winnerEval) return 999999999;

	int amtOfNpc = 5 - (AmtPlaceable - 1);
	int value = 1000;
	int countInLine = 0;

	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (!(proposedState.at(i).player == winnerEval)) continue;

		for (int j = 0; j < TILES_SIZE * TILES_SIZE; j++)
		{
			if (i == j) continue;
			if (!(proposedState.at(j).player == winnerEval)) continue;

			// further distance between objects decreases value more
			int distanceVal = distance(sf::Vector2f(proposedState.at(i).position.x, proposedState.at(i).position.y), sf::Vector2f(proposedState.at(j).position.x, proposedState.at(j).position.y));
			value -= static_cast<int>(static_cast<float>(distanceVal) * 0.2f); // decrease weight of clumping

			// check if in a line, increase its value (decrease clumping, increase amount of objects in a line)
			if (i == j - 1)
			{
				countInLine++;
				if ((j - 2) > 0)
					if ((proposedState.at(j - 2).player == winnerEval))
						countInLine += 10;
			}
			if (i == j - TILES_SIZE)
			{
				countInLine++;
				int pos = (j - (TILES_SIZE * 2));
				if (pos > 0)
					if (proposedState.at(pos).player == winnerEval)
						countInLine += 10;
			}
			if (i == j - TILES_SIZE - 1)
			{
				countInLine++;
				int pos = (j - (TILES_SIZE * 2) - 2);
				if (pos > 0)
					if (proposedState.at(pos).player == winnerEval)
						countInLine += 10;
			}
		}
		// prefer positions around center of board, 
		// this is as it is better to play near the center to begin with
		int distanceToCenter = distance(sf::Vector2f(proposedState.at(i).position.x, proposedState.at(i).position.y), sf::Vector2f(2.f, 2.f));
		value -= distanceToCenter; // prefer central positions
	}

	value = increaseValue(value, countInLine);

	return value;
}

int AiDecisionAbstract::calculateDepth(std::vector<std::vector<std::vector<Tile>>>& boardStates,
	std::vector<std::vector<MovementType>>& moves,
	std::function<Player(std::vector<Tile>&)> t_winFunction,
	std::vector<Tile>& tiles,
	std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction,
	int depth, int minMax)
{
	boardStates.emplace_back();
	moves.emplace_back();
	Player player;
	if (depth % 2 == 0) player = Player::One;
	else player = Player::Two;

	int valueExtent = 0;
	int furthestVal = (player == Player::One) ? 999999 : -999999; 
	bool firstPass = true; 

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i).tileItem == TileItem::none) continue;
		if (tiles.at(i).player == Player::none) continue;
		if (tiles.at(i).player != player) continue;

		for (int boardDepthX = 0; boardDepthX < boardStates.at(depth - 1).size(); boardDepthX++)
		{
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
				continue;
			}

			for (int t = 0; t < moveTiles.size(); t++)
			{
				if (checkable.at(t))
				{
					std::vector<Tile> tempBoard = boardStates.at(depth - 1).at(boardDepthX);
					MovementType move;
					move.currentPos = i;
					move.destination = moveTiles.at(t);
					moves.at(depth - 1).emplace_back(move);
					tempBoard.at(moveTiles.at(t)).tileItem = tempBoard.at(i).tileItem;
					tempBoard.at(moveTiles.at(t)).enemyOccupied = true;
					tempBoard.at(moveTiles.at(t)).initBody(player);
					boardStates.at(depth).emplace_back(tempBoard);

					// calculate highest heurustic for this depth
					int currentVal = calculateHeurusticValue(boardStates.at(depth).at(boardStates.at(depth).size() - 1), t_winFunction, player);
					moves.at(depth - 1).at(moves.at(depth - 1).size() - 1).value = currentVal;

					if (firstPass)
					{
						furthestVal = currentVal;
						firstPass = false;
					}

					// min
					if (player == Player::One) 
					{
						if (currentVal < furthestVal)
						{
							furthestVal = currentVal;
							if (minMax > currentVal) 
							{
								return currentVal;
							}
						}
					}
					// max
					else if (player == Player::Two) 
					{
						if (currentVal > furthestVal)
						{
							furthestVal = currentVal;
							if (minMax < currentVal) 
							{
								return currentVal;
							}
						}
					}
				}
			}

		}
	}

	return furthestVal;
}

int AiDecisionAbstract::increaseValue(int val, int lineAmt)
{
	return val + 50 * lineAmt;
}

MovementType AiDecisionAbstract::DecideMovement(std::vector<Tile>& tiles,
	std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction,
	std::function<Player(std::vector<Tile>&)> t_winFunction)
{
	int maxDepth = 4; 

	std::vector<std::vector<std::vector<Tile>>> boardStates;
	std::vector<std::vector<MovementType>> moves;
	boardStates.emplace_back();
	boardStates.at(0).emplace_back();
	boardStates.at(0).at(0) = tiles;

	// Initialize first depth moves
	moves.emplace_back();

	int minMax = 0;

	for (int depth = 1; depth < maxDepth; depth++)
	{
		minMax = calculateDepth(boardStates, moves, t_winFunction, tiles, t_movementFunction, depth, minMax);
	}

	MovementType bestMove;
	bestMove.value = -999999;

	if (!moves.empty() && !moves.at(0).empty())
	{
		for (const auto& move : moves.at(0))
		{
			if (move.value > bestMove.value)
			{
				bestMove = move;
			}
		}
	}

	return bestMove;
}
