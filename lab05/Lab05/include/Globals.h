// global variables for the game
#ifndef GLOBALS_H
#define GLOBALS_H

const unsigned int SCREEN_WIDTH = 1920; // width of the screen for maths
const unsigned int SCREEN_HEIGHT = 1080; // height of the screen for maths

enum class GameModeClass
{
	None,
	Menu,
	Gameplay,
	Settings
};

struct Vector2i
{
	int x, y;
};

struct SettingsData
{
	bool vsync{ false };
	Vector2i ScreenSize;
};

#endif // !GLOBALS_H