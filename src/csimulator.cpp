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

#include "csimulator.hpp"

csimulator::csimulator()
{
    m_gravity = 0.0000000000667384;
    m_timeStep = 60;
    m_currentTime = 0;

    m_resourcesAreBlocked = false;
    m_paused = true;
    m_stopped = true;
    m_collisionDetection = false;
}

csimulator::~csimulator()
{
}

bool csimulator::init()
{
    return initParticles();
}

void csimulator::start()
{
    if (m_collisionDetection)
    {
        simulateWithCollisions();
    }
    else
    {
        simulateWithoutCollisions();
    }
}

void csimulator::pause()
{
    m_paused = true;
}

void csimulator::unpause()
{
    m_paused = false;
}

void csimulator::stop()
{
    m_paused = true;
    m_stopped = true;
}

bool csimulator::addParticle(sparticle &particle)
{
    if (!m_resourcesAreBlocked)
    {
        if (isParticleValid(particle))
        {
            m_particles.push_back(particle);

            return true;
        }
    }

    return false;
}

bool csimulator::addParticles(std::vector <sparticle> &particles)
{
    bool ret = true;

    for (std::vector <sparticle>::iterator it = particles.begin(); it != particles.end(); ++it)
    {
        ret = addParticle(*it) && ret;
    }

    return ret;
}

bool csimulator::removeParticle(unsigned int index)
{
    if (!m_resourcesAreBlocked)
    {
        if (index < m_particles.size())
        {
            m_particles.erase(m_particles.begin() + index);
            return true;
        }
    }
    
    return false;
}

void csimulator::removeAllParticles()
{
    while (m_resourcesAreBlocked);
    if (!m_resourcesAreBlocked)
    {
        m_particles.resize(0);
    }
}

void csimulator::setGravitationalConstant(double grav)
{
    if (!m_resourcesAreBlocked)
    {
        m_gravity = grav;
    }
}

double csimulator::getGravitationalConstant()
{
    return m_gravity;
}

void csimulator::setTimeStep(double dT)
{
    if (!m_resourcesAreBlocked)
    {
        m_timeStep = dT;
    }
}

double csimulator::getTimeStep()
{
    return m_timeStep;
}

void csimulator::setCurrentTime(double currentTime)
{
    if (!m_resourcesAreBlocked)
    {
        m_currentTime = currentTime;
    }
}

double csimulator::getCurrentTime()
{
    return m_currentTime;
}

void csimulator::setCollisionDetection(bool col)
{
    if (!m_resourcesAreBlocked)
    {
        m_collisionDetection = col;
    }
}

bool csimulator::getCollisionDetection()
{
    return m_collisionDetection;
}

unsigned int csimulator::getParticleCount()
{
    return m_particles.size();
}

std::vector<sparticle> *csimulator::getParticles()
{
    return &m_particles;
}

bool csimulator::getParticle(unsigned int index, sparticle *pparticle)
{
    bool ret = false;

    if (pparticle)
    {
        if (index < m_particles.size())
        {
            ret = true;
            *pparticle = m_particles[index];
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

bool csimulator::isParticleValid(sparticle &particle)
{
    // For the particle to be allowed to enter the scene, the following conditions must be met
    // The particle must have a name longer than 0 characters
    // The particle must have positive rest mass
    // The particle must not share the position with any other object

    if (particle.name.size() == 0)
    {
        return false;
    }

    if (particle.mass <= 0)
    {
        return false;
    }

    for (std::vector<sparticle>::iterator it = m_particles.begin(); it != m_particles.end(); ++it)
    {
   /*     if (particle.name == it->name)
        {
            return false;
        }*/

        if (particle.position.x == it->position.x &&
            particle.position.y == it->position.y &&
            particle.position.z == it->position.z)
        {
            return false;
        }
    }

    return true;
}

void csimulator::checkCollisions()
{
    std::vector<int> markedForDeletion;
    double distance, radiusSum;

    for (unsigned int i = 0; i < m_particles.size() - 1; ++i)
    {
        for (unsigned int j = i + 1; j < m_particles.size(); ++j)
        {
            distance = (std::pow((m_particles[j].position.x - m_particles[i].position.x), 2) +
                std::pow((m_particles[j].position.y - m_particles[i].position.y), 2) +
                std::pow((m_particles[j].position.z - m_particles[i].position.z), 2));

            radiusSum = m_particles[i].radius + m_particles[j].radius;

            if (distance < radiusSum)
            {
                if (m_particles[i].mass >= m_particles[j].mass)
                {
                    m_particles[i].mass += m_particles[j].mass;
                    m_particles[i].radius += m_particles[j].radius;
                    m_particles[i].velocity.x += m_particles[j].velocity.x;
                    m_particles[i].velocity.y += m_particles[j].velocity.y;
                    m_particles[i].velocity.z += m_particles[j].velocity.z;
                    
                    markedForDeletion.push_back(j);
                }
                else
                {
                    m_particles[j].mass += m_particles[i].mass;
                    m_particles[j].radius += m_particles[i].radius;
                    m_particles[j].velocity.x += m_particles[i].velocity.x;
                    m_particles[j].velocity.y += m_particles[i].velocity.y;
                    m_particles[j].velocity.z += m_particles[i].velocity.z;

                    markedForDeletion.push_back(i);
                }
            }
        }
    }

    for (unsigned int k = markedForDeletion.size(); k > 0; k--)
    {
        m_particles.erase(m_particles.begin() + markedForDeletion[k - 1]);
    }
}

bool csimulator::initParticles()
{
    if (m_particles.size() == 0)
    {
        m_stopped = true;

        return false;
    }

    if (m_stopped == false)
    {
        return false;
    }

    m_stopped = false;

    return true;
}

void csimulator::simulateWithoutCollisions()
{
    while (!m_stopped)
    {
        while (!m_paused)
        {
            m_resourcesAreBlocked = true;
            
            m_currentTime += m_timeStep;

            calculateForceVectors();

            for (unsigned int i = 0; i < m_particles.size(); i++)
            {
                calculateParticleMovement(i);
            }

            m_resourcesAreBlocked = false;
        }
    }
}

void csimulator::simulateWithCollisions()
{
    while (!m_stopped)
    {
        while (!m_paused)
        {
            m_resourcesAreBlocked = true;

            m_currentTime += m_timeStep;

            calculateForceVectors();

            for (unsigned int i = 0; i < m_particles.size(); i++)
            {
                calculateParticleMovement(i);
            }

            checkCollisions();

            m_resourcesAreBlocked = false;
        }
    }
}

void csimulator::calculateForceVectors()
{
    double distance;
    double force;

    vec3 resultantForce;

    for (unsigned int j = 0; j < m_particles.size(); j++)
    {
        resultantForce.x = 0;
        resultantForce.y = 0;
        resultantForce.z = 0;

        for (unsigned int i = 0; i < m_particles.size(); i++)
        {
            if (i != j)
            {
                distance = (std::pow((m_particles[j].position.x - m_particles[i].position.x), 2) +
                    std::pow((m_particles[j].position.y - m_particles[i].position.y), 2) +
                    std::pow((m_particles[j].position.z - m_particles[i].position.z), 2));

                force = m_gravity * m_particles[j].mass * m_particles[i].mass;

                distance = std::sqrt(distance);

                resultantForce.x += (m_particles[i].position.x - m_particles[j].position.x) * force / (distance * distance * distance);
                resultantForce.y += (m_particles[i].position.y - m_particles[j].position.y) * force / (distance * distance * distance);
                resultantForce.z += (m_particles[i].position.z - m_particles[j].position.z) * force / (distance * distance * distance);
            }
        }

        m_particles[j].resultant = resultantForce;
        calculateAcceleration(j);
        calculateVelocity(j);
    }
    
}

void csimulator::calculateAcceleration(unsigned int index)
{
    vec3 force = m_particles[index].resultant;
    vec3 acceleration;

    double mass = m_particles[index].mass;

    acceleration.x = force.x / mass;
    acceleration.y = force.y / mass;
    acceleration.z = force.z / mass;

    m_particles[index].acceleration = acceleration;
}

void csimulator::calculateVelocity(unsigned int index)
{
    vec3 velocity = m_particles[index].velocity;
    vec3 acceleration = m_particles[index].acceleration;

    velocity.x = velocity.x + acceleration.x * m_timeStep;
    velocity.y = velocity.y + acceleration.y * m_timeStep;
    velocity.z = velocity.z + acceleration.z * m_timeStep;

    m_particles[index].velocity = velocity;
}

void csimulator::calculateParticleMovement(unsigned int index)
{
    vec3 movement;

    movement.x = calculateParticleMovementX(index);
    movement.y = calculateParticleMovementY(index);
    movement.z = calculateParticleMovementZ(index);

    m_particles[index].position.x += movement.x;
    m_particles[index].position.y += movement.y;
    m_particles[index].position.z += movement.z;
}

double csimulator::calculateParticleMovementX(unsigned int index)
{
    double space;

    double velocity = m_particles[index].velocity.x;
    double acceleration = m_particles[index].acceleration.x;

    space = velocity * m_timeStep + 0.5 * acceleration * m_timeStep * m_timeStep;

    return space;
}

double csimulator::calculateParticleMovementY(unsigned int index)
{
    double space;

    double velocity = m_particles[index].velocity.y;
    double acceleration = m_particles[index].acceleration.y;

    space = velocity * m_timeStep + 0.5 * acceleration * m_timeStep * m_timeStep;

    return space;
}

double csimulator::calculateParticleMovementZ(unsigned int index)
{
    double space;

    double velocity = m_particles[index].velocity.z;
    double acceleration = m_particles[index].acceleration.z;

    space = velocity * m_timeStep + 0.5 * acceleration * m_timeStep * m_timeStep;

    return space;
}
