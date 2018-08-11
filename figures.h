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

class figure {
public:
    explicit figure(line_width width = 1, Color color = Color::Black) noexcept
    :   m_width(width),
        m_color (color)
    { }

    virtual ~figure() = default;

    line_width get_width() const noexcept {
        return m_width;
    }

    void set_width(line_width width) noexcept {
        m_width = width;
    }

    Color get_color() const noexcept {
        return m_color;
    }

    void set_color(Color color) noexcept {
        m_color = color;
    }

    virtual void serialize(std::ostream& os) const {
        os << m_width << " " << static_cast<int>(m_color) << std::endl;
    }

    virtual void deserialize(std::istream& is) {
        int color;
        is >> m_width >> color;
        m_color = static_cast<Color>(color);
    }

private:
    line_width m_width;
    Color m_color;
};

struct point {
    explicit point(int _x = 0, int _y = 0) noexcept
    :   x(_x),
        y(_y)
    { }

    int x;
    int y;
};

class line : public figure {
public:
    line(point begin, point end, line_width width = 1, Color color = Color::Black) noexcept
    :   figure(width, color),
        m_begin(begin),
        m_end(end)
    { }

    ~line() override = default;

    point& begin() noexcept {
        return m_begin;
    }

    const point& begin() const noexcept {
        return m_begin;
    }

    point& end() noexcept {
        return m_end;
    }

    const point& end() const noexcept {
        return m_end;
    }

    void serialize(std::ostream& os) const override {
        os << "line ";
        os  << m_begin.x << " " << m_begin.y << " "
            << m_end.x << " " << m_end.y << " ";
        figure::serialize(os);
    }

    void deserialize(std::istream& is) override {
        is >> m_begin.x >> m_begin.y >> m_end.x >> m_end.y;
        figure::deserialize(is);
    }

private:
    point m_begin;
    point m_end;
};

class rect : public figure {
public:
    rect(point ul, point dr, line_width width = 1, Color color = Color::Black) noexcept
    :   figure(width, color),
        m_upper_left(ul),
        m_down_right(dr)
    { }

    ~rect() override = default;

    point& upper_left_corner() noexcept {
        return m_upper_left;
    }

    const point& upper_left_corner() const noexcept {
        return m_upper_left;
    }

    point& down_right_corner() noexcept {
        return m_down_right;
    }

    const point& down_right_corner() const noexcept {
        return m_down_right;
    }

    void serialize(std::ostream &os) const override {
        os << "rect ";
        os  << m_upper_left.x << " " << m_upper_left.y << " "
            << m_down_right.x << " " << m_down_right.y << " ";
        figure::serialize(os);
    }

    void deserialize(std::istream &is) override {
        is  >> m_upper_left.x >> m_upper_left.y
            >> m_down_right.x >> m_down_right.y;
        figure::deserialize(is);
    }

private:
    point m_upper_left;
    point m_down_right;
};

class circle : public figure {
public:
    circle(point center, size_t radius, line_width width = 1, Color color = Color::Black) noexcept
    :   figure(width, color),
        m_center(center),
        m_radius(radius)
    { }

    ~circle() override = default;

    point& center() noexcept {
        return m_center;
    }

    const point& center() const noexcept {
        return m_center;
    }

    size_t radius() const noexcept {
        return m_radius;
    }

    void set_radius(size_t rad) noexcept {
        m_radius = rad;
    }

    void serialize(std::ostream &os) const override {
        os << "circle ";
        os << m_center.x << " " << m_center.y << " " << m_radius << " ";
        figure::serialize(os);
    }

    void deserialize(std::istream &is) override {
        is >> m_center.x >> m_center.y >> m_radius;
        figure::deserialize(is);
    }

private:
    point m_center;
    size_t m_radius;
};

std::ostream& operator<<(std::ostream& os, const figure& f) {
    f.serialize(os);
    return os;
}

std::istream& operator>>(std::istream& is, figure& f) {
    f.deserialize(is);
    return is;
}