/// <summary>
/// author David Strikaitis 08/05/2023
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// </summary>
#include "Library.h"
#include"RenderObject.h"

// Abstract class
#include"GameMode.h"
#include"GamePlay.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	// static variable set ups
	static GameModeClass s_currentGameMode;
	static bool s_changeGameMode; // NOTE: set this to true if you want to change the game mode
	
	static bool s_gameActive;
	static float deltaTime; // global delta time

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void changeGameMode();

	void DebugUpdates();

	std::shared_ptr<GameMode> m_gameMode;      // used as abstract class for the gamemode
	RenderObject* m_renderer;
	sf::Vector2f m_mousePos;
};

#endif // !GAME_HPP

