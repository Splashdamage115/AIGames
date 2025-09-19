#include "wanderMoveState.h"
#include "Game.h"
#include "math.h"

wanderMoveState::wanderMoveState(std::shared_ptr<sf::Vector2f> t_position) : abstractMoveState(t_position)
{
}

void wanderMoveState::init()
{
    m_angle = rand() % 360;
}

sf::Vector2f wanderMoveState::moveVector(sf::Vector2f t_playerPos)
{
    return math::degreesToDisplacement(m_angle) * Game::deltaTime * m_speed;
}
