#pragma once

#include <memory>
#include <string>
#include <fstream>
#include "document.h"

class editor_control {
public:
    editor_control() = default;

    ~editor_control() = default;

    editor_control& operator=(const editor_control&) = delete;

    void open_document(const std::string& filename);

    void new_document();

    void save_document(const std::string& filename);

    void add_line(point beg, point end);

    void add_rect(point ul, point dr);

    void add_circle(point cent, size_t rad);

    void remove_figure(figure* f);

private:
    std::unique_ptr<document> m_opened_doc;
};
