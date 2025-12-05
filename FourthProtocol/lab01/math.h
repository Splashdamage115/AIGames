#ifndef SIMPLE_MATHS_H
#define SIMPLE_MATHS_H

#include <SFML/Graphics.hpp>

#define PI 3.1415926535897932384626433f

class math
{
public:
	/*! \brief check distance between 2 points
	*
	*  standard distance calculation
	*/
	static float distance(sf::Vector2f t_pos1, sf::Vector2f t_pos2)
	{
		return std::sqrt((t_pos1.x - t_pos2.x) * (t_pos1.x - t_pos2.x) + (t_pos1.y - t_pos2.y) * (t_pos1.y - t_pos2.y));
	}
};

#endif // !SIMPLE_MATHS_H
