#pragma once
#include "Library.h"
#include "abstractMoveState.h"
class NPC
{
public:
	enum class MoveState
	{
		none, seek, wander
	};

	NPC();
	void start(MoveState t_moveType);

	void update(sf::Vector2f t_playerPos);
private:
	void outOfBounds();

	void increaseSpeed();
	void decreaseSpeed();
	void changeAngle(int t_direction);

	std::shared_ptr<sf::CircleShape>m_body;
	std::shared_ptr<sf::Sprite> m_sprite;
	std::shared_ptr<sf::Vector2f> m_position;
	sf::Texture m_texture;
	std::shared_ptr<abstractMoveState> m_moveState;
};

