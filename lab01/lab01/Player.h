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
	std::shared_ptr<sf::Sprite> m_sprite;
	sf::Texture m_texture;

	sf::Vector2f m_moveDirection;

	float m_speed = 100.0f;
};

