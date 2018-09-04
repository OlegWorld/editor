#include "figures.h"

figure::figure(line_width width, Color color) noexcept
        :   m_width(width),
            m_color (color)
{ }

figure::figure(std::istream &is) {
    figure::deserialize(is);
}

void figure::serialize(std::ostream &os) const {
    os << m_width << " " << static_cast<int>(m_color);
}

void figure::deserialize(std::istream &is) {
    int color;
    is >> m_width >> color;
    m_color = static_cast<Color>(color);
}

point::point(int _x, int _y) noexcept
        :   x(_x),
            y(_y)
{ }

line::line(point begin, point end, line_width width, Color color) noexcept
        :   figure(width, color),
            m_begin(begin),
            m_end(end)
{ }

line::line(std::istream &is)
        :   figure(is)
{
    is >> m_begin.x >> m_begin.y >> m_end.x >> m_end.y;
}

void line::serialize(std::ostream &os) const {
    os << "line ";
    figure::serialize(os);
    os  << m_begin.x << " " << m_begin.y << " "
        << m_end.x << " " << m_end.y
        << std::endl;
}

void line::deserialize(std::istream &is) {
    figure::deserialize(is);
    is >> m_begin.x >> m_begin.y >> m_end.x >> m_end.y;
}

rect::rect(point ul, point dr, line_width width, Color color) noexcept
        :   figure(width, color),
            m_upper_left(ul),
            m_down_right(dr)
{ }

rect::rect(std::istream &is)
        :   figure(is)
{
    is  >> m_upper_left.x >> m_upper_left.y
        >> m_down_right.x >> m_down_right.y;
}

void rect::serialize(std::ostream &os) const {
    os << "rect ";
    figure::serialize(os);
    os  << m_upper_left.x << " " << m_upper_left.y << " "
        << m_down_right.x << " " << m_down_right.y
        << std::endl;
}

void rect::deserialize(std::istream &is) {
    figure::deserialize(is);
    is  >> m_upper_left.x >> m_upper_left.y
        >> m_down_right.x >> m_down_right.y;
}

circle::circle(point center, size_t radius, line_width width, Color color) noexcept
        :   figure(width, color),
            m_center(center),
            m_radius(radius)
{ }

circle::circle(std::istream &is)
        :   figure(is)
{
    is >> m_center.x >> m_center.y >> m_radius;
}

void circle::serialize(std::ostream &os) const {
    os << "circle ";
    figure::serialize(os);
    os << m_center.x << " " << m_center.y << " " << m_radius << std::endl;
}

void circle::deserialize(std::istream &is) {
    figure::deserialize(is);
    is >> m_center.x >> m_center.y >> m_radius;
}

std::ostream &operator<<(std::ostream &os, const figure &f) {
    f.serialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, figure &f) {
    f.deserialize(is);
    return is;
}
