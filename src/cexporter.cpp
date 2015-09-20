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

#include "cexporter.hpp"

cexporter::cexporter()
{
}

cexporter::~cexporter()
{
}

bool cexporter::exportParticles(std::string &filename, sfile &file)
{
    std::string answer;

    if (openFile(filename))
    {
        writeToFile(file);
        closeFile();
        return true;
    }
    
    return false;
}

bool cexporter::checkForNameCollisions(std::string &filename)
{
    std::ifstream inFile;

    bool ret = false;

    inFile.open(filename.c_str());

    if (inFile.is_open())
    {
        inFile.close();
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool cexporter::openFile(std::string &filename)
{
    outFile.open(filename.c_str(), std::ios::trunc);

    return outFile.is_open();
}

void cexporter::writeToFile(sfile &file)
{
    sparticle particle;

    outFile << "TIME=\"" << file.currTime << "\""
            << " TIMESTEP=\"" << file.deltaTime << "\""
            << " GRAV=\"" << file.gravity
            << "\"";

    for (std::vector <sparticle>::iterator it = file.particles.begin(); it != file.particles.end(); ++it)
    {
        outFile << "\nNAME=\"" << it->name << "\" "
                << "MASS=\"" << it->mass << "\" "
                << "POS=\""
                << it->position.x << " "
                << it->position.y << " "
                << it->position.z << "\" "
                << "ACCEL=\""
                << it->acceleration.x << " "
                << it->acceleration.y << " "
                << it->acceleration.z << "\" "
                << "VEL=\""
                << it->velocity.x << " "
                << it->velocity.y << " "
                << it->velocity.z << "\"";
    }
}

void cexporter::closeFile()
{
    outFile.close();
}
