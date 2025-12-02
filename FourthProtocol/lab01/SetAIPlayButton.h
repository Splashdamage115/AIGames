#pragma once

#include "Library.h"

class SetAIPlayButton
{
public:
	void Init();
	void update();

private:
	std::shared_ptr<sf::RectangleShape> m_box;
	std::shared_ptr<sf::Text> m_text;
	std::shared_ptr<sf::RectangleShape> m_hitBox;

	bool mouseDown = false;
};

