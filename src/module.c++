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

#include "module.h++"
#include <SFML/Graphics/Text.hpp>

module::module(const std::string& name,
               const std::vector<module::ptr> child_modules,
               const std::vector<node::ptr> child_nodes,
               const std::vector<operation::ptr> child_ops,
               const std::vector<node::ptr> ports)
    : _name(name),
      _child_modules(child_modules),
      _child_nodes(child_nodes),
      _child_ops(child_ops),
      _ports(ports)
{
}

module::ptr module::parse(const flo::ptr& circuit __attribute__((unused)))
{
    return std::make_shared<module>("Test Module",
                                    std::vector<module::ptr>(),
                                    std::vector<node::ptr>(),
                                    std::vector<operation::ptr>(),
                                    std::vector<node::ptr>());
}

void module::draw(const std::shared_ptr<sf::RenderWindow>& window)
{
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/dejavu/DejaVuSansMono.ttf");
    
    sf::Text text;
    text.setFont(font);
    text.setString(_name);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Regular);

    window->draw(text);
}
