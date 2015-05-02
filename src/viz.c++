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
#include "render.h++"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc __attribute__((unused)),
         const char **argv __attribute__((unused)))
{
    /* The main output window, which is simply rendered in a loop
     * until the user attempts to quit. */
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600),
                                                     "flo-viz",
                                                     sf::Style::Default);

    /* This prevents the rendering part from just blowing through the
     * entire CPU doing nothing interesting. */
    window->setFramerateLimit(120);

    /* The main rendering code, which deals with */
    auto world = std::make_shared<render>(flo::parse("test.flo"),
                                          800, 600, 200);

    /* Initializes the keyboard handling functions. */
    auto key_handlers = std::make_shared<keys>();
    key_handlers->insert(sf::Keyboard::Key::Escape,
                         "quit",
                         [](){},
                         [&](){window->close();});
    key_handlers->insert(sf::Keyboard::Key::H,
                         "prints help to stdout",
                         [&](){key_handlers->print_help_text();},
                         [](){});
    key_handlers->print_help_text();
    
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::Resized:
                /* FIXME: The DPI is hard-coded here and above, that
                 * should be fixed. */
                world->resize(event.size.width,
                              event.size.height,
                              200);

                window->setView(
                    sf::View(
                        sf::FloatRect(
                            0.0f,
                            0.0f,
                            world->window_width(),
                            world->window_height()
                            )
                        )
                    );
                break;

            case sf::Event::KeyPressed:
                key_handlers->press(event.key.code);
                break;
            case sf::Event::KeyReleased:
                key_handlers->release(event.key.code);
                break;

            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            case sf::Event::TextEntered:
            case sf::Event::MouseWheelMoved:
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            case sf::Event::MouseMoved:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
            case sf::Event::JoystickConnected:
            case sf::Event::JoystickDisconnected:
            case sf::Event::Count:
                break;

            default:
                std::cerr << "Unhandled event type: " << event.type << "\n" << std::flush;
                abort();
            }
        }

        window->clear(sf::Color::White);

        for (const auto& d: world->all_visible())
            d->draw(window);

        window->display();
    }

    return 0;
}
