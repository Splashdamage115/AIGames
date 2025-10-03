#include "SwarmMoveState.h"
#include "math.h"
#include "Game.h"

SwarmMoveState::SwarmMoveState(std::shared_ptr<sf::Vector2f> t_position) : abstractMoveState(t_position)
{
}

void SwarmMoveState::init()
{
    m_angle = rand() % 360;
}

sf::Vector2f SwarmMoveState::moveVector(sf::Vector2f t_other, float t_, float t_2)
{
	float r = math::distancebetweenPoints(*m_position, t_other);
	float rn = std::pow(r, N);
	float rm = std::pow(r, M);
	float steering = -A / rn + B / rm;

    float degrees = math::radiansToDegrees(steering);

    float change = steering - m_angle;
    float angleChange = (static_cast<int>(std::round(change + 360))) % 360;

    //std::cout << angleChange << std::endl;

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

sf::Vector2f SwarmMoveState::moveWithLocal(std::vector<sf::Vector2f> t_others)
{
    sf::Vector2f sumForce = sf::Vector2f();
    for (int i = 0; i < t_others.size(); i++)
    {
        sumForce += calcLJ(*m_position, t_others.at(i));
    }

    return math::normalize(sumForce) * m_speed * Game::deltaTime;
}

sf::Vector2f SwarmMoveState::calcLJ(sf::Vector2f me, sf::Vector2f other)
{
    sf::Vector2f R = me - other;
    float D = R.length();

    float rn = std::pow(D, N);
    float rm = std::pow(D, M);
    float U = -A / rn + B / rm;

    return R * U;
}
