g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\main.cpp -o obj\Release\main.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\assets.cpp -o obj\Release\src\assets.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\calc_helper.cpp -o obj\Release\src\calc_helper.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\cockpit.cpp -o obj\Release\src\cockpit.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\entity.cpp -o obj\Release\src\entity.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\file_handler.cpp -o obj\Release\src\file_handler.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\hud.cpp -o obj\Release\src\hud.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\intermission_menu.cpp -o obj\Release\src\intermission_menu.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\key_bindings.cpp -o obj\Release\src\key_bindings.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\main_menu.cpp -o obj\Release\src\main_menu.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\market_menu.cpp -o obj\Release\src\market_menu.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\mech.cpp -o obj\Release\src\mech.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\player_controller.cpp -o obj\Release\src\player_controller.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\settings.cpp -o obj\Release\src\settings.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\settings_menu.cpp -o obj\Release\src\settings_menu.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\tutorial.cpp -o obj\Release\src\tutorial.o
g++.exe -Wall -O2 -IC:\SFML-2.5.1\include -Iinclude -Isrc -c C:\SFMechSimulator\src\world_generator.cpp -o obj\Release\src\world_generator.o
g++.exe -LC:\SFML-2.5.1\lib -o bin\Release\SFMechSimulator.exe obj\Release\main.o obj\Release\src\assets.o obj\Release\src\calc_helper.o obj\Release\src\cockpit.o obj\Release\src\entity.o obj\Release\src\file_handler.o obj\Release\src\hud.o obj\Release\src\intermission_menu.o obj\Release\src\key_bindings.o obj\Release\src\main_menu.o obj\Release\src\market_menu.o obj\Release\src\mech.o obj\Release\src\player_controller.o obj\Release\src\settings.o obj\Release\src\settings_menu.o obj\Release\src\tutorial.o obj\Release\src\world_generator.o  -s  -lmingw32 -luser32 -lgdi32 -lwinmm -ldxguid -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -mwindows
