#ifndef KEY_BINDINGS_H
#define KEY_BINDINGS_H

#include<file_handler.h>
#include<SFML/Graphics.hpp>

class key_bindings
{
    public:
        std::map<std::string, sf::Keyboard::Key> bindings;
        void load(std::string cwd);
    private:
        std::map<std::string, sf::Keyboard::Key> keys;
};

#endif // KEY_BINDINGS_H
