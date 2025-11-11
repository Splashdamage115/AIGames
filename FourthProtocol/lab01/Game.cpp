#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Update.h"
#include "RenderObject.h"

float Game::deltaTime = 0.f;
sf::Font Game::m_jerseyFont;
sf::Texture Game::m_ship;
sf::Vector2i Game::mousePosition = { 0,0 };
bool Game::playerOneTurn = false;
TileItem Game::selectedItem = TileItem::none;

void Game::GameOver()
{
	gameOverState = true;
	(winner == Player::One) ? playerWins+=1 : enemyWins+=1;
	std::string winnerString = "\n\nGAME OVER\n\nPRESS SPACE\nTO RESTART\n\n\n";
	winnerString += (winner == Player::One) ? "Player 1 wins" : "Player 2 wins";
	m_instructions->setString(winnerString);
}

Game::Game()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	restartGame();

	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf")) std::cout << "problem loading arial black font" << std::endl;
	if (!m_ship.loadFromFile(".\\ASSETS\\IMAGES\\ship.png")) std::cout << "couldnt find ship\n";


	m_instructions = std::make_shared<sf::Text>(m_jerseyFont);
	m_instructions->setCharacterSize(42u);
	m_instructions->setFillColor(sf::Color(255, 255, 255, 215));
	m_instructions->setOutlineColor(sf::Color(0, 0, 0, 255));
	m_instructions->setOutlineThickness(1u);
	m_instructions->setPosition(sf::Vector2f(30.f, 30.f));
	m_instructions->setString("\n\nPlace the Characters\nThen click your \ncharacters to move\nthem around\n\n\n\nEach character has\nunique moves\nclick on a character\nand it will highlight\ntheir moves\n\n\n\n\nTry to beat the AI!");
	RenderObject::getInstance().addNewRenderObject(m_instructions, 7);
}

void Game::restartGame()
{
	m_tileManager = TileManager();
	m_charSelect = CharacterSelection();

	currentGamestate = GameState::place;
	playerOneTurn = false;
	selectedItem = TileItem::none;
	gameOverState = false;

	RenderObject::getInstance().start();

	m_tileManager.Start();
	m_charSelect.Start();
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (RenderObject::getInstance().getWindow().isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame.asSeconds()); //60 fps
		}
		RenderObject::getInstance().render();
	}
}

void Game::PlacedTile()
{
	selectedItem = TileItem::none;
	//playerOneTurn = !playerOneTurn;

	m_charSelect.ChangedItem();
}

void Game::changeGameState(GameState t_gameState)
{
	currentGamestate = t_gameState;

	switch (t_gameState)
	{
	case Game::GameState::place:

		break;
	case Game::GameState::move:
		m_tileManager.moveGameState();
		break;
	default:
		break;
	}
}

void Game::processEvents()
{
	while (const std::optional newEvent = RenderObject::getInstance().getWindow().pollEvent())
	{
		if (newEvent->is<sf::Event::Closed>())
		{
			RenderObject::getInstance().closeWindow();
		}
		if (newEvent->is<sf::Event::KeyReleased>() || newEvent->is<sf::Event::KeyPressed>()) //user pressed or released a key
		{
			processKeys(newEvent);
		}
		if (newEvent->is<sf::Event::MouseButtonReleased>()) //user released a mouse button
		{

		}
		if (newEvent->is<sf::Event::MouseMoved>())
		{
			mousePosition = sf::Mouse::getPosition(RenderObject::getInstance().getWindow());
		}
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	if (const auto* keyPressed = t_event->getIf<sf::Event::KeyReleased>())
	{
		if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
		{
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num1)
		{
			
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num2)
		{
			
		}
	}
}

void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		RenderObject::getInstance().closeWindow();
	}
}

void Game::update(float t_deltaTime)
{
	Game::deltaTime = t_deltaTime;
	checkKeyboardState();

	if (gameOverState)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
		{
			restartGame();
			RenderObject::getInstance().addNewRenderObject(m_instructions, 7);
			std::string winnerAmt = "Player Wins : " + std::to_string(playerWins / 2);
			winnerAmt += "\nEnemy Wins : " + std::to_string(enemyWins / 2);

			m_instructions->setString(winnerAmt);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
	{

	}

	Update::update();
}
