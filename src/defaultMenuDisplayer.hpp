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

#ifndef DEFAULTMENUDISPLAYER_HPP_
#define DEFAULTMENUDISPLAYER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "win32.hpp"

#undef max

class defaultMenuDisplayer
{
public:

    unsigned int display(std::vector <std::string> &options)
    {
        unsigned int input, i;
    
        i = 1;

        for (std::vector<std::string>::iterator it = options.begin(); it != options.end(); ++it)
        {
            std::cout << i << "] " << *it << "\n";
            i++;
        }

        std::cout << "\n\t Option: ";
        std::cin >> input;
        input--;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return input;
    }
};

#endif
