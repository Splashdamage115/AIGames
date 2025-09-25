#ifndef SIMPLE_MATHS_H
#define SIMPLE_MATHS_H

#include <SFML/Graphics.hpp>

#define PI 3.1415926535897932384626433f

class math
{
public:
	static float distance(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
	{
		return std::sqrt((t_pos1.x - t_pos2.x) * (t_pos1.x - t_pos2.x) + (t_pos1.y - t_pos2.y) * (t_pos1.y - t_pos2.y));
	}
	static float squareDistancebetweenPoints(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
	{
		return ((t_pos2.x - t_pos1.x) * (t_pos2.x - t_pos1.x) + (t_pos2.y - t_pos1.y) * (t_pos2.y - t_pos1.y));
	}
	static float distancebetweenPoints(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
	{
		return std::sqrtf((t_pos2.x - t_pos1.x) * (t_pos2.x - t_pos1.x) + (t_pos2.y - t_pos1.y) * (t_pos2.y - t_pos1.y));
	}

	static bool circleIntersects(sf::Vector2f t_pos1, sf::Vector2f t_pos2, float t_radius1, float t_radius2)
	{
		float distBetweenPoints = squareDistancebetweenPoints(t_pos1, t_pos2);
		float radSize = (t_radius1 + t_radius2) * (t_radius1 + t_radius2);
		return (distBetweenPoints <= radSize);
	}

	static sf::Vector2f displacement(sf::Vector2f t_loaction, sf::Vector2f t_aim)
	{
		sf::Vector2f displacement = t_aim - t_loaction;
		displacement /= std::sqrtf(displacement.x * displacement.x + displacement.y * displacement.y);
		return displacement;
	}
	static sf::Vector2f degreesToDisplacement(float t_angle)
	{
		float rad = degreesToRadians(t_angle);

		sf::Vector2f disp;
		disp.x = std::cos(rad);
		disp.y = std::sin(rad);

		return disp;
	}
	static float degreesToRadians(float t_degrees)
	{
		float radians = t_degrees * (PI / 180.0f);
		return radians;
	}
	static float radiansToDegrees(float t_radians)
	{
		float degrees = t_radians * 180.f / PI;
		return degrees;
	}
	static sf::Vector2f angleToPosition(float t_hypLen, float t_angle)
	{
		sf::Vector2f position;
		t_angle = degreesToRadians(t_angle);
		position.x = std::cos(t_angle) * t_hypLen;
		position.y = std::sin(t_angle) * t_hypLen;
		return position;
	}
	static float displacementToDegrees(sf::Vector2f t_displacement)
	{
		float angle = radiansToDegrees(std::atan2f(t_displacement.y, t_displacement.x));
		if (angle < 0.f)
			angle = 360.f + angle;
		if (angle > 360.f)
		{
			angle = angle - 360.f;
		}
		return angle;
	}
	static bool checkIsLeft(sf::Vector2f t_pointA, sf::Vector2f t_pointB, sf::Vector2f t_checkPoint)
	{
		// return ((x2 - x1) * (y3 - y1)) - ((y2 - y1) * (x3 - x1))
		return (((t_pointB.x - t_pointA.x) * (t_checkPoint.y - t_pointA.y) - (t_pointB.y - t_pointA.y) * (t_checkPoint.x - t_pointA.x)) > 0);
	}
	static bool containedInCone(sf::Vector2f t_pointA, sf::Vector2f t_pointB, sf::Vector2f t_pointC, sf::Vector2f t_checkPoint)
	{
		if (circleIntersects(t_pointA, t_checkPoint, distancebetweenPoints(t_pointA, t_pointB) + 80.f, 0.f))
			if (checkIsLeft(t_pointA, t_pointB, t_checkPoint) && checkIsLeft(t_pointC, t_pointA, t_checkPoint))
				return true;
		return false;
	}
	static sf::Vector2f rotatePoint(sf::Vector2f t_point, float t_angle)
	{
		float cos = std::cos(-t_angle);
		float sin = std::sin(-t_angle);
		float x = t_point.x * cos - t_point.y * sin;
		float y = t_point.x * sin + t_point.y * cos;
		return sf::Vector2f(x, y);
	}
	static bool positionInCircle(sf::Vector2f t_centerPos, float t_radius, sf::Vector2f t_pos)
	{
		float distBetweenPoints = squareDistancebetweenPoints(t_centerPos, t_pos);
		float radSize = t_radius * t_radius;
		return (distBetweenPoints <= radSize);
	}
	template <typename T>
	static bool nearlyEquals(T t_num1, T t_num2, T threshold = 1e-6)
	{
		if (std::abs(t_num1 - t_num2) < 1e-6)
		{
			return true;
		}
		return false;
	}
};

#endif // !SIMPLE_MATHS_H
