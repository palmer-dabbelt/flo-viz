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

#ifndef RENDER_HXX
#define RENDER_HXX

#include "drawable.h++"
#include "flo.h++"
#include "module.h++"
#include <memory>

/* Deals with rendering the scene.  There will be a single instance of
 * this class, which holds all the state that can be modified by the
 * user -- everything that's drawable, for example. */
class render {
public:
    typedef std::shared_ptr<render> ptr;

private:
    /* Holds every node in the circuit, just to be sure none of them
     * ever go away. */
    flo::ptr _circuit;

    /* In order to convert our virtual coordinates into pixels, it's
     * necessary to know how many pixels there are and how big the
     * pixels are. */
    int _width;
    int _height;
    float _dpi;

    /* The top-level module, which is what is used when actually
     * drawing to the screen. */
    module::ptr _top;

public:
    /* Constructs a new rendering engine, given the circuit that it
     * will render. */
    render(const flo::ptr& circuit, int width, int height, float dpi);

public:
    /* Changes the size of the window. */
    void resize(int new_width, int new_height, float new_dpi);

    /* Returns a list of every drawable object that's currently
     * visible. */
    std::vector<drawable::ptr> all_visible(void) const;
};

#endif
