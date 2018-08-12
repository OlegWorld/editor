#pragma once

#include <cstddef>
#include <iostream>

using line_width = size_t;

enum class Color {
    Red,
    Green,
    Blue,
    Black
};

/// \brief базовый класс, описывающий абстрактнцю фигуру
class figure {
public:
    explicit figure(line_width width = 1, Color color = Color::Black) noexcept;

    explicit figure(std::istream& is);

    virtual ~figure() = default;

    /// \brief виртуальный метод для вывода фигуры в поток
    virtual void serialize(std::ostream& os) const;

    /// \brief виртуальный метод для чтения фигуры из потока
    virtual void deserialize(std::istream& is);

private:
    line_width m_width;
    Color m_color;
};

/// \brief структура, описывающая точку на плоскости и хранящая ее коордиаты
class point {
public:
    explicit point(int _x = 0, int _y = 0) noexcept;

    int x;
    int y;
};

/// \brief класс, описывающий объект линии
class line : public figure {
public:
    line(point begin, point end, line_width width = 1, Color color = Color::Black) noexcept;

    explicit line(std::istream& is);

    ~line() override = default;

    /// \brief виртуальный метод для вывода линии в поток
    void serialize(std::ostream& os) const override;

    /// \brief виртуальный метод для чтения линии из потока
    void deserialize(std::istream& is) override;

private:
    point m_begin;
    point m_end;
};

/// \brief класс, описывающий объект прямоугольника
class rect : public figure {
public:
    rect(point ul, point dr, line_width width = 1, Color color = Color::Black) noexcept;

    explicit rect(std::istream& is);

    ~rect() override = default;

    /// \brief виртуальный метод для вывода прямоугольника в поток
    void serialize(std::ostream &os) const override;

    /// \brief виртуальный метод для чтения прямоугольника из потока
    void deserialize(std::istream &is) override;

private:
    point m_upper_left;
    point m_down_right;
};

/// \brief класс, описывающий объект окружности
class circle : public figure {
public:
    circle(point center, size_t radius, line_width width = 1, Color color = Color::Black) noexcept;

    explicit circle(std::istream& is);

    ~circle() override = default;

    /// \brief виртуальный метод для вывода окружности в поток
    void serialize(std::ostream &os) const override;

    /// \brief виртуальный метод для чтения окружности из потока
    void deserialize(std::istream &is) override;

private:
    point m_center;
    size_t m_radius;
};

/// \brief глобальная функция для вывода произвольной фигуры в поток
std::ostream& operator<<(std::ostream& os, const figure& f);

/// \brief глобальная функция для чтения произвольной фигуры из потока
std::istream& operator>>(std::istream& is, figure& f);