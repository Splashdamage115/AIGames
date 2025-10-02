#include "RenderObject.h"

RenderObject::RenderObject() : m_window{ sf::VideoMode{ sf::Vector2u{sf::VideoMode::getDesktopMode().size}, 32U}, "AI Games", sf::State::Fullscreen}
{
}

void RenderObject::closeWindow()
{
	m_window.close();
}

void RenderObject::start()
{
	m_layers.emplace_back();
}

bool RenderObject::addNewRenderObject(std::shared_ptr<sf::Drawable> t_renderObj, int t_layerNum)
{
	if (m_layers.size() - 1 < t_layerNum)
	{
		while (m_layers.size() - 1 < t_layerNum)
			m_layers.emplace_back();
	}
	
	for (unsigned int i = 0; i < m_layers.at(t_layerNum).size(); i++)
	{
		if (m_layers.at(t_layerNum).at(i).lock() == nullptr) // if the object is empty
		{
			m_layers.at(t_layerNum).at(i) = t_renderObj;
			return true;
		}
	}

	m_layers.at(t_layerNum).push_back(t_renderObj);
	return true;
}

void RenderObject::render()
{
	m_window.clear();

	for (int i = 0; i < m_layers.size();i++)
	{
		if (!m_layers.at(i).empty()) // error handling
		{
			for each(auto var in m_layers.at(i))
			{
				if (var.lock())
					m_window.draw(*var.lock());
			}
		}
	}
	m_window.display();
}
