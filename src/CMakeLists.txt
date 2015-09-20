# cmake_minimum_required(VERSION <specify CMake version here>)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    cexporter.cpp
    cexporter.hpp
    cframework.cpp
    cframework.hpp
    cimporter.cpp
    cimporter.hpp
    cmenu.hpp
    config.h
    csimulator.cpp
    csimulator.hpp
    cwindowmanager.cpp
    cwindowmanager.hpp
    defaultMenuDisplayer.hpp
    defaultTitleDisplayer.hpp
    gnu.cpp
    gnu.hpp
    main.cpp
    sfile.hpp
    sforce.hpp
    sparticle.hpp
    svec.cpp
    svec.hpp
    win32.cpp
    win32.hpp)

add_executable(src ${SOURCE_FILES})