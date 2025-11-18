#ifndef SETTINGS_STORAGE_H
#define SETTINGS_STORAGE_H

#include "Globals.h"
#include "YamlLoader.h"

class SettingsStorage
{
public:
    static SettingsStorage& getInstance()
    {
        static SettingsStorage instance;
        return instance;
    }

    // DELETE FUNCTIONS TO AVOID MORE INSTANCES
    SettingsStorage(SettingsStorage const&) = delete;
    void operator=(SettingsStorage const&) = delete;

    // Getters for all the variables!
    void initSettings() 
    { 
        std::string loc = "settings";
        yamlLoader::loadSettings(loc, m_data);
    }
    SettingsData& getSettings() { return m_data; }
    bool writeOutNewSettings() 
    {
        std::string loc = "settings";
        yamlLoader::WriteSettings(loc, m_data);
        return false;
    }

private:
    SettingsStorage()
    {  }

////////////////////////////////////////////////////////
///     Storage of all the Variables
////////////////////////////////////////////////////////
    SettingsData m_data;
};

#endif // !SETTINGS_STORAGE_H
