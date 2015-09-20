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

#ifndef CIMPORTER_HPP_
#define CIMPORTER_HPP_

#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "csimulator.hpp"
#include "sparticle.hpp"
#include "svec.hpp"
#include "sfile.hpp"

class cimporter
{
public:

    cimporter();
    ~cimporter();

    bool importFile(std::string &filename, sfile *pfile);

private:

    bool openFile(std::string &filename);
    bool readName(std::string *pline, std::string *pname);
    bool readPosition(std::string *pline, vec3 *pposition);
    bool readMass(std::string *pline, double *pmass);
    bool readTimeStep(std::string *pline, double *ptime);
    bool readGravConstant(std::string *pline, double *pgrav);
    bool readAcceleration(std::string *pline, vec3 *pacc);
    bool readVelocity(std::string *pline, vec3 *pvel);
    bool readCurrentTime(std::string *pline, double *pcurrTime);
    bool readScale(std::string *pline, double *pscale);
    bool isLineValid(std::string *pline);
    bool checkCommaPositions(std::string *pline);
    size_t countInvertedCommas(std::string *pline);
    size_t search(std::string key, std::string *psource);
    void closeFile();

    std::ifstream inFile;
};

#endif
