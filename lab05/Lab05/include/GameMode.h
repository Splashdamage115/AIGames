// THIS IS THE ABSTRACT CLASS FOR A STANDARD GAMEMODE
#ifndef GAMEMODE_H
#define GAMEMODE_H

#include<SFML/Graphics.hpp>
#include"Globals.h"
#include"RenderObject.h"

#include"DEBUG.h" // this is used for DEBUG_MSG

class GameMode
{
public:
	GameMode();  // standard constructor
	~GameMode(); // standard deconstructor (shouldnt be used)

	virtual void resetLevel() = 0;                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event) = 0;           // used to handle all new events outside key presses
	virtual void update() = 0;         // all update events

private:
	virtual void processKeys(sf::Event& t_event) = 0;      // handles all key inputs
	virtual void processMouse(sf::Event& t_event) = 0;     // handles all mouse events

protected:
	sf::Vector2f m_mousePos{ 0.0f,0.0f }; // the mouses position

	// this just sets the mouse position based off the movement
	inline void findMousePos(sf::Event& t_event) { 
		m_mousePos = RenderObject::getInstance().getWindow().mapPixelToCoords(sf::Vector2i(
			static_cast<int>(t_event.mouseMove.x),
			static_cast<int>(t_event.mouseMove.y)));
	}

};

#endif // !GAMEMODE_H