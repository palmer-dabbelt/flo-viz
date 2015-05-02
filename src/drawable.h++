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

#ifndef DRAWABLE_HXX
#define DRAWABLE_HXX

#include <SFML/Graphics.hpp>
#include <memory>

/* An object that can be drawn to the screen. */
class drawable {
public:
    typedef std::shared_ptr<drawable> ptr;

public:
    /* Draws the given object to the window, at whatever position and
     * size it deems appropriate. */
    virtual void draw(const std::shared_ptr<sf::RenderWindow>& window) = 0;
};

#endif
