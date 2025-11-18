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
};

static float distance(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
{
	return std::sqrt((t_pos1.x - t_pos2.x) * (t_pos1.x - t_pos2.x) + (t_pos1.y - t_pos2.y) * (t_pos1.y - t_pos2.y));
}

class AiDecisionAbstract
{
public:
	void init();
	PlacementType DecidePlacement(std::vector<Tile>& tiles,
		std::function<Player(std::vector<Tile>&)> t_winFunction);

	MovementType DecideMovement(std::vector<Tile>& tiles, 
		std::function<void(std::vector<int>&, std::vector<bool>&, int)> t_movementFunction,
		std::function<Player (std::vector<Tile>& )> t_winFunction);
private:
	int calculateHeurusticValue(std::vector<Tile>& proposedState, std::function<Player(std::vector<Tile>&)> t_winFunction);

	std::vector<bool> m_availableItems;
	int AmtPlaceable = 5;
};

