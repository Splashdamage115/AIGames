#pragma once

#include "Library.h"

class RenderObject
{
public:
	static RenderObject& getInstance()
	{
		static RenderObject instance;
		return instance;
	}

	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	RenderObject(RenderObject const&) = delete;
	void operator=(RenderObject const&) = delete;

	sf::RenderWindow& getWindow() { return m_window; }

	void closeWindow();
	void start();
	bool addNewRenderObject(std::shared_ptr<sf::Drawable> t_renderObj, int t_layerNum);
	void render();
private:
	RenderObject(); // Constructor
	std::vector<std::vector<std::weak_ptr<sf::Drawable>>> m_layers;
	std::vector<std::vector<std::weak_ptr<sf::Vertex>>> m_lines;

	sf::RenderWindow m_window;
};

