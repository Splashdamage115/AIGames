#include "FormationMoveState.h"
#include "Game.h"
#include "math.h"

FormationMoveState::FormationMoveState(std::shared_ptr<sf::Vector2f> t_position) : abstractMoveState(t_position)
{
}

void FormationMoveState::init()
{
    m_angle = rand() % 360;
}

sf::Vector2f FormationMoveState::moveVector(sf::Vector2f t_centerPos, float t_faceAngle, float t_)
{


    sf::Vector2f desiredDisplacement = math::displacement(*m_position, t_centerPos);
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

    arrive(t_centerPos);

    return math::degreesToDisplacement(m_angle) * Game::deltaTime * m_speed;
}

void FormationMoveState::arrive(sf::Vector2f t_playerPos)
{
    float dist = math::distancebetweenPoints(*m_position, t_playerPos);

    if (dist <= closeDistance)
    {
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
        decreaseSpeed();

    }
    else if (dist <= arriveDistance)
    {
        increaseSpeed();
        decreaseSpeed();
        decreaseSpeed();
    }
    else
    {
        increaseSpeed();
    }
}