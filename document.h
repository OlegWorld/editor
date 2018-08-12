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

    document(const std::string& filename);

    ~document() = default;

    void add_figure(figure* f);

    void delete_figure(const figure* f);

private:
    void read_figure(std::string& str);

private:
    std::list<std::unique_ptr<figure>> m_figures;
};

std::ofstream& operator<<(std::ofstream& ofs, const document& doc);
