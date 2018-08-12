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
    explicit figure(line_width width = 1, Color color = Color::Black) noexcept;

    explicit figure(std::istream& is);

    virtual ~figure() = default;

    virtual void serialize(std::ostream& os) const {
        os << m_width << " " << static_cast<int>(m_color);
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
    explicit point(int _x = 0, int _y = 0) noexcept;

    int x;
    int y;
};

class line : public figure {
public:
    line(point begin, point end, line_width width = 1, Color color = Color::Black) noexcept;

    explicit line(std::istream& is);

    ~line() override = default;

    void serialize(std::ostream& os) const override;

    void deserialize(std::istream& is) override;

private:
    point m_begin;
    point m_end;
};

class rect : public figure {
public:
    rect(point ul, point dr, line_width width = 1, Color color = Color::Black) noexcept;

    explicit rect(std::istream& is);

    ~rect() override = default;

    void serialize(std::ostream &os) const override;

    void deserialize(std::istream &is) override;

private:
    point m_upper_left;
    point m_down_right;
};

class circle : public figure {
public:
    circle(point center, size_t radius, line_width width = 1, Color color = Color::Black) noexcept;

    explicit circle(std::istream& is);

    ~circle() override = default;

    void serialize(std::ostream &os) const override;

    void deserialize(std::istream &is) override;

private:
    point m_center;
    size_t m_radius;
};

std::ostream& operator<<(std::ostream& os, const figure& f);

std::istream& operator>>(std::istream& is, figure& f);