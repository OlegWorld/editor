#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include "document.h"

class file_control;
class document_control;

/// \brief абстрактный класс команд управления файлами
class file_command {
public:
    virtual ~file_command() = default;

    virtual void operator()(file_control& fc) = 0;
};

/// \brief абстрактный класс команд управления документом
class document_command {
public:
    virtual ~document_command() = default;

    virtual void operator()(document_control& dc) = 0;
};

/// \brief команда на открытия файла
class open_file_command : public file_command {
public:
    open_file_command(std::string&& filename);

    ~open_file_command() override = default;

    void operator()(file_control& fc) override;

private:
    std::string m_filename;
};

/// \brief команда создания нового пустого документа
class new_file_command : public file_command {
public:
    ~new_file_command() override = default;

    void operator()(file_control& ec) override;
};

/// \brief команда сохранения в файл
class save_file_command : public file_command {
public:
    save_file_command(std::string&& filename, size_t file_index);

    ~save_file_command() override = default;

    void operator()(file_control& fc) override;

private:
    std::string m_filename;
    size_t m_index;
};

/// \brief команда переключеения активного файла
class switch_document_command : public document_command {
public:
    switch_document_command(document* doc);

    ~switch_document_command() override = default;

    void operator()(document_control& dc) override;

private:
    document* m_document;
};

/// \brief команда добавления фигуры
class add_figure_command : public document_command {
public:
    add_figure_command(figure* f);

    ~add_figure_command() override = default;

    void operator()(document_control& dc);

private:
    figure* m_figure;
};

/// \brief команда удаления фигуры
class remove_figure_command : public document_command {
public:
    remove_figure_command(figure* f);

    ~remove_figure_command() override = default;

    void operator()(document_control& dc);

private:
    figure* m_figure;
};

/// \brief класс, осуществляющий редактирование документа
class document_control {
public:
    explicit document_control(document* doc = nullptr);

    ~document_control();

    /// \brief смена активного файла
    void change_document(document* doc);

    /// \brief метод добавления в документ новой фигуры
    void add_figure(figure* f);

    /// \brief метод удаления указанной пользователем фигуры
    void remove_figure(figure* f);

private:
    document* m_document;
};

/// \brief класс, осуществляющий управление файлами
class file_control {
public:
    using doc_list = std::vector<std::unique_ptr<document>>;

    file_control() = default;

    ~file_control() = default;

    /// \brief создать новый файл
    void new_file();

    /// \brief открыть файл
    void open_file(const std::string& filename);

    /// \brief сохранить в файл
    void save_to_file(const std::string& filename, size_t file_index);

private:
    doc_list m_opened_docs;
};

/// \brief класс, осуществляющий управление редактором
class editor_control {
public:
    editor_control() = default;

    ~editor_control() = default;

    editor_control& operator=(const editor_control&) = delete;

    void process_file_command(file_command& command);

    void process_document_command(document_command& command);

private:
    file_control m_file_control;
    document_control m_doc_control;
};
