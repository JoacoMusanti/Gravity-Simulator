// This file is part of newtonian gravity simulator.

// newtonian gravity simulator is free software: you can redistribute
// it and/or modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.

// newtonian gravity simulator is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with newtonian gravity simulator.  If not, see
// <http://www.gnu.org/licenses/>.

// Copyright 2012, 2013 Joaquín Musanti

#include "cwindowmanager.hpp"

std::vector <sparticle> *pToDraw;
double max;

cwindowmanager::cwindowmanager()
{
    m_zoom = 0;
    m_xShift = 0;
    m_yShift = 0;
    m_first = true;
    m_yRotation = 0;
    m_yRotationPrev = 0;
    m_angle = 0;
    m_angleX = 0;
    m_xRotation = 0;
    m_xRotationPrev = 0;
    m_scale = 1000;
}

cwindowmanager::~cwindowmanager()
{
}

bool cwindowmanager::start(GLsizei gl_x, GLsizei gl_y, std::vector <sparticle> *particles)
{
    m_render = false;

    if (glfwInit() == GL_FALSE)
    {
        return false;
    }

    if (!createWindow(gl_x, gl_y))
    {
        return false;
    }

    m_particles = particles;

    m_render = true;

    run();

    return true;
}

bool cwindowmanager::createWindow(GLsizei x, GLsizei y)
{
    m_window = glfwCreateWindow(x, y, "Simulation", nullptr, nullptr);
    if (m_window == nullptr)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, 1.0, 10.0, 1000000000.0);
    glMatrixMode(GL_MODELVIEW);

    return true;
}

void cwindowmanager::run()
{
    while (m_render)
    {
        render();
        glfwPollEvents();
        checkInput();
    }

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void cwindowmanager::stop()
{
    m_render = false;
}

void cwindowmanager::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(m_xShift, m_yShift, m_zoom);

    glRotatef(m_angle + m_deltaRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(m_angleX + m_deltaRotationX, 0.0f, 0.0f, 1.0f);

    glColor3f(1, 1, 1);

    for (std::vector <sparticle>::iterator it = m_particles->begin(); it != m_particles->end(); ++it)
    {
        glBegin(GL_POINTS);

        glVertex3f(static_cast<float>(it->position.x),
                   static_cast<float>(it->position.z),
                   static_cast<float>(it->position.y));

        glEnd();
    }

    glPopMatrix();
    glfwSwapBuffers(m_window);
    glFlush();
}

void cwindowmanager::checkInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_UP))
    {
        m_yShift -= m_scale;
    }
    if (glfwGetKey(m_window, GLFW_KEY_DOWN))
    {
        m_yShift += m_scale;
    }
    if (glfwGetKey(m_window, GLFW_KEY_LEFT))
    {
        m_xShift += m_scale;
    }
    if (glfwGetKey(m_window, GLFW_KEY_RIGHT))
    {
        m_xShift -= m_scale;
    }
    if (glfwGetKey(m_window, 'Z'))
    {
        m_zoom -= m_scale;
    }
    if (glfwGetKey(m_window, 'A'))
    {
        m_zoom += m_scale;
    }
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT))
    {
        m_angle = 0;
        m_angleX = 0;
        m_deltaRotation = 0;
        m_deltaRotationX = 0;
    }
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT))
    {
        glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);
        if (m_first == true)
        {
            m_xRotation = m_mouseX;
            m_xRotationPrev = m_mouseX;
            m_yRotation = m_mouseY;
            m_yRotationPrev = m_mouseY;
            m_first = false;
            m_deltaRotation = m_angle;
            m_deltaRotationX = m_angleX;
        }
        else
        {
            m_yRotation = m_mouseY;
            m_deltaRotation = m_yRotation - m_yRotationPrev;

            m_xRotation = m_mouseX;
            m_deltaRotationX = m_xRotation - m_xRotationPrev;
        }
    }
    else
    {
        if (!m_first)
        {
            m_angleX += m_deltaRotationX;
            m_angle += m_deltaRotation;
            m_deltaRotation = 0;
            m_deltaRotationX = 0;
        }

        m_first = true;
    }
    // Is window open?
    if (glfwWindowShouldClose(m_window))
    {
        stop();
    }
}

void cwindowmanager::setScale(double scale)
{
    m_scale = scale;
}

double cwindowmanager::getScale()
{
    return m_scale;
}
