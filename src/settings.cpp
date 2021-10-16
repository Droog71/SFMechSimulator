#include <string>
#include <settings.h>
#include <file_handler.h>

bool music = true;
bool invert_mouse = false;
double audio_volume = 1;

// Loads settings from file
void load_settings(std::string cwd)
{
    size_t pos = 0;
    std::string entry;
    std::string delimeter = "\n";
    std::string saved_settings = get_file_contents(cwd + "/settings.list");

    while ((pos = saved_settings.find(delimeter)) != std::string::npos)
    {
        entry = saved_settings.substr(0, pos);
        std::string key = entry.substr(0, entry.find(":"));
        std::string value = entry.substr(entry.find(":") + 1, pos);
        if (key == "volume")
        {
            audio_volume = std::stod(value);
        }
        if (key == "music")
        {
            music = std::stoi(value);
        }
        if (key == "invert_mouse")
        {
            invert_mouse = std::stoi(value);
        }
        saved_settings.erase(0, pos + delimeter.length());
    }
}

// Saves settings to file
void save_settings(std::string cwd)
{
    std::string current_settings = "volume:" + std::to_string(audio_volume) + "\n" +
                                    "music:" + std::to_string(music) + "\n";
                                    "invert_mouse:" + std::to_string(invert_mouse) + "\n";

    write_to_file(cwd + "/settings.list", current_settings);
}
