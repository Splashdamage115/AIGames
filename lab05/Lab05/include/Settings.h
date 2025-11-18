#ifndef SETTINGS_H
#define SETTINGS_H

#include "GameMode.h"
#include "SimpleButton.h"
#include <vector>

class Settings : public GameMode
{
public:
	Settings();  // standard constructor
	~Settings(); // standard deconstructor (shouldnt be used)

	void resetLevel()override;                         // used to reset the level for each session instead of reconstructing
	void events(sf::Event& t_event)override;           // used to handle all new events outside key presses
	void update()override;         // all update events

private:
	void processKeys(sf::Event& t_event)override;      // handles all key inputs
	void processMouse(sf::Event& t_event)override;     // handles all mouse events

	std::vector <std::shared_ptr<SimpleButton>> m_testButtons;
};

#endif // !SETTINGS_H
