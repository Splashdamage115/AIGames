#pragma once
#include <SFML\Graphics.hpp>
class Player
{
public:
	Player();
	void start();

	void update();
private:
	void outOfBounds();
	std::shared_ptr<sf::CircleShape>m_body;

	sf::Vector2f m_moveDirection;
};

