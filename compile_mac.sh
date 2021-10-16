#! /bin/bash

g++ -std=c++11 -F/Library/Frameworks -Iinclude -framework sfml-window -framework sfml-graphics -framework sfml-audio -framework sfml-system main.cpp $PWD/src/settings_menu.cpp $PWD/src/cockpit.cpp $PWD/src/settings.cpp $PWD/src/market_menu.cpp $PWD/src/tutorial.cpp $PWD/src/key_bindings.cpp $PWD/src/assets.cpp $PWD/src/calc_helper.cpp $PWD/src/entity.cpp $PWD/src/file_handler.cpp $PWD/src/hud.cpp $PWD/src/intermission_menu.cpp $PWD/src/main_menu.cpp $PWD/src/mech.cpp $PWD/src/player_controller.cpp $PWD/src/world_generator.cpp -o SFMechSimulator
