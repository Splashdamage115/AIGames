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
//     2. Call <sf::text name>.setFont(*GlobalFontStorage::getInstance().getFont());
// 
// 
// *******************************************************************************************************
// 
//	Notes:
//			
// 
// *******************************************************************************************************

#ifndef GLOBAL_FONT_STORAGE_H
#define GLOBAL_FONT_STORAGE_H

#include "Library.h"

class GlobalFontStorage
{
public:
    static GlobalFontStorage& getInstance()
    {
        static GlobalFontStorage instance;
        return instance;
    }

    // DELETE FUNCTIONS TO AVOID MORE INSTANCES
    GlobalFontStorage(GlobalFontStorage const&) = delete;
    void operator=(GlobalFontStorage const&) = delete;

    void init()
    {
        g_globalFont = std::make_shared<sf::Font>();

        // load the font from the file and print error if unsuccessful
        if (!g_globalFont->loadFromFile(".\\ASSETS\\FONTS\\PixelSans.ttf"))
        {
            DEBUG_MSG("COULDNT FIND GLOBAL FONT");
            exit(2);
        }
    }

    std::shared_ptr<sf::Font> getFont() { return g_globalFont; }
private:
    GlobalFontStorage() {}

    std::shared_ptr<sf::Font> g_globalFont;
};

#endif // !GLOBAL_FONT_STORAGE_H
