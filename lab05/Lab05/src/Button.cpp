#include "Button.h"
#include "Game.h"


// basic initialisation
void Button::init(sf::Texture& t_texture, sf::Vector2i t_frameSize, sf::Vector2f t_position, int t_AnimLength, float t_frameDelay)
{
	m_frameAmt = t_AnimLength;
	m_frameDelay = t_frameDelay;
	m_buttonT = std::make_shared<sf::Texture>(t_texture);
	m_frameSize = t_frameSize;

	// initialise the sprite here:
	m_buttonS = std::make_shared<sf::Sprite>(); // make sure to inistialise the sprite
	m_buttonS->setTexture(*m_buttonT);
	m_buttonS->setPosition(t_position);
	m_buttonS->setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));
	RenderObject::getInstance().add(m_buttonS);
	// !

}

Button::~Button()
{
}

// call this on update to change the frame
void Button::updateFrame()
{
	int frameInt = static_cast<int>(m_frameTimer);
	if (m_inBounds)
	{
		if (m_frameTimer < m_frameAmt)
		{
			m_frameTimer += m_frameDelay;

			frameInt = static_cast<int>(m_frameTimer);

			if (t_currentFrame != frameInt)
			{
				t_currentFrame++;
				m_buttonS->setTextureRect(sf::IntRect(m_frameSize.x * t_currentFrame, m_startFrameHeight, m_frameSize.x, m_frameSize.y));
			}
		}
	}
	else
	{
		if (m_frameTimer > 0)
		{
			m_frameTimer -= m_frameDelay;

			frameInt = static_cast<int>(m_frameTimer);

			if (t_currentFrame != frameInt)
			{
				t_currentFrame--;
				m_buttonS->setTextureRect(sf::IntRect(m_frameSize.x * t_currentFrame, m_startFrameHeight, m_frameSize.x, m_frameSize.y));
			}
		}
	}
}

// check all intersections with the mouse (call this on click)
void Button::checkBounds(sf::Vector2f t_mousePos)
{
	if (m_buttonS->getGlobalBounds().contains(t_mousePos))
	{
		m_inBounds = true;
	}
	else
	{
		m_inBounds = false;
	}
}


// call this on initialisation to use a single sprite sheet
void Button::changeFrameHeight(int t_frameNumber)
{
	if (t_frameNumber >= 0)
	{
		m_startFrameHeight = m_frameSize.y * t_frameNumber;
		m_buttonS->setTextureRect(sf::IntRect(0, m_startFrameHeight, m_frameSize.x, m_frameSize.y));
	}
}

// call this on mouse release
bool Button::releaseButton()
{
	if (m_inBounds)
	{
		m_executeFunction();
		return true;
	}
	return false;
}