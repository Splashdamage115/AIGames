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
	/*! \brief Reinitialise all items in the game
	*
	*  go through all classes and reinitialise them
	*/
	void restartGame();

	/*! \brief track the current game state
	*
	*  change the state of the game from place, to move
	*/
	enum class GameState
	{
		place, move
	};

	/*! \brief singleton pattern
	*
	*  using singleton for the game class as many items need access to some of the functions
	*/
	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	// DELETE FUNCTIONS TO AVOID MORE INSTANCES FOR SINGLETON
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	/*! \brief standard game loop
	*
	*  update and render cycle
	*/
	void run();

	/*! \brief call after an item is placed
	*
	*  reset the placing item
	*/
	void PlacedTile();

	/*! \brief go to place state for the game
	*
	* change game state after all items are placed
	*/
	void changeGameState(GameState t_gameState);

	static float deltaTime; // time per second
	static sf::Font m_jerseyFont; // standard used font
	//static sf::Texture m_ship; 
	static sf::Vector2i mousePosition; // track the position of the mouse

	static bool playerOneTurn; // whos turn is it
	static TileItem selectedItem; // the current item selected by the player

	static bool aiEnabled; // wether the ai is enabled or not

	/*! \brief check if the game has ended
	*
	*  change the text, and ready to restart
	*/
	void GameOver(); 

	Player winner; // which player has won

	int playerWins = 0; // amount of wins from the player
	int enemyWins = 0; // amount of wins from the enemy

	// AI timing control
	static float aiMoveDelay;
	static float aiMoveTimer;
	static bool aiWaitingToMove;

private:
	Game();

	/*! \brief process all input events
	*
	*  
	*/
	void processEvents();

	/*! \brief Process key presses
	*
	*  
	*/
	void processKeys(const std::optional<sf::Event> t_event);

	/*! \brief check if escape it pressed to close the game
	*
	*  
	*/
	void checkKeyboardState();

	/*! \brief update game items
	*
	*  
	*/
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
