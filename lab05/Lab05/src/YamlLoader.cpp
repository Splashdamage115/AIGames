#include "YamlLoader.h"

// read
void operator >> (const YAML::Node& t_node, SettingsData& t_settingsData)
{
	t_settingsData.vsync = t_node["vsync"].as<int>();
	t_settingsData.ScreenSize.x = t_node["Screen"]["x"].as<int>();
	t_settingsData.ScreenSize.y = t_node["Screen"]["y"].as<int>();
}

// write
void operator << (YAML::Node& t_node, const SettingsData& t_settingsData)
{
	t_node["vsync"] = static_cast<int>(t_settingsData.vsync);
	t_node["Screen"]["x"] = t_settingsData.ScreenSize.x;
	t_node["Screen"]["y"] = t_settingsData.ScreenSize.y;
}

/// <summary>
/// @brief try to load the settings data
///    this can be used as a simple template for more yaml loading
/// </summary>
/// <param name="t_loadFileName">files name</param>
/// <param name="t_settings">settings data struct</param>
void yamlLoader::loadSettings(std::string t_loadFileName, SettingsData& t_settings)
{
	std::string filename = ".\\ASSETS\\DATA\\SETTINGS\\" + t_loadFileName + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> t_settings;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}

/// <summary>
/// @brief dumps new settings into the yaml file
/// 
/// </summary>
/// <param name="t_loadFileName">file to dump into</param>
/// <param name="t_settings">settings data struct</param>
void yamlLoader::WriteSettings(std::string t_loadFileName, SettingsData& t_settings)
{


	std::string filename = ".\\ASSETS\\DATA\\SETTINGS\\" + t_loadFileName + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode << t_settings;

		std::ofstream fout(filename);
		fout << baseNode; // dump it back into the file
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}
