/*
 * Copyright (C) 2015 Palmer Dabbelt
 *   <palmer@dabbelt.com>
 *
 * This file is part of flo-viz.
 *
 * flo-viz is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * flo-viz is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with flo-viz.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "keys.h++"
#include <iostream>

static std::string find_name_for_key(sf::Keyboard::Key key);

keys::keys(void)
    : _help(),
      _on_press(),
      _on_release()
{
}

void keys::insert(sf::Keyboard::Key key, const std::string& help,
                  std::function<void(void)> on_press,
                  std::function<void(void)> on_release)
{
    _help[key] = help;
    _on_press[key] = on_press;
    _on_release[key] = on_release;
}

void keys::print_help_text(void)
{
    std::cout << "Key bindings:\n";
    for (const auto& pair: _help) {
        auto key = pair.first;
        auto text = pair.second;

        std::cout << "\t" << find_name_for_key(key) << "\t" << text << "\n";
    }
    std::cout << std::flush;
}

void keys::press(sf::Keyboard::Key key)
{
    auto l = _on_press.find(key);
    if (l == _on_press.end())
        return;

    l->second();
}

void keys::release(sf::Keyboard::Key key)
{
    auto l = _on_release.find(key);
    if (l == _on_release.end())
        return;

    l->second();
}

std::string find_name_for_key(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Key::A:
        return "A";
    case sf::Keyboard::Key::B:
        return "B";
    case sf::Keyboard::Key::C:
        return "C";
    case sf::Keyboard::Key::D:
        return "D";
    case sf::Keyboard::Key::E:
        return "E";
    case sf::Keyboard::Key::F:
        return "F";
    case sf::Keyboard::Key::G:
        return "G";
    case sf::Keyboard::Key::H:
        return "H";
    case sf::Keyboard::Key::I:
        return "I";
    case sf::Keyboard::Key::J:
        return "J";
    case sf::Keyboard::Key::K:
        return "K";
    case sf::Keyboard::Key::L:
        return "L";
    case sf::Keyboard::Key::M:
        return "M";
    case sf::Keyboard::Key::N:
        return "N";
    case sf::Keyboard::Key::O:
        return "O";
    case sf::Keyboard::Key::P:
        return "P";
    case sf::Keyboard::Key::Q:
        return "Q";
    case sf::Keyboard::Key::R:
        return "R";
    case sf::Keyboard::Key::S:
        return "S";
    case sf::Keyboard::Key::T:
        return "T";
    case sf::Keyboard::Key::U:
        return "U";
    case sf::Keyboard::Key::V:
        return "V";
    case sf::Keyboard::Key::W:
        return "W";
    case sf::Keyboard::Key::X:
        return "X";
    case sf::Keyboard::Key::Y:
        return "Y";
    case sf::Keyboard::Key::Z:
        return "Z";
    case sf::Keyboard::Key::Num0:
        return "0";
    case sf::Keyboard::Key::Num1:
        return "1";
    case sf::Keyboard::Key::Num2:
        return "2";
    case sf::Keyboard::Key::Num3:
        return "3";
    case sf::Keyboard::Key::Num4:
        return "4";
    case sf::Keyboard::Key::Num5:
        return "5";
    case sf::Keyboard::Key::Num6:
        return "6";
    case sf::Keyboard::Key::Num7:
        return "7";
    case sf::Keyboard::Key::Num8:
        return "8";
    case sf::Keyboard::Key::Num9:
        return "9";
    case sf::Keyboard::Key::Escape:
        return "Escape";
    case sf::Keyboard::Key::LControl:
        return "left Control";
    case sf::Keyboard::Key::LShift:
        return "left Shift";
    case sf::Keyboard::Key::LAlt:
        return "left Alt";
    case sf::Keyboard::Key::LSystem:
        return "left OS specific key: window (Windows and Linux), apple (MacOS X), ...";
    case sf::Keyboard::Key::RControl:
        return "right Control";
    case sf::Keyboard::Key::RShift:
        return "right Shift";
    case sf::Keyboard::Key::RAlt:
        return "right Alt";
    case sf::Keyboard::Key::RSystem:
        return "right OS specific key: window (Windows and Linux), apple (MacOS X), ...";
    case sf::Keyboard::Key::Menu:
        return "Menu";
    case sf::Keyboard::Key::LBracket:
        return "[";
    case sf::Keyboard::Key::RBracket:
        return "]";
    case sf::Keyboard::Key::SemiColon:
        return ";";
    case sf::Keyboard::Key::Comma:
        return ",";
    case sf::Keyboard::Key::Period:
        return ".";
    case sf::Keyboard::Key::Quote:
        return "'";
    case sf::Keyboard::Key::Slash:
        return "/";
    case sf::Keyboard::Key::BackSlash:
        return "\\";
    case sf::Keyboard::Key::Tilde:
        return "~";
    case sf::Keyboard::Key::Equal:
        return "=";
    case sf::Keyboard::Key::Dash:
        return "-";
    case sf::Keyboard::Key::Space:
        return "Space";
    case sf::Keyboard::Key::Return:
        return "Return";
    case sf::Keyboard::Key::BackSpace:
        return "Backspace";
    case sf::Keyboard::Key::Tab:
        return "Tabulation";
    case sf::Keyboard::Key::PageUp:
        return "Page up";
    case sf::Keyboard::Key::PageDown:
        return "Page down";
    case sf::Keyboard::Key::End:
        return "End";
    case sf::Keyboard::Key::Home:
        return "Home";
    case sf::Keyboard::Key::Insert:
        return "Insert";
    case sf::Keyboard::Key::Delete:
        return "Delete";
    case sf::Keyboard::Key::Add:
        return "+";
    case sf::Keyboard::Key::Subtract:
        return "-";
    case sf::Keyboard::Key::Multiply:
        return "*";
    case sf::Keyboard::Key::Divide:
        return "/";
    case sf::Keyboard::Key::Left:
        return "Left arrow.";
    case sf::Keyboard::Key::Right:
        return "Right arrow.";
    case sf::Keyboard::Key::Up:
        return "Up arrow.";
    case sf::Keyboard::Key::Down:
        return "Down arrow.";
    case sf::Keyboard::Key::Numpad0:
        return "numpad 0";
    case sf::Keyboard::Key::Numpad1:
        return "numpad 1";
    case sf::Keyboard::Key::Numpad2:
        return "numpad 2";
    case sf::Keyboard::Key::Numpad3:
        return "numpad 3";
    case sf::Keyboard::Key::Numpad4:
        return "numpad 4";
    case sf::Keyboard::Key::Numpad5:
        return "numpad 5";
    case sf::Keyboard::Key::Numpad6:
        return "numpad 6";
    case sf::Keyboard::Key::Numpad7:
        return "numpad 7";
    case sf::Keyboard::Key::Numpad8:
        return "numpad 8";
    case sf::Keyboard::Key::Numpad9:
        return "numpad 9";
    case sf::Keyboard::Key::F1:
        return "F1";
    case sf::Keyboard::Key::F2:
        return "F2";
    case sf::Keyboard::Key::F3:
        return "F3";
    case sf::Keyboard::Key::F4:
        return "F4";
    case sf::Keyboard::Key::F5:
        return "F5";
    case sf::Keyboard::Key::F6:
        return "F6";
    case sf::Keyboard::Key::F7:
        return "F7";
    case sf::Keyboard::Key::F8:
        return "F8";
    case sf::Keyboard::Key::F9:
        return "F9";
    case sf::Keyboard::Key::F10:
        return "F10";
    case sf::Keyboard::Key::F11:
        return "F11";
    case sf::Keyboard::Key::F12:
        return "F12";
    case sf::Keyboard::Key::F13:
        return "F13";
    case sf::Keyboard::Key::F14:
        return "F14";
    case sf::Keyboard::Key::F15:
        return "F15";
    case sf::Keyboard::Key::Pause:
        return "Pause ";

    case sf::Keyboard::Key::Unknown:
    case sf::Keyboard::Key::KeyCount:
        break;
    }

    std::cerr << "Unknown key\n";
    abort();
}

