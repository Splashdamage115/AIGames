#pragma once

#include "Library.h"
#include <functional>

class Tile;
enum class TileItem;
enum class Player;

struct PlacementType
{
	int placementPosition = 0;
	TileItem placementType;
	bool allPlaced = false;
};

struct MovementType
{
	int currentPos = 0;
	int destination = 0;
	int value = -100;
};

static float distance(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
{
	return std::sqrt((t_pos1.x - t_pos2.x) * (t_pos1.x - t_pos2.x) + (t_pos1.y - t_pos2.y) * (t_pos1.y - t_pos2.y));
}

class AiDecisionAbstract
{
public:
	/*! \brief Initialise basic data for the ai
	*
	*  Set the player and initilise the available items array
	*/
	void init(Player t_player);

	/*! \brief AI decides where to place tokens
	*
	*  Take the current board state and win function (for checking if a play is a win)
	*  and loop through every potential play, and check if there is a winner, or if a block is necessary
	*  or if the ai has to block, if it has to block it will check if a three in a row is present (block an enemy win)
	*  or if a 2 in a row is present block that (future win if not near edge of board)
	*  otherwise it checks its heurustic and plays the best move
	*/
	PlacementType DecidePlacement(std::vector<Tile>& tiles,
		std::function<Player(std::vector<Tile>&)> t_winFunction);

	/*! \brief AI decides where to move tokens
	*
	*  Uses mini max to move the tokens to the best position
	*  calculates minimax, finds best move of mini max
	*  finds corresponding move and plays it
	*/
	MovementType DecideMovement(std::vector<Tile>& tiles,
		std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction,
		std::function<Player(std::vector<Tile>&)> t_winFunction);

	/*! \brief This is no longer used
	*
	*  used to calculate the alpha beta without recursive calls
	*/
	int calculateDepth(std::vector<std::vector<std::vector<Tile>>>& boardStates,
		std::vector<std::vector<MovementType>>& moves,
		std::function<Player(std::vector<Tile>&)> t_winFunction,
		std::vector<Tile>& tiles,
		std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction,
		int depth, int alpha, int beta);

	/*! \brief Alpha beta pruning between minimax
	*
	*  standard implementation of minimax,
	*  prune irrelevant branches
	*  return the best move
	*/
	int MinimaxAB(std::vector<Tile>& boardState, int depth, int alpha, int beta, bool isMaximizingPlayer,
		std::function<Player(std::vector<Tile>&)> t_winFunction,
		std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction);

	static int SEARCH_DEPTH;
private:
	/*! \brief Calculate the value of the current board state
	*
	*  check linearity between your pieces vs enemy pieces
	*  check how many pieces are in a line
	*  check if youve won
	*  check if enemy won
	*  check ditance to other pieces of yours (keep you pieces together)
	*  check distance to center (prefer central positions)
	*/
	int calculateHeurusticValue(std::vector<Tile>& proposedState, std::function<Player(std::vector<Tile>&)> t_winFunction, Player winnerEval);

	/*! \brief increase the value amt
	*
	*  change value based on amt in line
	*/
	int increaseValue(int val, int lineAmt);

	/*! \brief calculate if 2 items are in a row
	*
	*  check if 2 of the enemies items are in a row and return if they are
	*/
	bool detectTwoInARowThreat(std::vector<Tile>& tiles, Player targetPlayer, int blockPosition);

	std::vector<bool> m_availableItems;
	int AmtPlaceable = 5;

	Player m_player;
	Player m_enemy;
};
