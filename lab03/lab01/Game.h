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
#include "Player.h"
#include "NPC.h"


const sf::Color ULTRAMARINE{ 5, 55,242,255 }; // const colour

class Game
{
public:
	Game();
	~Game();
	void run();

	static float deltaTime;
	static sf::Font m_jerseyFont;
private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(float t_deltaTime);
	void calculateClosest();

	//void changeNPC(int t_num);

	Player m_player;
	std::vector<NPC> m_npcs;
	std::vector<bool> m_npcActive;
	std::vector<int> m_closestNpc;

	//std::shared_ptr<sf::Text> m_instructions;
};

#pragma warning( pop ) 
#endif // !GAME_HPP

