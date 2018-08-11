#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <boost/ptr_container/ptr_list.hpp>
#include "figures.h"

class document {
public:
    document() = default;

    document(const std::string& filename) {
        std::ifstream ifs(filename);

        for(std::string line; std::getline(ifs, line);) {
            read_figure(line)
        }
    }

    ~document() = default;

    void read_figure(std::string& str) {
        std::istringstream iss(str);
        std::string name;
        iss >> name;

        if (name == "line") {
            m_figures.push_back(new line(iss));
        }

        if (name == "rect") {
            m_figures.push_back(new rect(iss));
        }

        if (name == "circle") {
            m_figures.push_back(new circle(iss));
        }
    }

private:
    boost::ptr_list<figure> m_figures;
};
