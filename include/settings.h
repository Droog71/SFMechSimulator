#ifndef SETTINGS_H
#define SETTINGS_H

extern bool music;
extern bool invert_mouse;
extern double audio_volume;

void save_settings(std::string cwd);
void load_settings(std::string cwd);

#endif // SETTINGS_H
