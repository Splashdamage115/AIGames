#include "Game.h"
#include "GamePlay.h"
#include "Settings.h"
#include "GlobalFontStorage.h"
#include "Menu.h"

Menu::Menu()
{
	resetLevel();
}

Menu::~Menu()
{
}

/// <summary>
/// resets all values to default as needed
/// </summary>
void Menu::resetLevel()
{
	m_sfmlLogoS = std::make_shared<sf::Sprite>();
	m_hudText = std::make_shared<sf::Text>();

	if (!m_sfmlLogoT.loadFromFile("ASSETS\\IMAGES\\Misc\\SFML-LOGO.png"))
	{
		DEBUG_MSG("COULDNT FIND SFML LOGO");
	}
	else
	{
		m_sfmlLogoS->setTexture(m_sfmlLogoT);
		m_sfmlLogoS->setPosition(200.f, 200.f);

		RenderObject::getInstance().add(m_sfmlLogoS);
	}

	// sample text initialising in the hud
	m_globalFont = GlobalFontStorage::getInstance().getFont();

	m_hudText->setFont(*m_globalFont);
	m_hudText->setFillColor(sf::Color::White);
	m_hudText->setOutlineColor(sf::Color::Black);
	m_hudText->setOutlineThickness(0.5f);
	m_hudText->setString("Sample_Text");
	m_hudText->setOrigin(m_hudText->getGlobalBounds().width / 2.f , m_hudText->getGlobalBounds().height / 2.f);
	m_hudText->setPosition(SCREEN_WIDTH / 2.f, 200.f);

	RenderObject::getInstance().addHUD(m_hudText);
	// ! initialising

	if (!m_buttonTexture.loadFromFile("ASSETS\\IMAGES\\Buttons\\SlideButton.png")) //rotate_button.png
	{
		DEBUG_MSG("COULDNT FIND BUTTON");
	}
	else
	{
		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			m_buttons.push_back(Button());
			m_buttons.at(i).init(m_buttonTexture, sf::Vector2i(320, 96), sf::Vector2f(-1.f, 600.f + (100 * i)), 6, 0.5f);
			//m_buttons.at(i).init(m_buttonTexture, sf::Vector2i(256, 128), sf::Vector2f(100.f, 600.f + (150 * i)), 4, 0.5f);
		}

		m_buttons.at(0).changeFrameHeight(1);

		m_buttons.at(0).setFunction([]() -> void { Game::s_changeGameMode = true; Game::s_currentGameMode = GameModeClass::Gameplay; });
		m_buttons.at(1).setFunction([]() -> void { Game::s_changeGameMode = true; Game::s_currentGameMode = GameModeClass::Settings; });
		m_buttons.at(2).setFunction([]() -> void { Game::s_gameActive = false; });
	}
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void Menu::events(sf::Event& t_event)
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
void Menu::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void Menu::update()
{
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		m_buttons.at(i).updateFrame();
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void Menu::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);

		for (unsigned int i = 0; i < m_buttons.size(); i++)
			m_buttons.at(i).checkBounds(m_mousePos);
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

void Menu::mouseButtonDown()
{
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		;
}

void Menu::mouseButtonUp()
{
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		m_buttons.at(i).releaseButton();
}
