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

#ifndef CMENU_HPP_
#define CMENU_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <limits>

template <typename titleDisplayerPolicy, typename menuDisplayerPolicy>
class cmenu
{
public:

    unsigned int getOptionCount()			
    {
        return m_Options.size();
    }

    void setTitle(std::string &Title)
    {				
        m_Title = Title;
    }

    void setTitle(const char option[])
    {
        std::string title(option);

        setTitle(title);
    }

    void addOption(std::string &Option)
    {
        m_Options.push_back(Option);
    }

    void addOption(const char option[])
    {
        std::string opt(option);

        addOption(opt);
    }

    void addOptions(std::vector <std::string> &Options)
    {
        m_Options.insert(m_Options.end(), Options.begin(), Options.end());
    }

    void editOption(std::string &Option, unsigned int index)	
    {								
        if (index < m_Options.size())
        {
            m_Options[index] = Option;
        }

        return;
    }

    void editOption(const char opt[], unsigned int index)
    {
        std::string option(opt);

        editOption(option, index);
    }

    void removeOption(unsigned int index)			
    {
        if (index < m_Options.size())
        {
            m_Options.erase(m_Options.begin() + index);
        }
 
        return;
    }

    void removeAllOptions()
    {
        m_Options.resize(0);
    }

    int display()
    {
        titleDisplayer.display(m_Title);
    
        return menuDisplayer.display(m_Options);
    }

    std::string getOption(unsigned int index)
    {
        std::string option;
    
        if (index < m_Options.size())
        {
            option = m_Options[index];
        }

        return option;
    }

    std::string getTitle()
    {
        return m_Title;
    }


private:

    titleDisplayerPolicy titleDisplayer;
    menuDisplayerPolicy menuDisplayer;

    std::string m_Title;
	
    std::vector <std::string> m_Options;
};

#endif
