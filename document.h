#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <memory>
#include "figures.h"

/// \brief класс рабочего документа, в который можно добавлять/удалять фигуры
class document {
public:
    friend std::ofstream& operator<<(std::ofstream& ofs, const document& doc);

    document() = default;

    /// \brief конструктор для чтения документа из файла
    explicit document(const std::string& filename);

    ~document() = default;

    /// \brief добавление новой фигуры к документу
    void add_figure(figure* f);

    /// \brief удаление выделенной пользователем фигуры
    void delete_figure(const figure* f);

private:
    /// \brief чтение фигуры из файла
    void read_figure(std::string& str);

private:
    std::list<std::unique_ptr<figure>> m_figures;
};

/// \brief запись документа в файл
std::ofstream& operator<<(std::ofstream& ofs, const document& doc);
