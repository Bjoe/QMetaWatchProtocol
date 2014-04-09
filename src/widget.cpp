#include "widget.h"

namespace qmwp {

Widget::Widget()
{
}

Widget::Widget(uint8_t id, Widget::Type type, Widget::InvertColor color, Widget::Layout layout, Widget::Position position)
    : m_wid(id), m_type(type), m_color(color), m_layout(layout), m_position(position)
{
}

Widget::~Widget()
{
}

uint8_t Widget::id() const
{
    return m_wid;
}

Widget::Type Widget::type() const
{
    return m_type;
}

Widget::InvertColor Widget::invertColor() const
{
    return m_color;
}

Widget::Layout Widget::layout() const
{
    return m_layout;
}

Widget::Position Widget::position() const
{
    return m_position;
}

} // namespace qmwp
