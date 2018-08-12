#include "controller.h"

void editor_control::open_document(const std::string &filename) {
    m_opened_doc = std::make_unique<document>(filename);
}

void editor_control::new_document() {
    m_opened_doc = std::make_unique<document>();
}

void editor_control::save_document(const std::string &filename) {
    std::ofstream ofs(filename);
    ofs << *m_opened_doc;
}

void editor_control::add_line(point beg, point end) {
    m_opened_doc->add_figure(new line(beg, end));
}

void editor_control::add_rect(point ul, point dr) {
    m_opened_doc->add_figure(new rect(ul, dr));
}

void editor_control::add_circle(point cent, size_t rad) {
    m_opened_doc->add_figure(new circle(cent, rad));
}

void editor_control::remove_figure(figure *f) {
    m_opened_doc->delete_figure(f);
}
