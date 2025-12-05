#include "SetAIPlayButton.h"
#include "RenderObject.h"
#include "Game.h"
#include "Update.h"

void SetAIPlayButton::Init()
{
	m_box = std::make_shared<sf::RectangleShape>(sf::Vector2f(60.0f,60.0f));
	m_box->setFillColor(sf::Color::Transparent);
	m_box->setOutlineColor(sf::Color::White);
	m_box->setOutlineThickness(1u);
	m_box->setPosition(sf::Vector2f(30.0f, 1000.0f));
	RenderObject::getInstance().addNewRenderObject(m_box, 3);


	m_text = std::make_shared<sf::Text>(Game::m_jerseyFont);
	m_text->setFillColor(sf::Color::White);
	m_text->setCharacterSize(30u);
	m_text->setString("Clean it up for me AI");
	m_text->setPosition(sf::Vector2f(110.f, 1015.0f));
	RenderObject::getInstance().addNewRenderObject(m_text, 3);


	m_hitBox = std::make_shared<sf::RectangleShape>(sf::Vector2f(370.0f, 100.0f));
	m_hitBox->setFillColor(sf::Color::Transparent);
	m_hitBox->setOutlineColor(sf::Color::White);
	m_hitBox->setOutlineThickness(1u);
	m_hitBox->setPosition(sf::Vector2f(10.0f, 980.0f));
	//RenderObject::getInstance().addNewRenderObject(m_hitBox, 3);

	m_difficultyHitBox = std::make_shared<sf::RectangleShape>(sf::Vector2f(370.0f, 100.0f));
	m_difficultyHitBox->setFillColor(sf::Color::Transparent);
	m_difficultyHitBox->setOutlineColor(sf::Color::White);
	m_difficultyHitBox->setOutlineThickness(1u);
	m_difficultyHitBox->setPosition(sf::Vector2f(10.0f, 880.0f));
	RenderObject::getInstance().addNewRenderObject(m_difficultyHitBox, 3);

	m_difficultyText = std::make_shared<sf::Text>(Game::m_jerseyFont);
	m_difficultyText->setFillColor(sf::Color::Blue);
	m_difficultyText->setCharacterSize(20u);
	m_difficultyText->setString("Difficulty : Normal\n<Click to Change>");
	m_difficultyText->setPosition(sf::Vector2f(110.f, 915.0f));
	RenderObject::getInstance().addNewRenderObject(m_difficultyText, 3);

	Update::append([this]() { this->update(); });
}

void SetAIPlayButton::update()
{
	if (m_hitBox->getGlobalBounds().contains(sf::Vector2f(Game::mousePosition.x, Game::mousePosition.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			mouseDown = true;
		}
		else if (mouseDown)
		{
			mouseDown = false;
			Game::aiEnabled = !Game::aiEnabled;
			m_box->setFillColor((Game::aiEnabled) ? sf::Color::White : sf::Color::Transparent);
		}
	}
	if (m_difficultyHitBox->getGlobalBounds().contains(sf::Vector2f(Game::mousePosition.x, Game::mousePosition.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			mouseDown = true;
		}
		else if (mouseDown)
		{
			mouseDown = false;
			if (normalDifficulty)
			{
				AiDecisionAbstract::SEARCH_DEPTH = 4;
				m_difficultyText->setString("Difficulty : Hard\n<Click to Change>");
				m_difficultyText->setFillColor(sf::Color::Red);
				normalDifficulty = false;
			}
			else
			{
				AiDecisionAbstract::SEARCH_DEPTH = 2;
				m_difficultyText->setString("Difficulty : Normal\n<Click to Change>");
				m_difficultyText->setFillColor(sf::Color::Blue);
				normalDifficulty = true;

			}
		}
	}
}
