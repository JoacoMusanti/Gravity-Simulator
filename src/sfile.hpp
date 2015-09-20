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

#ifndef SFILE_HPP_
#define SFILE_HPP_

#include <vector>
#include "sparticle.hpp"

struct sfile
{
    std::vector <sparticle> particles;
    double gravity;
    double deltaTime;
    double currTime;
    double scale;
};
    
#endif
