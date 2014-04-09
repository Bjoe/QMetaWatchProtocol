#include "clockwidget.h"

#include <cstdint>
#include <deque>

namespace qmwp {

static std::deque<uint8_t> clockIndex = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

ClockWidget::ClockWidget()
{
}

ClockWidget::~ClockWidget()
{
    clockIndex.push_back(m_wid & 0x0F);
}

ClockWidget_t ClockWidget::create(ClockWidget::Type type)
{
    ClockWidget_t widget = ClockWidget_t(new ClockWidget());
    widget->m_type = Widget::Type::CLOCK;
    widget->m_clockType = type;

    uint8_t wid = clockIndex.front();
    switch(type) {
    case ClockWidget::UP_LEFT:
        widget->m_layout = Widget::Layout::QUAD;
        widget->m_position = Widget::Position::UP_LEFT;
        break;
    case ClockWidget::UP_RIGHT:
        widget->m_layout = Widget::Layout::QUAD;
        widget->m_position = Widget::Position::UP_RIGHT;
        break;
    case ClockWidget::BOTTOM_LEFT:
        widget->m_layout = Widget::Layout::QUAD;
        widget->m_position = Widget::Position::BOTTOM_LEFT;
        break;
    case ClockWidget::BOTTOM_RIGHT:
        widget->m_layout = Widget::Layout::QUAD;
        widget->m_position = Widget::Position::BOTTOM_RIGHT;
        break;
    case ClockWidget::UP_HORIZONTAL:
        wid |= 0x10;
        widget->m_layout = Widget::Layout::HORIZONTAL;
        widget->m_position = Widget::Position::UP_LEFT;
        break;
    case ClockWidget::BOTTOM_HORIZONTAL:
        wid |= 0x10;
        widget->m_layout = Widget::Layout::HORIZONTAL;
        widget->m_position = Widget::Position::BOTTOM_LEFT;
        break;
    case ClockWidget::BIG:
        wid |= 0x30;
        widget->m_layout = Widget::Layout::FULL;
        widget->m_position = Widget::Position::UP_LEFT;
        break;
    case ClockWidget::FISH:
        wid |= 0x40;
        widget->m_layout = Widget::Layout::FULL;
        widget->m_position = Widget::Position::UP_LEFT;
        break;
    case ClockWidget::HANZI:
        wid |= 0x50;
        widget->m_layout = Widget::Layout::FULL;
        widget->m_position = Widget::Position::UP_LEFT;
        break;
    case ClockWidget::LOGO:
        wid |= 0x20;
        widget->m_layout = Widget::Layout::FULL;
        widget->m_position = Widget::Position::UP_LEFT;
        break;
    default:
        widget->m_layout = Widget::Layout::QUAD;
        widget->m_position = Widget::Position::UP_LEFT;
        break;
    }

    widget->m_wid = wid;
    clockIndex.pop_front();
    return widget;

}

void ClockWidget::setInvertColor(Widget::InvertColor color)
{
    m_color = color;
}

ClockWidget::Type ClockWidget::clockType() const
{
    return m_clockType;
}

} // namespace qmwp
