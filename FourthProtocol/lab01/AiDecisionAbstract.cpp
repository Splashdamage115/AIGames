#include "AiDecisionAbstract.h"
#include "Tile.h"
#include <algorithm> 

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

		// Check for immediate winning move first
		Player p = t_winFunction(tempBoard);
		if (p == Player::Two)
		{
			chosenSpot = i;
			std::cout << "Winning move found @ " << i << "\n";
			break;
		}

		// Check if opponent would win on next turn - block it
		tempBoard.at(i).player = Player::One;
		Player opponentWin = t_winFunction(tempBoard);
		if (opponentWin == Player::One)
		{
			tempBoard.at(i).player = Player::Two;
			currentHeurustic = 500000;
			std::cout << "blocking player win @ " << i << "\n";
		}
		// Check for 2-in-a-row threat from player - prioritize blocking
		else if (detectTwoInARowThreat(tiles, Player::One, i))
		{
			tempBoard.at(i).player = Player::Two;
			currentHeurustic = 100000;
			std::cout << "blocking 2-in-a-row threat @ " << i << "\n";
		}
		else
		{
			tempBoard.at(i).player = Player::Two;
			currentHeurustic = calculateHeurusticValue(tempBoard, t_winFunction, Player::Two);
		}

		//std::cout << "Board position : " << i << " cost is : " << currentHeurustic << "\n";

		if (currentHeurustic > highestHeurusticValue)
		{
			bestPosition = i;
			highestHeurusticValue = currentHeurustic;
		}
		tiles.at(i).tilePlaceValue->setString(std::to_string(currentHeurustic));
	}

	// Use chosenSpot if winning move was found, otherwise use bestPosition
	if (chosenSpot == 0)
	{
		chosenSpot = bestPosition;
	}

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
	// Check for immediate win/loss first
	Player gameResult = t_winFunction(proposedState);
	if (gameResult == winnerEval) return 999999999;
	if (gameResult != Player::none && gameResult != winnerEval) return -999999999;

	Player opponent = (winnerEval == Player::One) ? Player::Two : Player::One;
	int value = 1000;
	int aiPieces = 0;
	int opponentPieces = 0;
	int aiCountInLine = 0;
	int opponentCountInLine = 0;

	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (proposedState.at(i).player == winnerEval)
		{
			aiPieces++;
			// Prefer central positions for AI
			int distanceToCenter = static_cast<int>(distance(sf::Vector2f(proposedState.at(i).position.x, proposedState.at(i).position.y), sf::Vector2f(2.f, 2.f)));
			value -= distanceToCenter * 5;
		}
		else if (proposedState.at(i).player == opponent)
		{
			opponentPieces++;
		}
	}

	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (proposedState.at(i).player != winnerEval) continue;

		for (int j = 0; j < TILES_SIZE * TILES_SIZE; j++)
		{
			if (i == j || proposedState.at(j).player != winnerEval) continue;


			int distanceVal = static_cast<int>(distance(sf::Vector2f(proposedState.at(i).position.x, proposedState.at(i).position.y),
				sf::Vector2f(proposedState.at(j).position.x, proposedState.at(j).position.y)));
			value -= static_cast<int>(static_cast<float>(distanceVal) * 0.2f);


			if (i == j - 1 && (i % TILES_SIZE) != (TILES_SIZE - 1))
			{
				aiCountInLine++;

				if ((j + 1) < (TILES_SIZE * TILES_SIZE) && proposedState.at(j + 1).player == winnerEval) aiCountInLine += 15;
			}
			if (i == j - TILES_SIZE)
			{
				aiCountInLine++;

				if ((j + TILES_SIZE) < (TILES_SIZE * TILES_SIZE) && proposedState.at(j + TILES_SIZE).player == winnerEval) aiCountInLine += 15;
			}
			if (i == j - TILES_SIZE - 1 && (i % TILES_SIZE) != (TILES_SIZE - 1))
			{
				aiCountInLine++;

				if ((j + TILES_SIZE + 1) < (TILES_SIZE * TILES_SIZE) && proposedState.at(j + TILES_SIZE + 1).player == winnerEval) aiCountInLine += 15;
			}
		}
	}

	// Check opponent line count
	for (int i = 0; i < TILES_SIZE * TILES_SIZE; i++)
	{
		if (proposedState.at(i).player != opponent) continue;

		for (int j = 0; j < TILES_SIZE * TILES_SIZE; j++)
		{
			if (i == j || proposedState.at(j).player != opponent) continue;

			if (i == j - 1 && (i % TILES_SIZE) != (TILES_SIZE - 1))
			{
				opponentCountInLine++;

				if ((j + 1) < (TILES_SIZE * TILES_SIZE) && proposedState.at(j + 1).player == opponent) value -= 200;
			}
			if (i == j - TILES_SIZE)
			{
				opponentCountInLine++;
				if ((j + TILES_SIZE) < (TILES_SIZE * TILES_SIZE) && proposedState.at(j + TILES_SIZE).player == opponent) value -= 200;
			}
			if (i == j - TILES_SIZE - 1 && (i % TILES_SIZE) != (TILES_SIZE - 1))
			{
				opponentCountInLine++;
				if ((j + TILES_SIZE + 1) < (TILES_SIZE * TILES_SIZE) && proposedState.at(j + TILES_SIZE + 1).player == opponent) value -= 200;
			}
		}
	}

	value = increaseValue(value, aiCountInLine);
	value -= (opponentCountInLine * 30);
	value += (aiPieces - opponentPieces) * 20;

	return value;
}

int AiDecisionAbstract::calculateDepth(std::vector<std::vector<std::vector<Tile>>>& boardStates,
	std::vector<std::vector<MovementType>>& moves,
	std::function<Player(std::vector<Tile>&)> t_winFunction,
	std::vector<Tile>& tiles,
	std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction,
	int depth, int alpha, int beta)
{
	// Add depth limit to prevent infinite recursion
	if (depth >= 6) // Reduced depth limit
	{
		return 0;
	}

	boardStates.emplace_back();
	moves.emplace_back();
	Player currentPlayer = (depth % 2 == 0) ? Player::One : Player::Two;
	bool isMaximizing = (currentPlayer == Player::Two);

	int bestValue = isMaximizing ? -999999 : 999999;

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i).tileItem == TileItem::none) continue;
		if (tiles.at(i).player == Player::none) continue;
		if (tiles.at(i).player != currentPlayer) continue;

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

					// Move the piece and clear the original position
					tempBoard.at(moveTiles.at(t)).tileItem = tempBoard.at(i).tileItem;
					tempBoard.at(moveTiles.at(t)).enemyOccupied = (currentPlayer == Player::Two);
					tempBoard.at(moveTiles.at(t)).occupied = true;
					tempBoard.at(moveTiles.at(t)).player = currentPlayer;

					// Clear the original position properly
					tempBoard.at(i).tileItem = TileItem::none;
					tempBoard.at(i).enemyOccupied = false;
					tempBoard.at(i).occupied = false;
					tempBoard.at(i).player = Player::none;

					boardStates.at(depth).emplace_back(tempBoard);

					// Check for win / loss
					Player winner = t_winFunction(tempBoard);
					int currentVal;
					if (winner == Player::Two)
					{
						currentVal = 999999;
					}
					else if (winner == Player::One)
					{
						currentVal = -999999;
					}
					else
					{
						currentVal = calculateHeurusticValue(boardStates.at(depth).at(boardStates.at(depth).size() - 1), t_winFunction, currentPlayer);
					}

					moves.at(depth - 1).at(moves.at(depth - 1).size() - 1).value = currentVal;

					if (isMaximizing)
					{
						bestValue = std::max(bestValue, currentVal);
						alpha = std::max(alpha, bestValue);
						if (beta <= alpha)
						{
							return bestValue;
						}
					}
					else
					{
						bestValue = std::min(bestValue, currentVal);
						beta = std::min(beta, bestValue);
						if (beta <= alpha)
						{
							return bestValue;
						}
					}
				}
			}
		}
	}

	return bestValue;
}

int AiDecisionAbstract::increaseValue(int val, int lineAmt)
{
	return val + 50 * lineAmt;
}

MovementType AiDecisionAbstract::DecideMovement(std::vector<Tile>& tiles,
	std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction,
	std::function<Player(std::vector<Tile>&)> t_winFunction)
{
	int maxDepth = 5;

	std::vector<std::vector<std::vector<Tile>>> boardStates;
	std::vector<std::vector<MovementType>> moves;
	boardStates.emplace_back();
	boardStates.at(0).emplace_back();
	boardStates.at(0).at(0) = tiles;

	moves.emplace_back();

	MovementType bestMove;
	bestMove.value = -999999;

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i).tileItem == TileItem::none) continue;
		if (tiles.at(i).player != Player::Two) continue;

		std::vector<int> moveTiles;
		std::vector<bool> checkable;
		t_movementFunction(moveTiles, checkable, i);

		for (int t = 0; t < moveTiles.size(); t++)
		{
			if (checkable.at(t))
			{
				std::vector<Tile> tempBoard = tiles;
				tempBoard.at(moveTiles.at(t)).tileItem = tempBoard.at(i).tileItem;
				tempBoard.at(moveTiles.at(t)).enemyOccupied = true;
				tempBoard.at(moveTiles.at(t)).initBody(Player::Two);
				tempBoard.at(i).tileItem = TileItem::none;
				tempBoard.at(i).enemyOccupied = false;
				tempBoard.at(i).player = Player::none;

				// Check for immediate win
				Player winner = t_winFunction(tempBoard);
				if (winner == Player::Two)
				{
					MovementType winningMove;
					winningMove.currentPos = i;
					winningMove.destination = moveTiles.at(t);
					winningMove.value = 999999;
					std::cout << "AI winning from " << i << " to " << moveTiles.at(t) << "\n";
					return winningMove;
				}

				MovementType move;
				move.currentPos = i;
				move.destination = moveTiles.at(t);
				move.value = calculateHeurusticValue(tempBoard, t_winFunction, Player::Two);
				moves.at(0).emplace_back(move);

				if (move.value > bestMove.value)
				{
					bestMove = move;
				}
			}
		}
	}

	int alpha = -999999;
	int beta = 999999;

	for (int depth = 1; depth < maxDepth; depth++)
	{
		calculateDepth(boardStates, moves, t_winFunction, tiles, t_movementFunction, depth, alpha, beta);
	}

	if (!moves.empty() && !moves.at(0).empty())
	{
		bestMove.value = -999999;
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

bool AiDecisionAbstract::detectTwoInARowThreat(std::vector<Tile>& tiles, Player targetPlayer, int blockPosition)
{
	// Check if placing a piece at blockPosition would interrupt a 2-in-a-row threat from targetPlayer
	// We need to check all possible directions: horizontal, vertical, and both diagonals

	int x = blockPosition % TILES_SIZE;
	int y = blockPosition / TILES_SIZE;

	// Direction vectors: right, down, down-right diagonal, down-left diagonal
	int dx[] = { 1, 0, 1, 1 };
	int dy[] = { 0, 1, 1, -1 };

	for (int dir = 0; dir < 4; dir++)
	{
		// Check if this position would block a 2-in-a-row in this direction

		// Look backwards along this direction
		int backCount = 0;
		int checkX = x - dx[dir];
		int checkY = y - dy[dir];

		while (checkX >= 0 && checkX < TILES_SIZE && checkY >= 0 && checkY < TILES_SIZE)
		{
			int checkPos = checkY * TILES_SIZE + checkX;
			if (tiles.at(checkPos).occupied && tiles.at(checkPos).player == targetPlayer)
			{
				backCount++;
				checkX -= dx[dir];
				checkY -= dy[dir];
			}
			else
			{
				break;
			}
		}

		// Look forwards along this direction
		int forwardCount = 0;
		checkX = x + dx[dir];
		checkY = y + dy[dir];

		while (checkX >= 0 && checkX < TILES_SIZE && checkY >= 0 && checkY < TILES_SIZE)
		{
			int checkPos = checkY * TILES_SIZE + checkX;
			if (tiles.at(checkPos).occupied && tiles.at(checkPos).player == targetPlayer)
			{
				forwardCount++;
				checkX += dx[dir];
				checkY += dy[dir];
			}
			else
			{
				break;
			}
		}

		// If we have exactly 2 pieces in a line that would be blocked by placing here
		if (backCount + forwardCount == 2)
		{
			// Additional check: make sure there's space for the opponent to extend this line
			// Check if there's at least one free space on either end of the line

			bool hasExtensionSpace = false;

			// Check space beyond the back pieces
			checkX = x - dx[dir] * (backCount + 1);
			checkY = y - dy[dir] * (backCount + 1);
			if (checkX >= 0 && checkX < TILES_SIZE && checkY >= 0 && checkY < TILES_SIZE)
			{
				int extendPos = checkY * TILES_SIZE + checkX;
				if (!tiles.at(extendPos).occupied)
				{
					hasExtensionSpace = true;
				}
			}

			// Check space beyond the forward pieces
			checkX = x + dx[dir] * (forwardCount + 1);
			checkY = y + dy[dir] * (forwardCount + 1);
			if (checkX >= 0 && checkX < TILES_SIZE && checkY >= 0 && checkY < TILES_SIZE)
			{
				int extendPos = checkY * TILES_SIZE + checkX;
				if (!tiles.at(extendPos).occupied)
				{
					hasExtensionSpace = true;
				}
			}

			if (hasExtensionSpace)
			{
				return true;
			}
		}
	}

	return false;
}
