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

#include "cframework.hpp"
#include "win32.hpp"

cframework::cframework()
{
}

cframework::~cframework()
{
}

bool cframework::init(int argc, char **argv)
{
    srand(time(0));
    
    m_mainMenu.setTitle("Main menu");
    m_mainMenu.addOption("Start simulation");
    m_mainMenu.addOption("Add particle");
    m_mainMenu.addOption("Add particles randomly");
    m_mainMenu.addOption("Remove particle");
    m_mainMenu.addOption("Remove all particles");
    m_mainMenu.addOption("Options");
    m_mainMenu.addOption("Load");
    m_mainMenu.addOption("Save");
    m_mainMenu.addOption("Exit");

    m_addParticleMenu.setTitle("Add particle");
    m_addParticleMenu.addOption("Set mass");
    m_addParticleMenu.addOption("Set position");
    m_addParticleMenu.addOption("Set velocity");
    m_addParticleMenu.addOption("Set name");
    m_addParticleMenu.addOption("Set radius");
    m_addParticleMenu.addOption("Accept");
    m_addParticleMenu.addOption("Discard");

    m_optionsMenu.setTitle("Options");
    m_optionsMenu.addOption("Set gravitational constant");
    m_optionsMenu.addOption("Set delta time");
    m_optionsMenu.addOption("Set scale");
    m_optionsMenu.addOption("Set collision checking");
    m_optionsMenu.addOption("Back");

    return interpretProgramArguments(argc, argv);
}

void cframework::run()
{
    mainSwitch();
}

void cframework::destroy()
{
}

void cframework::mainSwitch()
{
    bool cont = true;

    std::thread *sim = nullptr;
    std::thread *win = nullptr;
    
    while (cont)
    {
        switch (m_mainMenu.display())
        {
            case 0:
                if (m_simulator.init())
                {                
                    sim = new std::thread(&csimulator::start, &m_simulator);
                    win = new std::thread(std::bind(&cwindowmanager::start, &m_windowManager, 800, 600, m_simulator.getParticles()));
                }
                
                break;
            case 1:
                m_simulator.pause();
                addSwitch();
                m_simulator.unpause();
                break;
            case 2:
                m_simulator.pause();
                addRandomlyPrompt();
                m_simulator.unpause();
                break;
            case 3:
                m_simulator.pause();
                removeSwitch();
                m_simulator.unpause();
                break;
            case 4:
                m_simulator.pause();
                m_simulator.removeAllParticles();
                m_simulator.unpause();
                break;
            case 5:
                m_simulator.pause();
                optionsSwitch();
                m_simulator.unpause();
                break;
            case 6:
                importerPrompt();
                break;
            case 7:
                exporterPrompt();
                break;
            case 8:
                m_simulator.stop();
                m_windowManager.stop();

                if (sim && win)
                {
                    sim->join();
                    win->join();

                    delete sim;
                    delete win;
                }

                cont = false;
                break;
        }
    }
}

void cframework::addSwitch()
{
    bool cont = true;
    sparticle particle;
    
    while (cont)
    {
        switch (m_addParticleMenu.display())
        {
            case 0:
                particle.mass = getMass();
                m_addParticleMenu.editOption("Set mass (" + std::to_string(particle.mass) + " kg)", 0);
                break;
            case 1:
                particle.position = getPos();
                m_addParticleMenu.editOption("Set position (" + std::to_string(particle.position.x) + ", " + std::to_string(particle.position.y) + ", " + 
                    std::to_string(particle.position.z) + ")", 1);
                break;
            case 2:
                particle.velocity = getVel();
                break;
            case 3:
                particle.name = getName();
                break;
            case 4:
                particle.radius = getRadius();
                break;
            case 5:
                m_simulator.addParticle(particle);
                cont = false;
                break;
            case 6:
                cont = false;
                break;
        }
    }
}

void cframework::addRandomlyPrompt()
{
    bool error = true;
    sparticle particle;
    unsigned int amount;

    do
    {
        cls();
        std::cout << "\n Amount of particles to add: ";
        std::cin >> amount;

        error = false;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            error = true;
        }
    } while (error == true);

    for (unsigned int i = 0; i < amount; i++)
    {
        do
        {
            particle.mass = rand();
            particle.radius = rand();
            particle.position.x = rand();
            particle.position.y = rand();
            particle.position.z = rand();
            particle.velocity.x = 0;
            particle.velocity.y = 0;
            particle.velocity.z = 0;
            particle.name = std::to_string(rand());
        } while (!m_simulator.addParticle(particle));
    }
}

void cframework::scalePrompt()
{
    float esc;
    bool error;

    do
    {
        cls();
        std::cout << "\n Current scale = " << m_windowManager.getScale();
        std::cout << "\n New scale = ";
        std::cin >> esc;

        error = std::cin.fail();

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (error);

    m_windowManager.setScale(esc);
}

void cframework::removeSwitch()
{
    std::vector <sparticle> *part = m_simulator.getParticles();
    int option;

    m_removeParticleMenu.removeAllOptions();

    m_removeParticleMenu.setTitle("Remove particle");

    for (std::vector<sparticle>::iterator it = part->begin(); it != part->end(); ++it)    // Populate the menu
    {
        m_removeParticleMenu.addOption(it->name);
    }

    m_removeParticleMenu.addOption("Back");

    while ((option = m_removeParticleMenu.display()) != m_simulator.getParticleCount())  // display the menu, get the option, loop until selected option is "Back"
    {
        m_simulator.removeParticle(option);
        m_removeParticleMenu.removeOption(option);
    }
}

void cframework::optionsSwitch()
{
    bool cont = true;

    while (cont)
    {
        switch (m_optionsMenu.display())
        {
            case 0:
                gravityPrompt();
                break;
            case 1:
                deltaTimePrompt();
                break;
            case 2:
                scalePrompt();
                break;
            case 3:
                collisionPrompt();
                break;
            case 4:
                cont = false;
                break;
        }
    }
}

void cframework::importerPrompt()
{
    std::string filename;
    sfile file;

    std::cout << "\n File name: ";
    std::cin >> filename;

    if (m_importer.importFile(filename, &file))
    {
        m_simulator.addParticles(file.particles);
        m_simulator.setTimeStep(file.deltaTime);
        m_simulator.setGravitationalConstant(file.gravity);
        m_simulator.setCurrentTime(file.currTime);
        m_windowManager.setScale(file.scale);
    }
    else
    {
        std::cout << "\n The file is corrupt or it doesn't exist";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
    }
}

void cframework::exporterPrompt()
{
    std::string filename;
    std::string answer;
    sfile file;       

    bool error;
    bool write = true;
    
    std::cout << "\n File name: ";
    std::cin >> filename;

    if (m_exporter.checkForNameCollisions(filename))
    {
        do
        {
            cls();
            std::cout << "\n\n Name collision detected! "
                      << "Another file called " << filename << " already exists"
                      << "\n Do you want to overwrite that file? [Y/n]"
                      << "  Option: ";
            std::cin >> answer;

            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

            if (answer == "yes" || answer == "ye" || answer == "y")
            {
                error = false;
                write = true;
            }
            else if (answer == "no" || answer == "n")
            {
                write = false;
                error = false;
            }
            else
            {
                error = true;
            }
        } while (error == true);
    }

    if (write)
    {
        file.particles = *m_simulator.getParticles();
        file.gravity = m_simulator.getGravitationalConstant();
        file.deltaTime = m_simulator.getTimeStep();
        file.currTime = m_simulator.getCurrentTime();

        if (m_exporter.exportParticles(filename, file))
        {
            std::cout << "\n File exported successfully";
        }
        else
        {
            std::cout << "\n Couldn't export file";
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
    }
}

void cframework::gravityPrompt()
{
    double g;
    bool error;

    do
    {
        cls();
        std::cout << "\n Current G = " << m_simulator.getGravitationalConstant();
        std::cout << "\n New G = ";
        std::cin >> g;

        error = std::cin.fail();

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (error);
    
    m_simulator.setGravitationalConstant(g);
}

void cframework::deltaTimePrompt()
{
    double dt;
    bool error;

    do
    {
        cls();
        std::cout << "\n Current dt = " << m_simulator.getTimeStep();
        std::cout << "\n New dt = ";
        std::cin >> dt;

        error = std::cin.fail();

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (error);
    
    m_simulator.setTimeStep(dt);
}

void cframework::collisionPrompt()
{
    std::string answer;
    bool error, colli;

    do
    {
        cls();
        std::cout << "\n Collision detection will only work if particles have a radius";
        std::cout << "\n Collision detection is currently " << (m_simulator.getCollisionDetection() ? "ENABLED" : "DISABLED");
        std::cout << "\n Enable collision detection? [Y/n] ";
        std::cin >> answer;

        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer == "yes" || answer == "ye" || answer == "y")
        {
            error = false;
            colli = true;
        }
        else if (answer == "no" || answer == "n")
        {
            error = false;
            colli = false;
        }
        else
        {
            error = true;
        }
    } while (error);

    m_simulator.setCollisionDetection(colli);
}

bool cframework::interpretProgramArguments(int argc, char **argv)
{
    sfile file;
    
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);

        if (arg == "--version" || arg == "-v")
        {
            std::cout << "\nnewtonian gravity simulator version " << VERSION << std::endl;

            return false;
        }
        else if (arg == "--help" || arg == "-h")
        {
            std::cout << "newton [OPTIONS] [FILENAME]\n\n";
            std::cout << "OPTIONS:\n\n";
            std::cout << "--help  |  -h         Display this help\n";
            std::cout << "--version  |  -v      Display current version number\n";

            return false;
        }
        else
        {
            m_importer.importFile(arg, &file);

            m_simulator.addParticles(file.particles);
            m_simulator.setTimeStep(file.deltaTime);
            m_simulator.setGravitationalConstant(file.gravity);
            m_simulator.setCurrentTime(file.currTime);
        }
    }

    return true;
}            

double cframework::getMass()
{
    double mass;

    std::cout << "\n\n  Mass: ";
    std::cin >> mass;
    std::cin.clear();

    return mass;
}

double cframework::getRadius()
{
    double radius;

    std::cout << "\n\n  Radius: ";
    std::cin >> radius;
    std::cin.clear();

    return radius;
}

vec3 cframework::getPos()
{
    vec3 pos;

    std::cout << "\nx = ";
    std::cin >> pos.x;
    std::cin.clear();

    std::cout << "y = ";
    std::cin >> pos.y;
    std::cin.clear();

    std::cout << "z = ";
    std::cin >> pos.z;
    std::cin.clear();

    return pos;
}

vec3 cframework::getVel()
{
    return getPos();
}

std::string cframework::getName()
{
    std::string name;

    std::cout << "\n\n    Name: ";
    std::cin >> name;

    return name;
}

