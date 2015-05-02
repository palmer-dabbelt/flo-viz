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

#ifndef KEYS_HXX
#define KEYS_HXX

#include <functional>
#include <map>
#include <memory>
#include <SFML/Window/Keyboard.hpp>

/* A little class that handles keyboard events. */
class keys {
public:
    typedef std::shared_ptr<keys> ptr;

private:
    std::map<sf::Keyboard::Key, std::string> _help;
    std::map<sf::Keyboard::Key, std::function<void(void)> > _on_press;
    std::map<sf::Keyboard::Key, std::function<void(void)> > _on_release;

public:
    /* Creates a new, empty, key set. */
    keys(void);

public:
    /* Inserts a new keyboard event into the set. */
    void insert(sf::Keyboard::Key key, const std::string& help,
                std::function<void(void)> on_press,
                std::function<void(void)> on_release);

    /* Prints a help text for every key in this mapping. */
    void print_help_text(void);

    /* Calls the callback for a given key. */
    void press(sf::Keyboard::Key key);
    void release(sf::Keyboard::Key key);
};

#endif
