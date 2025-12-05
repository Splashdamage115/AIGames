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

	/*! \brief close the window object and clean up
	*
	*  
	*/
	void closeWindow();

	/*! \brief start all standard window stuff
	*
	*  clear all layers to begin with
	*/
	void start();

	/*! \brief append new object to render
	*
	*  add new object into the designated layer and render that object
	*/
	bool addNewRenderObject(std::shared_ptr<sf::Drawable> t_renderObj, int t_layerNum);

	/*! \brief render all layers
	*
	*  loop through all layers and render them all
	*/
	void render();
private:
	RenderObject(); // Constructor
	std::vector<std::vector<std::weak_ptr<sf::Drawable>>> m_layers;

	sf::RenderWindow m_window;
};

