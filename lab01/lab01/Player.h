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

	void playerInput();
	void increaseSpeed();
	void decreaseSpeed();
	void changeAngle(int t_direction);

	std::shared_ptr<sf::CircleShape>m_body;
	std::shared_ptr<sf::Sprite> m_sprite;
	sf::Texture m_texture;

	float m_angle = 0.0f;
	float m_angleChange = 100.0f;

	float m_speed = 0.0f;
	float m_maxSpeed = 500.0f;
	float m_speedIncreaseFactor = 100.0f;
};

