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

#include "cimporter.hpp"

cimporter::cimporter()
{
}

cimporter::~cimporter()
{
}

bool cimporter::importFile(std::string &filename, sfile *pfile)
{
    std::string line;

    bool correct = true;

    sparticle newParticle;

    if (!openFile(filename))
    {
        pfile->gravity = 0.0000000000667384;
        pfile->deltaTime = 60;
        pfile->currTime = 0;
        pfile->scale = 1e+009;
        return false;
    }

    // Start reading the simulation config
    // That resides in the header of the file (single line)
    std::getline(inFile, line);

    correct = correct && readGravConstant(&line, &(pfile->gravity));
        
    correct = correct && readTimeStep(&line, &(pfile->deltaTime));
        
    correct = correct && readCurrentTime(&line, &(pfile->currTime));

    if (!readScale(&line, &(pfile->scale)))
    {
        pfile->scale = 1e+009;
    }

    while (!inFile.eof() && correct)
    {
        // Read all the particle related stuff
        
        std::getline(inFile, line);

        correct = correct && readName(&line, &newParticle.name);

        correct = correct && readPosition(&line, &newParticle.position);

        correct = correct && readMass(&line, &newParticle.mass);

        correct = correct && readAcceleration(&line, &newParticle.acceleration);

        correct = correct && readVelocity(&line, &newParticle.velocity);

        if (correct)
        {
            pfile->particles.push_back(newParticle);
        }
    }

    closeFile();

    return correct;
}

bool cimporter::openFile(std::string &filename)
{
    inFile.open(filename.c_str());

    return inFile.is_open();
}

bool cimporter::readName(std::string *pline, std::string *pname)
{
    size_t pos = 0;

    std::string name;
    std::string key = "NAME=\"";

    bool status = false;

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) !=  '\"'; pos++)
        {
            name += pline->at(pos);
        }

        status = true;
        *pname = name;
    }
    else
    {
        status = false;
        pname = nullptr;
    }
        
    return status;
}

bool cimporter::readPosition(std::string *pline, vec3 *pposition)
{       
    size_t pos = 0;

    bool status = false;

    std::string x;
    std::string y;
    std::string z;
    std::string key = "POS=\"";

    std::stringstream ss;

    vec3 position;

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) != ' ' && pline->at(pos) != '\"'; pos++)
        {
            x += pline->at(pos);
        }

        pos++;
        
        for (; pline->at(pos) != ' ' && pline->at(pos) != '\"'; pos++)
        {
            y += pline->at(pos);
        }

        pos++;

        for (; pline->at(pos) !=  '\"'; pos++)
        {
            z += pline->at(pos);
        }

        ss.str(x);
        ss >> position.x;

        ss.clear();
        ss.str("");

        ss.str(y);
        ss >> position.y;

        ss.clear();
        ss.str("");

        ss.str(z);
        ss >> position.z;

        *pposition = position;
        status = true;
    }
    else
    {
        pposition = nullptr;
        status = false;
    }

    return status;
}
        
bool cimporter::readMass(std::string *pline, double *pmass)
{
    size_t pos = 0;

    bool status = false;

    std::string mass;
    std::string key = "MASS=\"";
    std::stringstream ss;

    double Mass = 0;

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) !=  '\"'; pos++)
        {
            mass += pline->at(pos);
        }

        ss.str(mass);
        ss >> Mass;

        status = true;
        *pmass = Mass;
    }
    else
    {
        status = false;
        pmass = nullptr;
    }
    
    return status;
}

bool cimporter::readTimeStep(std::string *pline, double *ptime)
{
    size_t pos = 0;

    bool status = false;

    std::string timeStep;
    std::string key = "TIMESTEP=\"";
    std::stringstream ss;

    double ts = 0;

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) !=  '\"'; pos++)
        {
            timeStep += pline->at(pos);
        }

        ss.str(timeStep);
        ss >> ts;

        status = true;
        *ptime = ts;
    }
    else
    {
        status = false;
        ptime = nullptr;
    }
 
    return status;
}

bool cimporter::readGravConstant(std::string *pline, double *pgrav)
{
    size_t pos = 0;

    bool status = false;

    std::string key = "GRAV=\"";
    std::string gravConstant;
    std::stringstream ss;

    double grav = 0;

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) != '\"'; pos++)
        {
            gravConstant += pline->at(pos);
        }
        
        ss.str(gravConstant);
        ss >> grav;

        status = true;
        *pgrav = grav;
    }
    else
    {
        status = false;
        pgrav = nullptr;
    }

    return status;
}

bool cimporter::readAcceleration(std::string *pline, vec3 *pacc)
{
    size_t pos = 0;

    bool status = false;

    std::string x;
    std::string y;
    std::string z;
    std::string key = "ACCEL=\"";

    std::stringstream ss;

    vec3 accel;

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) != ' ' && pline->at(pos) != '\"'; pos++)
        {
            x += pline->at(pos);
        }

        pos++;

        for (; pline->at(pos) != ' ' && pline->at(pos) != '\"'; pos++)
        {
            y += pline->at(pos);
        }

        pos++;

        for (; pline->at(pos) != '\"'; pos++)
        {
            z += pline->at(pos);
        }

        ss.str(x);
        ss >> accel.x;

        ss.clear();
        ss.str("");

        ss.str(y);
        ss >> accel.y;

        ss.clear();
        ss.str("");

        ss.str(z);
        ss >> accel.z;

        status = true;
        *pacc = accel;
    }
    else
    {
        status = false;
        pacc = nullptr;
    }
    
    return status;
}

bool cimporter::readVelocity(std::string *pline, vec3 *pvel)
{
    size_t pos = 0;

    bool status = false;

    std::string x;
    std::string y;
    std::string z;
    std::string key = "VEL=\"";

    std::stringstream ss;

    vec3 vel;

    if (pline == nullptr ||
        pvel == nullptr)
    {
        return false;
    }

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) != ' ' && pline->at(pos) != '\"'; pos++)
        {
            x += pline->at(pos);
        }

        pos++;

        for (; pline->at(pos) != ' ' && pline->at(pos) != '\"'; pos++)
        {
            y += pline->at(pos);
        }

        pos++;

        for (; pline->at(pos) != '\"'; pos++)
        {
            z += pline->at(pos);
        }

        ss.str(x);
        ss >> vel.x;

        ss.clear();
        ss.str("");

        ss.str(y);
        ss >> vel.y;

        ss.clear();
        ss.str("");

        ss.str(z);
        ss >> vel.z;

        status = true;
        *pvel = vel;
    }
    else
    {
        status = false;
        pvel = nullptr;
    }

    return status;
}

bool cimporter::readCurrentTime(std::string *pline, double *pcurrTime)
{
    size_t pos = 0;

    bool status = false;

    std::string time;
    std::string key = "TIME=\"";

    std::stringstream ss;

    double currentTime = 0;

    if (pline == nullptr ||
        pcurrTime == nullptr)
    {
        return false;
    }

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) != '\"'; pos++)
        {
            time += pline->at(pos);
        }

        ss.str(time);
        ss >> currentTime;

        status = true;
        *pcurrTime = currentTime;
    }
    else
    {
        status = false;
        pcurrTime = nullptr;
    }
    
    return status;
}

bool cimporter::readScale(std::string *pline, double *pscale)
{
    size_t pos = 0;

    bool status = false;

    std::string scale;
    std::string key = "SCALE=\"";

    std::stringstream ss;

    double scal = 0;

    if (pline == nullptr ||
        pscale == nullptr)
    {
        return false;
    }

    pos = search(key, pline);
    if (pos != std::string::npos && isLineValid(pline))
    {
        for (; pline->at(pos) != '\"'; pos++)
        {
            scale += pline->at(pos);
        }

        ss.str(scale);
        ss >> scal;

        status = true;
        *pscale = scal;
    }
    else
    {
        status = false;
        pscale = nullptr;
    }

    return status;
}

bool cimporter::isLineValid(std::string *pline)
{
    unsigned int commaCount = countInvertedCommas(pline);

    return ((commaCount % 2 == 0) && checkCommaPositions(pline));
}

bool cimporter::checkCommaPositions(std::string *pline)
{
    std::vector <std::string> keys;

    keys.push_back("NAME=\"");
    keys.push_back("VEL=\"");
    keys.push_back("ACCEL=\"");
    keys.push_back("TIME=\"");
    keys.push_back("TIMESTEP=\"");
    keys.push_back("GRAV=\"");
    keys.push_back("POS=\"");
    keys.push_back("MASS=\"");

    bool correct = true;
    unsigned int pos = 0;
    unsigned int in = 0;                      // awdaw"adwdawee"xxxxx
    unsigned int out = 0;                     //      ^        ^
                                              //      in       out
    
    for (unsigned int i = 0; i < pline->size(); i++)
    {
        if (pline->at(i) == '\"')
        {
            if (in <= out)
            {
                in = i;
            }
            else
            {
                out = i;

                for (unsigned int j = 0; j < keys.size(); j++)
                {
                    pos = pline->find(keys[j]);

                    if (pos < out && pos > in)
                    {
                        correct = correct && false;
                    }
                }
            }
        }
    }

    return correct;
}

size_t cimporter::countInvertedCommas(std::string *pline)
{
    size_t count = 0;
    
    for (unsigned int i = 0; i < pline->size(); i++)
    {
        if (pline->at(i) == '\"')
        {
            count++;
        }
    }

    return count;
}

void cimporter::closeFile()
{
    inFile.close();
}

size_t cimporter::search(std::string key, std::string *psource)
{
    // This method searches for a key in source, if it finds it, it moves
    // the position forward key.size() characters
    size_t pos = std::string::npos;
    
    if (psource != nullptr)
    {
        pos = psource->find(key);
    }
      
    if (pos != std::string::npos)
    {
        pos += key.size();
    }
 
    return pos;
}
