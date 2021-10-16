#include <key_bindings.h>

// Creates aliases for key binds and loads current bindings from file
void key_bindings::load(std::string cwd)
{
    keys["A"] = sf::Keyboard::A;
    keys["B"] = sf::Keyboard::B;
    keys["C"] = sf::Keyboard::C;
    keys["D"] = sf::Keyboard::D;
    keys["E"] = sf::Keyboard::E;
    keys["F"] = sf::Keyboard::F;
    keys["G"] = sf::Keyboard::G;
    keys["H"] = sf::Keyboard::H;
    keys["I"] = sf::Keyboard::I;
    keys["J"] = sf::Keyboard::J;
    keys["K"] = sf::Keyboard::K;
    keys["L"] = sf::Keyboard::L;
    keys["M"] = sf::Keyboard::M;
    keys["N"] = sf::Keyboard::N;
    keys["O"] = sf::Keyboard::O;
    keys["P"] = sf::Keyboard::P;
    keys["Q"] = sf::Keyboard::Q;
    keys["R"] = sf::Keyboard::R;
    keys["S"] = sf::Keyboard::S;
    keys["T"] = sf::Keyboard::T;
    keys["U"] = sf::Keyboard::U;
    keys["V"] = sf::Keyboard::V;
    keys["W"] = sf::Keyboard::W;
    keys["X"] = sf::Keyboard::X;
    keys["Y"] = sf::Keyboard::Y;
    keys["Z"] = sf::Keyboard::Z;

    keys["Up"] = sf::Keyboard::Up;
    keys["Down"] = sf::Keyboard::Down;
    keys["Left"] = sf::Keyboard::Left;
    keys["Right"] = sf::Keyboard::Right;

    keys["LControl"] = sf::Keyboard::LControl;
    keys["RControl"] = sf::Keyboard::RControl;
    keys["LShift"] = sf::Keyboard::LShift;
    keys["RShift"] = sf::Keyboard::RShift;
    keys["LAlt"] = sf::Keyboard::LAlt;
    keys["RAlt"] = sf::Keyboard::RAlt;
    keys["Space"] = sf::Keyboard::Space;
    keys["Return"] = sf::Keyboard::Return;

    keys["Num0"] = sf::Keyboard::Num0;
    keys["Num1"] = sf::Keyboard::Num1;
    keys["Num2"] = sf::Keyboard::Num2;
    keys["Num3"] = sf::Keyboard::Num3;
    keys["Num4"] = sf::Keyboard::Num4;
    keys["Num5"] = sf::Keyboard::Num5;
    keys["Num6"] = sf::Keyboard::Num6;
    keys["Num7"] = sf::Keyboard::Num7;
    keys["Num8"] = sf::Keyboard::Num8;
    keys["Num9"] = sf::Keyboard::Num9;

    keys["Numpad0"] = sf::Keyboard::Numpad0;
    keys["Numpad1"] = sf::Keyboard::Numpad1;
    keys["Numpad2"] = sf::Keyboard::Numpad2;
    keys["Numpad3"] = sf::Keyboard::Numpad3;
    keys["Numpad4"] = sf::Keyboard::Numpad4;
    keys["Numpad5"] = sf::Keyboard::Numpad5;
    keys["Numpad6"] = sf::Keyboard::Numpad6;
    keys["Numpad7"] = sf::Keyboard::Numpad7;
    keys["Numpad8"] = sf::Keyboard::Numpad8;
    keys["Numpad9"] = sf::Keyboard::Numpad9;

    keys["F1"] = sf::Keyboard::F1;
    keys["F2"] = sf::Keyboard::F2;
    keys["F3"] = sf::Keyboard::F3;
    keys["F4"] = sf::Keyboard::F4;
    keys["F5"] = sf::Keyboard::F5;
    keys["F6"] = sf::Keyboard::F6;
    keys["F7"] = sf::Keyboard::F7;
    keys["F8"] = sf::Keyboard::F8;
    keys["F9"] = sf::Keyboard::F9;
    keys["F10"] = sf::Keyboard::F10;
    keys["F11"] = sf::Keyboard::F11;
    keys["F12"] = sf::Keyboard::F12;

    keys["Tilde"] = sf::Keyboard::Tilde;
    keys["Tab"] = sf::Keyboard::Tab;

    keys["Home"] = sf::Keyboard::Home;
    keys["PageUp"] = sf::Keyboard::PageUp;
    keys["PageDown"] = sf::Keyboard::PageDown;
    keys["Insert"] = sf::Keyboard::Insert;
    keys["BackSpace"] = sf::Keyboard::BackSpace;
    keys["Delete"] = sf::Keyboard::Delete;
    keys["Pause"] = sf::Keyboard::Pause;

    keys["Dash"] = sf::Keyboard::Dash;
    keys["Equal"] = sf::Keyboard::Equal;
    keys["BackSlash"] = sf::Keyboard::BackSlash;
    keys["LBracket"] = sf::Keyboard::LBracket;
    keys["RBracket"] = sf::Keyboard::RBracket;
    keys["SemiColon"] = sf::Keyboard::SemiColon;
    keys["Quote"] = sf::Keyboard::Quote;
    keys["Comma"] = sf::Keyboard::Comma;
    keys["Period"] = sf::Keyboard::Period;
    keys["Slash"] = sf::Keyboard::Slash;

    size_t pos = 0;
    std::string entry;
    std::string delimeter = "\n";
    std::string saved_bindings = get_file_contents(cwd + "/bindings.list");

    while ((pos = saved_bindings.find(delimeter)) != std::string::npos)
    {
        entry = saved_bindings.substr(0, pos);
        std::string action = entry.substr(0, entry.find(":"));
        std::string bound = entry.substr(entry.find(":") + 1, pos);
        bindings[action] = keys[bound];
        saved_bindings.erase(0, pos + delimeter.length());
    }
}
