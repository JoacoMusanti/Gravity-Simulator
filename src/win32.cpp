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

#include "win32.hpp"

#ifdef _WIN32

void cls()
{
    HANDLE hOut;                            
    CONSOLE_SCREEN_BUFFER_INFO csbi;        
    DWORD dcount;                           
    DWORD cellCount;                        
    COORD home = {0, 0};                  

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo(hOut, &csbi))
    {
        return;
    }
    
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hOut, (TCHAR) ' ', cellCount,
                                   home, &dcount))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount,
                                   home, &dcount))
    {
        return;
    }
        
    SetConsoleCursorPosition(hOut, home);
}

void gotoxy(short x, short y)
{
    HANDLE hOut;
    COORD home = {x, y};

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut != INVALID_HANDLE_VALUE)
    {
        SetConsoleCursorPosition(hOut, home);
    }
}

#endif
