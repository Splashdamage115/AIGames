/// <summary>
/// author Pete Lowe May 2025
/// you need to change the above line or lose marks
/// Also don't have any member properties called Delete...
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include "Library.h"
#include <SFML/Audio.hpp>
#include "Tile.h"
#include "CharacterSelection.h"
#include "SetAIPlayButton.h"

class Game
{
public:
	void restartGame();

	enum class GameState
	{
		place, move
	};

	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	void run();
	void PlacedTile();
	void changeGameState(GameState t_gameState);

	static float deltaTime;
	static sf::Font m_jerseyFont;
	static sf::Texture m_ship;
	static sf::Vector2i mousePosition;

	static bool playerOneTurn;
	static TileItem selectedItem;

static bool aiEnabled;

void GameOver();

Player winner;

int playerWins = 0;
int enemyWins = 0;

// AI timing control
static float aiMoveDelay;
static float aiMoveTimer;
static bool aiWaitingToMove;

private:
Game();

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(float t_deltaTime);

	std::shared_ptr<sf::Text> m_instructions;
	TileManager m_tileManager;
	CharacterSelection m_charSelect;

	GameState currentGamestate;

	bool gameOverState = false;

	SetAIPlayButton aiPlayButton;
};

#pragma warning( pop ) 
#endif // !GAME_HPP
