#include "PursueMoveState.h"
#include "Game.h"
#include "math.h"

PursueMoveState::PursueMoveState(std::shared_ptr<sf::Vector2f> t_position) : abstractMoveState(t_position)
{
}

void PursueMoveState::init()
{
    m_angle = rand() % 360;
}

sf::Vector2f PursueMoveState::moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed)
{
    sf::Vector2f predictedPosition = t_playerPos + (math::degreesToDisplacement(t_playerAngle) * lookAheadTime * t_speed);
    float dist = math::distancebetweenPoints(*m_position, predictedPosition);
    sf::Vector2f desiredDisplacement;

    if (dist <= arriveDistance) {
        desiredDisplacement = math::displacement(*m_position, predictedPosition);
    }
    else
    {
        desiredDisplacement = math::displacement(*m_position, t_playerPos);
    }
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

    return math::degreesToDisplacement(m_angle) * Game::deltaTime * m_speed;
}
