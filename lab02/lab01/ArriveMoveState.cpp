#include "ArriveMoveState.h"
#include "Game.h"
#include "math.h"

ArriveMoveState::ArriveMoveState(std::shared_ptr<sf::Vector2f> t_position) : abstractMoveState(t_position)
{
}

void ArriveMoveState::init()
{
    m_angle = rand() % 360;
}

sf::Vector2f ArriveMoveState::moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed)
{
    sf::Vector2f desiredDisplacement = math::displacement(*m_position, t_playerPos);
    float desiredAngle = math::displacementToDegrees(desiredDisplacement);

    float change = desiredAngle - m_angle;
    float angleChange = (static_cast<int>(std::round(change + 360))) % 360;

    if (angleChange < 180)
    {
        changeAngle(+1);
    }
    else
    {
        changeAngle(-1);
    }

    arrive(t_playerPos);

    return math::degreesToDisplacement(m_angle) * Game::deltaTime * m_speed;
}

void ArriveMoveState::arrive(sf::Vector2f t_playerPos)
{
    float dist = math::distancebetweenPoints(*m_position, t_playerPos);

    if (dist <= closeDistance)
    {
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
    }
    else if (dist <= arriveDistance)
    {
        increaseSpeed();
        decreaseSpeed();
    }
    else
    {
        increaseSpeed();
    }
}
