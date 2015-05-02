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

#ifndef MODULE_HXX
#define MODULE_HXX

#include "drawable.h++"
#include "flo.h++"
#include <memory>
#include <vector>

/* The circuits we are trying to draw are arranged into modules, with
 * one of them being the top-level module.  All the cooresponding
 * elements of a Flo file are held at exactly one point within the
 * module hierarchy. */
class module: public drawable {
public:
    typedef std::shared_ptr<module> ptr;

private:
    /* This information is all defined by the circuit, and therefor
     * cannot change without changing the circuit topology, which will
     * require re-running this program. */
    const std::string _name;
    const std::vector<module::ptr> _child_modules;
    const std::vector<node::ptr> _child_nodes;
    const std::vector<operation::ptr> _child_ops;
    const std::vector<node::ptr> _ports;

    /* Information about how to draw the module, which will change
     * over the lifetime of the run. */
    
    
public:
    /* You probably don't want to call this as a user, it's really for
     * std::shared_ptr. */
    module(const std::string& name,
           const std::vector<module::ptr> child_modules,
           const std::vector<node::ptr> child_nodes,
           const std::vector<operation::ptr> child_ops,
           const std::vector<node::ptr> ports);

public:
    /* Parses a Flo file to produce a module hierarchy and returns a
     * pointer to the top-level module in that heirarchy. */
    static ptr parse(const flo::ptr& circuit);

public:
    /* drawable virtual methods */
    virtual void draw(const std::shared_ptr<sf::RenderWindow>& window);
};

#endif
