// *******************************************************************************************************
//
//													HOW TO USE
// 
// *******************************************************************************************************
//
// 
//     1. Include this file
// 
// 
//     2. create a shared pointer of type "SimpleButton"  (std::shared_ptr<SimpleButton> NAME;)
//			~This pointer has to stay alive (declare in class header file)
//	
// 
//     3. initialise a new button ~ in constructor (or other) call :
//				NAME = SimpleButtonHolder::getInstance().spawnNewButton("<Text you want displayed>");
// 
// 
//	   4. in update call if(NAME->clicked()) <thing you want to happen>;
//			- e.g.    if(spawnButton->clicked()) m_npcManager.spawnNewEnemy();
// 
// 
// *******************************************************************************************************
// 
//	Notes:
//			Can be held in a vector, just make sure that the vector is kept alive
// 
// *******************************************************************************************************



#pragma once

#include "Library.h"

#include "Game.h"
#include "RenderObject.h"

class SimpleButtonHolder;

class SimpleButton
{
	friend SimpleButtonHolder;
public:
	SimpleButton() {}
	// check if the button was clicked
	bool clicked()
	{
		if (m_wasJustClicked)
		{
			m_wasJustClicked = false;
			return true;
		}
		return false;
	}

private:
	// call this update from main to update all buttons
	void update(sf::Vector2f const& t_mousePos)
	{
		// getting mouse button released without events
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_mouseDown = true;
		}
		else
		{
			// if the mouse was pressed last frame, and its not now
			// then it was released
			if (m_mouseDown)
			{
				m_released = true;
				m_mouseDown = false;
			}

		}

		if (m_bg->getGlobalBounds().contains(t_mousePos))
		{
			if (m_mouseDown)
			{
				m_bg->setFillColor(sf::Color(255, 255, 255, 80));
			}
			else
			{
				m_bg->setFillColor(sf::Color(255, 255, 255, 40));
			}
			if (m_released) // if mouse was released, pass back just clicked to the clicked call
				m_wasJustClicked = true;
		}
		else
		{
			m_bg->setFillColor(sf::Color(0, 0, 0, 80));
		}
		m_released = false; // unset released, so that it isnt called in next frames
	}

	// initialise the text and background box
	void init(std::string& t_displayString, sf::Vector2f t_spawnPos)
	{
		m_dispText = std::make_shared<sf::Text>(Game::m_jerseyFont);
		m_bg = std::make_shared<sf::RectangleShape>();

		// initialise the text and place the origin in the center
		m_dispText->setString(t_displayString);
		m_dispText->setCharacterSize(20u);
		m_dispText->setOutlineColor(sf::Color::Black);
		m_dispText->setOutlineThickness(1u);
		m_dispText->setOrigin({ m_dispText->getGlobalBounds().size.x / 2.f, m_dispText->getGlobalBounds().size.y / 2.f });

		// initialise the background of the box to be slightly bigger than the text
		m_bg->setFillColor(sf::Color(0, 0, 0, 80));
		m_bg->setOutlineColor(sf::Color(255, 255, 255, 80)); // white at  80/255
		m_bg->setOutlineThickness(1u);
		m_bg->setPosition(t_spawnPos);
		float padding = 30.f;
		m_bg->setSize(sf::Vector2f(m_dispText->getGlobalBounds().size.x + padding, padding));

		// place text in the center of the button
		m_dispText->setPosition(sf::Vector2f(m_bg->getGlobalBounds().size.x / 2.f, m_bg->getGlobalBounds().size.y / 2.f) + t_spawnPos);

		RenderObject::getInstance().addNewRenderObject(m_bg, 8);
		RenderObject::getInstance().addNewRenderObject(m_dispText, 8);
	}

	std::shared_ptr<sf::RectangleShape> m_bg;
	std::shared_ptr<sf::Text> m_dispText;

	bool m_wasJustClicked{ false };
	bool m_mouseDown{ false };
	bool m_released{ false };
};

class SimpleButtonHolder
{
public:
	// make this singletone, we dont need more button holders
	static SimpleButtonHolder& getInstance()
	{
		static SimpleButtonHolder instance;
		return instance;
	}
	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	SimpleButtonHolder(SimpleButtonHolder const&) = delete;
	void operator=(SimpleButtonHolder const&) = delete;


	// initialise the button and pass back a pointer to the button
	// this will be used to call the clicked function
	std::shared_ptr<SimpleButton> spawnNewButton(std::string t_displayText)
	{
		std::shared_ptr<SimpleButton> temporaryButton;
		temporaryButton = std::make_shared<SimpleButton>();

		// early return as a new button wasnt pushed into the array, instead an old one was reused
		for (unsigned int i = 0; i < m_buttons.size(); i++)
		{
			if (m_buttons.at(i).lock() == nullptr)
			{
				temporaryButton->init(t_displayText, sf::Vector2f(1.f, i * 32.f + 1.f));
				m_buttons.at(i) = temporaryButton;
				return temporaryButton;
			}
		}
		temporaryButton->init(t_displayText, sf::Vector2f(1.f, m_buttons.size() * 32.f + 1.f));
		m_buttons.push_back(temporaryButton);

		return temporaryButton;
	}

	// set the mouse position for button use
	void setMouse(sf::Vector2f const& t_mousePos) { m_mousePos = t_mousePos; }

	// call update on the buttons
	void update()
	{
		// (checking if pointer is active)
		for (unsigned int i = 0; i < m_buttons.size(); i++)
		{
			std::shared_ptr<SimpleButton>tempButton = m_buttons.at(i).lock();
			if (tempButton != nullptr)
			{
				tempButton->update(m_mousePos);
			}
		}
	}
private:
	SimpleButtonHolder() {}
	std::vector< std::weak_ptr<SimpleButton> > m_buttons; // vector of all simple buttons
	sf::Vector2f m_mousePos;
};
