#include "Settings.h"
#include "SettingsStorage.h"

/// <summary>
/// default constructor
/// </summary>
Settings::Settings()
{
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("VSYNC TRUE"));
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("VSYNC FALSE"));
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("Screen x ++"));
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("Screen x --"));
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("Screen y ++"));
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("Screen y --"));
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("SAVE DATA"));
	m_testButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("LOAD DATA"));





	SettingsStorage::getInstance().initSettings();
}

/// <summary>
/// default deconstructor
/// </summary>
Settings::~Settings()
{
}

/// <summary>
/// resets all values to default as needed
/// </summary>
void Settings::resetLevel()
{
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void Settings::events(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type || sf::Event::KeyReleased == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}
	else
	{
		processMouse(t_event);
	}
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void Settings::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void Settings::update()
{
	if (m_testButtons.at(0)->clicked())
	{
		SettingsData& data = SettingsStorage::getInstance().getSettings();
		data.vsync = true;
		DEBUG_MSG("VSYNC : " + std::to_string(data.vsync));
	}
	if (m_testButtons.at(1)->clicked())
	{
		SettingsData& data = SettingsStorage::getInstance().getSettings();
		data.vsync = false;
		DEBUG_MSG("VSYNC : " + std::to_string(data.vsync));
	}
	if (m_testButtons.at(2)->clicked())
	{
		SettingsData& data = SettingsStorage::getInstance().getSettings();
		data.ScreenSize.x += 10;
		DEBUG_MSG("Screen : " + std::to_string(data.ScreenSize.x) + "x" + std::to_string(data.ScreenSize.y));
	}
	if (m_testButtons.at(3)->clicked())
	{
		SettingsData& data = SettingsStorage::getInstance().getSettings();
		data.ScreenSize.x -= 10;
		DEBUG_MSG("Screen : " + std::to_string(data.ScreenSize.x) + "x" + std::to_string(data.ScreenSize.y));
	}
	if (m_testButtons.at(4)->clicked())
	{
		SettingsData& data = SettingsStorage::getInstance().getSettings();
		data.ScreenSize.y += 10;
		DEBUG_MSG("Screen : " + std::to_string(data.ScreenSize.x) + "x" + std::to_string(data.ScreenSize.y));
	}
	if (m_testButtons.at(5)->clicked())
	{
		SettingsData& data = SettingsStorage::getInstance().getSettings();
		data.ScreenSize.y -= 10;
		DEBUG_MSG("Screen : " + std::to_string(data.ScreenSize.x) + "x" + std::to_string(data.ScreenSize.y));
	}
	if (m_testButtons.at(6)->clicked())
	{
		DEBUG_MSG("CHANGES HAVE BEEN SAVED");
		SettingsStorage::getInstance().writeOutNewSettings();
	}
	if (m_testButtons.at(7)->clicked())
	{
		DEBUG_MSG("CHANGES HAVE BEEN LOADED");
		RenderObject::getInstance().loadsettings();
	}
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void Settings::processMouse(sf::Event& t_event)
{
	if (sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//mouseButtonUp();
	}
}
