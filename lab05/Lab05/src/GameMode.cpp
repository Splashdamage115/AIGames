#include "GameMode.h"

/// <summary>
/// default constructor
/// </summary>
GameMode::GameMode()
{
	// NOTE: reset the level in the constructor
}

/// <summary>
/// default deconstructor
/// </summary>
GameMode::~GameMode()
{
}

/*

/// <summary>
/// resets all values to default as needed
/// </summary>
void GameMode::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GameMode::events(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type || sf::Event::KeyReleased == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}
	else
	{
		processMouse(t_event);
	}
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void GameMode::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GameMode::update()
{
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GameMode::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		mouseButtonUp();
	}
}
*/
