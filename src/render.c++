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

#include "render.h++"
#include <iostream>

render::render(const flo::ptr& circuit, int width, int height, float dpi)
    : _circuit(circuit),
      _width(width),
      _height(height),
      _dpi(dpi),
      _top( module::parse(circuit) )
{
    if (_top == NULL) {
        std::cerr << "Unable to parse module hierarchy\n";
        abort();
    }
}

void render::resize(int new_width, int new_height, float new_dpi)
{
    _width = new_width;
    _height = new_height;
    _dpi = new_dpi;
}

std::vector<drawable::ptr> render::all_visible(void) const
{
    return {_top};
}
