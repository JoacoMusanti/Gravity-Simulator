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

#ifndef CSIMULATOR_HPP_
#define CSIMULATOR_HPP_

#include <vector>
#include <string>
#include <cmath>
#include <mutex>
#include <condition_variable>


#include "sparticle.hpp"
#include "sforce.hpp"
#include "svec.hpp"


class csimulator
{
public:
	
    csimulator();
    ~csimulator();

    bool init();
    void start();
    void pause();
    void unpause();
    void stop();
	
    bool addParticle(sparticle &particle);
    bool addParticles(std::vector <sparticle> &particles);
    bool removeParticle(unsigned int index);
    void removeAllParticles();
	
    void setGravitationalConstant(double grav);
    double getGravitationalConstant();

    void setTimeStep(double dT);
    double getTimeStep();

    void setCurrentTime(double currentTime);
    double getCurrentTime();

    void setCollisionDetection(bool col);
    bool getCollisionDetection();
	
    unsigned int getParticleCount();

    std::vector<sparticle> *getParticles();
    bool getParticle(unsigned int index, sparticle *pparticle);

private:

    bool isParticleValid(sparticle &particle);
    bool initParticles();

    void checkCollisions();
    void simulateWithCollisions();
    void simulateWithoutCollisions();
    void processParticle(unsigned int which);
    void calculateForceVectors();
    void calculateAcceleration(unsigned int index);
    void calculateVelocity(unsigned int index);
    void calculateParticleMovement(unsigned int index);
    double calculateParticleMovementX(unsigned int index);
    double calculateParticleMovementY(unsigned int index);
    double calculateParticleMovementZ(unsigned int index);

    bool m_stopped;
    bool m_paused;
    bool m_resourcesAreBlocked;
    bool m_collisionDetection;

    double m_gravity;
    double m_timeStep;
    double m_currentTime;

    std::vector <sparticle> m_particles;
};

#endif
