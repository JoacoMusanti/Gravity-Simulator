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

#ifndef CWINDOWMANAGER_HPP_
#define CWINDOWMANAGER_HPP_

#ifdef _WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include  "GLFW/glfw3.h"
#elif defined(__gnu_linux__)
#include <GL/glfw.h>
#endif


#include <vector>
#include "sparticle.hpp"

class cwindowmanager
{
public:

    cwindowmanager();
    ~cwindowmanager();

    bool start(GLsizei x, GLsizei y, std::vector <sparticle> *particles);
    void stop();

    void setScale(double scale);
    double getScale();
    
private:

    void run();
    bool createWindow(GLsizei x, GLsizei y);
    void render();
    void checkInput();

    bool m_render;
    bool m_first;

    double m_deltaRotation;
    double m_yRotationPrev;
    double m_yRotation;
    double m_deltaRotationX;
    double m_xRotationPrev;
    double m_xRotation;
    double m_scale;
    double m_zoom;
    double m_xShift;
    double m_yShift;
    double m_angle;
    double m_angleX;

    double m_mouseX;
    double m_mouseY;

    GLFWwindow *m_window;
    
    std::vector <sparticle> *m_particles;
};

#endif
