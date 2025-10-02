#include "SwarmMoveState.h"
#include "math.h"
#include "Game.h"

SwarmMoveState::SwarmMoveState(std::shared_ptr<sf::Vector2f> t_position) : abstractMoveState(t_position)
{
}

void SwarmMoveState::init()
{
}

sf::Vector2f SwarmMoveState::moveVector(sf::Vector2f t_other, float t_, float t_2)
{
	float r = math::distancebetweenPoints(*m_position, t_other);
	float rn = std::pow(r, N);
	float rm = std::pow(r, M);
	float steering = -A / rn + B / rm;

    float change = steering - m_angle;
    float angleChange = (static_cast<int>(std::round(change + 360))) % 360;

    if (angleChange < 180)
    {
        changeAngle(+1);
    }
    else
    {
        changeAngle(-1);
    }

    return math::degreesToDisplacement(m_angle) * Game::deltaTime * m_speed;
}
