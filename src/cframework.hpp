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

#ifndef CFRAMEWORK_HPP_
#define CFRAMEWORK_HPP_

#include <string>
#include <thread>
#include "cmenu.hpp"
#include "csimulator.hpp"
#include "cwindowmanager.hpp"
#include "cimporter.hpp"
#include "cexporter.hpp"
#include "defaultMenuDisplayer.hpp"
#include "defaultTitleDisplayer.hpp"
#include "sfile.hpp"
#include "config.h"

#undef max

class cframework
{
    typedef cmenu<defaultTitleDisplayer, defaultMenuDisplayer> normalMenu;

public:

    cframework();
    ~cframework();

    bool init(int argc, char **argv);
    void run();
    void destroy();

private:

    void mainSwitch();
    void addSwitch();
    void addRandomlyPrompt();
    void removeSwitch();
    void scalePrompt();
    void optionsSwitch();
    void importerPrompt();
    void exporterPrompt();
    void gravityPrompt();
    void deltaTimePrompt();
    void collisionPrompt();
    bool interpretProgramArguments(int argc, char **argv);

    double getMass();
    double getRadius();
    vec3 getPos();
    vec3 getVel();
    std::string getName();

    normalMenu m_mainMenu;
    normalMenu m_addParticleMenu;
    normalMenu m_addParticleRandomlyMenu;
    normalMenu m_removeParticleMenu;
    normalMenu m_optionsMenu;

    cimporter m_importer;
    cexporter m_exporter;
    csimulator m_simulator;
    cwindowmanager m_windowManager;
};    

#endif
