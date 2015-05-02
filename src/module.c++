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
#include <deque>
#include <unordered_map>
#include <iostream>
#include <SFML/Graphics/Text.hpp>

/* Returns TRUE if all the operands of this operation are in the same
 * module, and FALSE otherwise.  This just looks at the names and does
 * some string comparisons, which is really necessary to seed the real
 * lookup tables. */
static bool all_same_module_prefix(const operation::ptr& op);
static bool all_same_module_prefix(const std::vector<node::ptr>& nodes);

/* Returns the module prefix name of the given node, or searches all
 * the nodes until one with a prefix is found. */
static std::string find_prefix(const std::string& name);
static std::string find_prefix(const std::vector<node::ptr>& nodes);

/* Counts the number of levels deep in the hierarchy this module name
 * is. */
static size_t count_module_depth(const std::string& name);

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

module::ptr module::parse(const flo::ptr& circuit)
{
    /* The goal here is to build up a mapping of module names (which
     * are strings) to all the operations contained within that
     * module. */
    auto modulenames = std::vector<std::string>();
    auto modulename2ops = std::multimap<std::string, operation::ptr>();
    auto op2modulename = std::unordered_map<operation::ptr, std::string>();
    auto node2modulename = std::unordered_map<node::ptr, std::string>();

    auto insert_op = [&](const operation::ptr& op, std::string m) -> void
        {
            if (modulename2ops.find(m) == modulename2ops.end())
                modulenames.push_back(m);
            modulename2ops.insert(std::make_pair(m, op));
            op2modulename[op] = m;
            for (const auto& node: op->operands())
                node2modulename[node] = m;
        };

    auto all_same_module = [&](const operation::ptr& op) -> std::string
        {
            auto has_module = false;
            std::string module = "";

            for (const auto& node: op->operands()) {
                if (node->is_const() == true)
                    continue;

                auto l = node2modulename.find(node);
                if (l == node2modulename.end())
                    continue;
                auto m = l->second;

                if (has_module == false) {
                    has_module = true;
                    module = m;
                }

                if (m.compare(module) != 0)
                    return "";
            }

            return has_module ? module : "";
        };

    /* This is just a big, brute-force approach to trying to determine
     * the modules that each node belongs to. */
    auto remaining_ops = [&]() -> std::deque<operation::ptr> {
        auto ops = circuit->operations();
        return std::deque<operation::ptr>(ops.begin(), ops.end());
    }();
    size_t iterations_since_doing_something = 0;
    while (remaining_ops.size() > 0) {
        auto op = remaining_ops.front();
        remaining_ops.pop_front();

        /* First check to see if every node in this operation is an
         * actual member of the same module, in which case this is
         * easy: this whole operation lives inside the given module,
         * so just stick it in there. */
        if (all_same_module_prefix(op)) {
            insert_op(op, find_prefix(op->operands()));
            iterations_since_doing_something = 0;
            continue;
        }

        /*  */
        auto found_module = all_same_module(op);
        if (found_module.compare("") != 0) {
            insert_op(op, found_module);
            iterations_since_doing_something = 0;
            continue;
        }

        /* I don't know how to deal with this particular sort of
         * operation, so just put it back on the queue and hope it
         * comes around again. */
        remaining_ops.push_back(op);
        iterations_since_doing_something++;
        if (iterations_since_doing_something > remaining_ops.size())
            break;
    }

    /* Check to see if there are any remaining ops to process, which
     * means we were unable to display the whole circuit and should
     * bail out now. */
    if (remaining_ops.size() > 0) {
        std::cerr << "Unable to assign some nodes to a module:\n";
        for (const auto& op: remaining_ops)
            std::cerr << "  " << op->to_string() << "\n";
        abort();
    }

    /* There is a tree of modules, so if we construct it starting at
     * the leaves then there's no need to build non-const modules. */
    std::sort(modulenames.begin(), modulenames.end(),
              [](const std::string a, const std::string b) -> int
              {
                  return count_module_depth(b) - count_module_depth(a);
              });

    auto modulename2children = std::multimap<std::string, module::ptr>();
    for (const auto& module_name: modulenames) {
        auto child_modules = std::vector<module::ptr>();
        auto child_nodes = std::vector<node::ptr>();
        auto child_ops = std::vector<operation::ptr>();
        auto ports = std::vector<node::ptr>();
        auto m = std::make_shared<module>(module_name,
                                          child_modules,
                                          child_nodes,
                                          child_ops,
                                          ports);

        auto parent_name = find_prefix(module_name);
        if (parent_name.compare("") == 0)
            return m;
        modulename2children.insert(std::make_pair(parent_name, m));
    }

    return nullptr;
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

bool all_same_module_prefix(const operation::ptr& op)
{
    return all_same_module_prefix(op->operands());
}

bool all_same_module_prefix(const std::vector<node::ptr>& nodes)
{
    auto has_prefix = false;
    auto prefix = std::string("");

    for (const auto& node: nodes) {
        if (node->is_const() == true)
            continue;

        /* FIXME: This shouldn't be a straight-up string compare, but
         * should instead actually check if this is a reset. */
        if (node->name().compare("reset") == 0)
            continue;

        if (find_prefix(node->name()).compare("") == 0)
            continue;

        if (has_prefix == false) {
            has_prefix = true;
            prefix = find_prefix(node->name());
        }

        if (find_prefix(node->name()).compare(prefix) != 0)
            return false;
    }

    return has_prefix;
}

std::string find_prefix(const std::string& name)
{
    auto last = name.find_last_of(":");
    if (last == std::string::npos)
        return "";

    if (name[last - 1] == ':')
        return std::string(name, 0, last - 1);

    return std::string(name, 0, last);
}

std::string find_prefix(const std::vector<node::ptr>& nodes)
{
    for (const auto& node: nodes) {
        if (find_prefix(node->name()) == "")
            continue;

        return find_prefix(node->name());
    }

    return "";
}

size_t count_module_depth(const std::string& name)
{
    size_t count = 0;
    for (size_t i = 1; i < name.size(); ++i)
        if (name[i] == ':' && name[i-1] != ':')
            count++;
    return count + 1;
}
