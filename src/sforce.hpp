// This file is part of newtonian gravity simulator.

// newtonian gravity simulator is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// newtonian gravity simulator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with newtonian gravity simulator.  If not, see <http://www.gnu.org/licenses/>.

// Copyright 2012, 2013 Joaquín Musanti

#ifndef SFORCE_HPP_
#define SFORCE_HPP_

// @sforce.hpp
// Description: This file is a header only file, it contains
// the declaration of a  structure  called  "sforce",  which
// represents a force with a direction and a magnitude, just
// like a vector. Each sparticle object (@sparticle.hpp)  will  have
// a std::vector of forces.

#include <vector>
#include "svec.hpp"

struct sforce
{
    vec3 direction;

    double magnitude;
};

#endif
