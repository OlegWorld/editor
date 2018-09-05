#include "controller.h"

open_file_command::open_file_command(std::string&& filename)
:   m_filename(std::move(filename))
{ }

void open_file_command::operator()(file_control& fc) {
    fc.open_file(m_filename);
}

void new_file_command::operator()(file_control& fc) {
    fc.new_file();
}

save_file_command::save_file_command(std::string&& filename, size_t file_index)
:   m_filename(std::move(filename)),
    m_index(file_index)
{ }

void save_file_command::operator()(file_control& fc) {
    fc.save_to_file(m_filename, m_index);
}

switch_document_command::switch_document_command(document* doc)
        : m_document(doc)
{ }

void switch_document_command::operator()(document_control& dc) {
    dc.change_document(m_document);
}

add_figure_command::add_figure_command(figure* f)
:   m_figure(f)
{ }

void add_figure_command::operator()(document_control& dc) {
    dc.add_figure(m_figure);
}

remove_figure_command::remove_figure_command(figure* f)
:   m_figure(f)
{ }

void remove_figure_command::operator()(document_control& dc) {
    dc.remove_figure(m_figure);
}

document_control::document_control(document* doc)
:   m_document(doc)
{ }

document_control::~document_control() {
    m_document = nullptr;
}

void document_control::change_document(document* doc) {
    m_document = doc;
}

void document_control::add_figure(figure* f) {
    m_document->add_figure(f);
}

void document_control::remove_figure(figure* f) {
    m_document->delete_figure(f);
}

void file_control::new_file() {
    m_opened_docs.emplace_back(new document);
}

void file_control::open_file(const std::string& filename) {
    m_opened_docs.emplace_back(new document(filename));
}

void file_control::save_to_file(const std::string& filename, size_t file_index) {
    std::ofstream ofs(filename);
    ofs << *m_opened_docs[file_index];
    ofs.close();
}

void editor_control::process_file_command(file_command& command) {
    command(m_file_control);
}

void editor_control::process_document_command(document_command& command) {
    command(m_doc_control);
}
