#pragma once

#include <memory>
#include <string>
#include <fstream>
#include "document.h"

/// \brief класс, осуществляющий управление документом
class editor_control {
public:
    editor_control() = default;

    ~editor_control() = default;

    editor_control& operator=(const editor_control&) = delete;

    /// \brief метод открытия документа путем чтения из файла
    void open_document(const std::string& filename);

    /// \brief метод создания нового пустого документа
    void new_document();

    /// \brief метод сохранения документа в файл
    void save_document(const std::string& filename);

    /// \brief метод добавления в документ линии
    void add_line(point beg, point end);

    /// \brief метод добавления в документ прямоугольника
    void add_rect(point ul, point dr);

    /// \brief метод добавления в документ окружности
    void add_circle(point cent, size_t rad);

    /// \brief метод удаления указанной пользователем фигуры
    void remove_figure(figure* f);

private:
    std::unique_ptr<document> m_opened_doc;
};
