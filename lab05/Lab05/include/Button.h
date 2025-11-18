#ifndef BUTTON_H
#define BUTTON_H

#include "Library.h"
#include"RenderObject.h"
#include"Globals.h"
#include<functional>

///////////////////////////////////////////////
///					 How to use
//////////////////////////////////////////////
///
///  1 : initialise the button, can be put into list or similar
///			- anim length is that what you export -1 (for final frame hold)
/// 
///       ~  { call set frame height if multiple buttons are within same file
///			ensure you use 0 based indexing  }
/// 
///  2 : set the lambda function to which you will call when needed
///			 (use other calls as reference)
/// 
///  3 : call check bounds function (best in update)
/// 
///  4 : update the button
/// 
///  5 : call release button (this will execute the passed in function)
/// 
//////////////////////////////////////////////



//////////////////////////////////////////////
///            Potential issues
//////////////////////////////////////////////
///
///    - no while pressed down function
///
//////////////////////////////////////////////

class Button
{
public:
	void init(sf::Texture& t_texture, sf::Vector2i t_frameSize, sf::Vector2f t_position, int t_AnimLength = 0, float t_frameDelay = 0.0f);
	~Button();

	void updateFrame();
	void checkBounds(sf::Vector2f t_mousePos);
	void changeFrameHeight(int t_frameNumber);
	bool releaseButton();
	void setFunction(std::function<void()> t_executeFunction) { m_executeFunction = t_executeFunction; }

private:
	std::shared_ptr<sf::Sprite> m_buttonS;
	std::shared_ptr<sf::Texture> m_buttonT;

	sf::Vector2i m_frameSize{ 0,0 };

	int m_startFrameHeight{ 0 };
	int m_frameAmt{ 0 };
	int t_currentFrame{ 0 };
	float m_frameDelay{ 0 };
	float m_frameTimer{ 0 };

	bool m_inBounds{ false };

	std::function<void()> m_executeFunction = {};
};

#endif // !BUTTON_H
