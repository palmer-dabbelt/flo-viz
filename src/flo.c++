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

#include "flo.h++"

flo::flo(std::map<std::string, std::shared_ptr<node>>& nodes,
         std::vector<std::shared_ptr<operation>>& ops)
    : libflo::flo<node, operation>(nodes, ops)
{
}

const std::shared_ptr<flo> flo::parse(const std::string filename)
{
    auto func = libflo::flo<node, operation>::create_node;

    auto f = libflo::flo<node, operation>::parse_help<flo>(filename,
                                                           func);

    return f;
}
