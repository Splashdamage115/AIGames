#pragma once
#include "Library.h"
#include "abstractMoveState.h"
class NPC
{
public:
	enum class MoveState
	{
		none, seek, wander, arrive, pursue
	};

	NPC();
	void start(MoveState t_moveType, sf::Vector2f t_position);

	void update(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed);

	void changeMaxMoveSpeed(float t_newMaxMove);
	void changeMoveSpeed(float t_newMaxMove);
private:
	void outOfBounds();

	std::shared_ptr<sf::VertexArray> m_line;

	std::shared_ptr<sf::VertexArray> m_cone;
	std::shared_ptr<sf::CircleShape>m_body;
	std::shared_ptr<sf::Sprite> m_sprite;
	std::shared_ptr<sf::Vector2f> m_position;
	sf::Texture m_texture;
	std::shared_ptr<abstractMoveState> m_moveState;
	std::shared_ptr<sf::Text> m_stateType;
};

