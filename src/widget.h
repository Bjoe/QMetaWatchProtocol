#ifndef QMWP_WIDGET_H
#define QMWP_WIDGET_H

#include <cstdint>
#include <QSharedPointer>

namespace qmwp {

class Widget
{
public:
    enum class Type { NORMAL, CLOCK };
    enum class InvertColor { NORMAL, INVERT };
    enum class Layout { QUAD, HORIZONTAL, VERTICAL, FULL };
    enum class Position { UP_LEFT, UP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

    Widget();
    Widget(uint8_t id, Type type, InvertColor color, Layout layout, Position position);
    virtual ~Widget();

    uint8_t id() const;
    Type type() const;
    InvertColor invertColor() const;
    Layout layout() const;
    Position position() const;

protected:
    uint8_t m_wid = 0;
    Type m_type = Type::NORMAL;
    InvertColor m_color = InvertColor::NORMAL;
    Layout m_layout = Layout::QUAD;
    Position m_position = Position::UP_LEFT;
};

using Widget_t = QSharedPointer<Widget>;

} // namespace qmwp

#endif // QMWP_WIDGET_H
