#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <memory>
#include "figures.h"

class document {
public:
    friend std::ofstream& operator<<(std::ofstream& ofs, const document& doc);

    document() = default;

    document(const std::string& filename) {
        std::ifstream ifs(filename);

        for(std::string line; std::getline(ifs, line);) {
            read_figure(line);
        }
    }

    ~document() = default;

    void add_figure(figure* f) {
        m_figures.emplace_back(f);
    }

    void delete_figure(const figure* f) {
        auto it = std::find_if(m_figures.begin(), m_figures.end(), [&f](const auto& fig){ return fig.get() == f; });
        m_figures.erase(it);
    }

private:
    void read_figure(std::string& str) {
        std::istringstream iss(str);
        std::string name;
        iss >> name;

        if (name == "line") {
            m_figures.emplace_back(new line(iss));
        }

        if (name == "rect") {
            m_figures.emplace_back(new rect(iss));
        }

        if (name == "circle") {
            m_figures.emplace_back(new circle(iss));
        }
    }

private:
    std::list<std::unique_ptr<figure>> m_figures;
};

std::ofstream& operator<<(std::ofstream& ofs, const document& doc) {
    for (const auto& fig : doc.m_figures) {
        ofs << *fig;
    }

    return ofs;
}
