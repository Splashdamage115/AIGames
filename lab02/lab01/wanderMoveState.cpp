#include "wanderMoveState.h"
#include "Game.h"
#include "math.h"

wanderMoveState::wanderMoveState(std::shared_ptr<sf::Vector2f> t_position) : abstractMoveState(t_position)
{
}

void wanderMoveState::init()
{
    m_angle = rand() % 360;

    setNewWaitTime();
}

sf::Vector2f wanderMoveState::moveVector(sf::Vector2f t_playerPos, float t_playerAngle, float t_speed)
{
    if (m_randomisePoint)
    {
        if (checkTimeUp())
        {
            chooseNewPoint();
        }
        else
        {
            m_randomisePoint = false;
        }

    }
    else if (checkFacingPoint())
    {
        m_randomisePoint = true;
    }
    else
    {
        float change = m_targetAngle - m_angle;
        float angleChange = (static_cast<int>(std::round(change + 360))) % 360;

        if (angleChange < 180)
        {
            changeAngle(+1);
        }
        else
        {
            changeAngle(-1);
        }
    }

    return math::degreesToDisplacement(m_angle) * Game::deltaTime * m_speed;
}

void wanderMoveState::setNewWaitTime()
{
    m_currentWaitTimeLeft = static_cast<float>(rand() % m_maxWaitTime);
}

bool wanderMoveState::checkTimeUp()
{
    m_currentWaitTimeLeft -= Game::deltaTime;

    if (m_currentWaitTimeLeft <= 0.0f)
    {
        setNewWaitTime();
        return true;
    }
    return false;
}

bool wanderMoveState::checkFacingPoint()
{
    if (math::nearlyEquals(m_angle, m_targetAngle))
    {
        return true;
    }
    return false;
}

void wanderMoveState::chooseNewPoint()
{
    m_targetAngle = (rand() % 180) + m_angle + (m_targetAngleIncrease *(rand() % 2 == 0 ? -1 : 1));
    m_targetAngleIncrease += m_rotateIncrease;
}
