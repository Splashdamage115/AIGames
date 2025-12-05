#pragma once

#include "Library.h"

class SetAIPlayButton
{
public:
	/*! \brief initialise the items here
	*
	*  
	*/
	void Init();

	/*! \brief update all input in the button
	*
	*  when the button is clicked pass the info off to the game class
	*/
	void update();
private:
	std::shared_ptr<sf::RectangleShape> m_box;
	std::shared_ptr<sf::Text> m_text;
	std::shared_ptr<sf::RectangleShape> m_hitBox;

	bool mouseDown = false;

	std::shared_ptr<sf::RectangleShape> m_difficultyHitBox;
	std::shared_ptr<sf::Text> m_difficultyText;
	bool normalDifficulty = true;
};

