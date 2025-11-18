// *******************************************************************************************************
//
//													HOW TO USE
// 
// *******************************************************************************************************
//
// 
//     1. Include this file (best in cpp file)
// 
//    
//     2. make the "Drawable" an std::shared_ptr
//          ~e.g. std::shared_ptr<sf::Sprite> m_playerBody
// 
//    
//     3. Enable the shared pointer (in the constructor, or other)
//          ~e.g. m_playerBody = std::make_shared<sf::Sprite>();
// 
// 
//     4. pass the sprite to the desired layer
//          ~e.g. RenderObject::getInstance().add(m_playerBody);
// 
// 
//     5. use the "m_playerBody" pointer as normally desired / required
// 
// 
// *******************************************************************************************************
// 
//	Notes:
//			
// 
// *******************************************************************************************************
//
//                                       Copy Paste Example
//
// *******************************************************************************************************
/*

    m_sfmlLogoS = std::make_shared<sf::Sprite>();

	if (!m_sfmlLogoT.loadFromFile("ASSETS\\IMAGES\\Misc\\SFML-LOGO.png"))
	{
		DEBUG_MSG("COULDNT FIND SFML LOGO");
	}
	else
	{
		m_sfmlLogoS->setTexture(m_sfmlLogoT);
		m_sfmlLogoS->setPosition(200.f, 200.f);

		RenderObject::getInstance().add(m_sfmlLogoS);
	}

*/

#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "Library.h"

#include"Globals.h"

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
    void closeWindow() { m_window.close(); }

    void loadsettings();

    // add a new item to be rendered
    void add(std::shared_ptr<sf::Drawable> t_new);
    // add a new item to the hud (hud is drawn above the standard game)
    void addHUD(std::shared_ptr<sf::Drawable> t_new);
    // add a new item to the background (drawn at the bottom)
    void addBG(std::shared_ptr<sf::Drawable> t_new);

    // clear list of render objects
    void clear();

    void render();
private:
    RenderObject(); // Constructor

    void appendToObject(std::vector<std::weak_ptr< sf::Drawable >>& t_obj, std::shared_ptr<sf::Drawable> t_new);

    std::vector<std::weak_ptr< sf::Drawable >> m_hud;
    std::vector<std::weak_ptr< sf::Drawable >> m_backGround;
    std::vector<std::weak_ptr< sf::Drawable >> m_assets;

    sf::RenderWindow m_window;
};

#endif // !RENDER_OBJECT_H
