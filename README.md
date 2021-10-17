SFMechSimulator
===============

_A pseudo 3D mech simulator created with C++ and SFML_ <br />

Pilot a giant robot and battle other giant robots in a pseudo 3D environment. <br />
Repair and upgrade your mech between missions. <br />
Carefully select upgrades and develop winning strategies in combat. <br />

<img src="https://i.imgur.com/Kt5mlTH.png" alt="SF Mech Sim" width="427" height="240">

**Compiling** <br />

_Windows:_ <br />

Download SFML and GCC here https://www.sfml-dev.org/download/sfml/2.5.1/ <br />
You will need 'MinGW Builds 7.3.0 (64-bit)' and SFML 'GCC 7.3.0 MinGW (SEH) - 64-bit' <br />
For 32 bit systems you will need 'MinGW Builds 7.3.0 (32-bit)' and 'GCC 7.3.0 MinGW (DW2) - 32-bit' <br />

Clone this repository to C:\ so the source code is present at C:\SFMechSimulator <br />
Extract the downloaded SFML package to C:\ so SFML is present at C:\SFML-2.5.1 <br />
Run the compile_windows.bat script <br />
Run SFMechSimulator.exe to play the game <br />
To run the game in a window, use the command line argument '-window' <br />
ie: 'SFMechSimulator.exe -window 1280 720' <br />
The window cannot be smaller than 1280x720 <br />

_Mac:_ <br />

Clone this repository. <br />
Install g++ as described here http://www.edparrish.net/common/macgpp.php#installg++ <br />
Download SFML here https://www.sfml-dev.org/download/sfml/2.5.1/ <br />
Copy the contents of the SFML Frameworks and extlibs directories to /Library/Frameworks <br />
Run the compile_mac.sh script <br />
Run the SFMechSimulator executable to play the game <br />
To run the game in a window, use the command line argument '-window' <br />
ie: './SFMechSimulator -window 1280 720' <br />
The window cannot be smaller than 1280x720 <br />

_Linux:_ <br />

Clone this repository. <br />
Install SFML, ie: 'sudo apt-get install libsfml-dev' <br />
Run the compile_linux.sh script <br />
Run the SFMechSimulator executable to play the game <br />
To run the game in a window, use the command line argument '-window' <br />
ie: './SFMechSimulator -window 1280 720' <br />
The window cannot be smaller than 1280x720 <br />

**Playing the Game** <br />

Click the 'NEW GAME' button at the main menu <br />
Press F1 to start the tutorial <br />

Key bindings can be reassigned by editing the bindings.list file in the game directory <br />
All possible key aliases can be found at the following link <br />
https://github.com/Droog71/SFMechSimulator/blob/main/src/key_bindings.cpp
