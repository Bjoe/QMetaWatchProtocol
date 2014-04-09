#include "normalwidget.h"

#include <cstdint>
#include <deque>

namespace qmwp {

static std::deque<uint8_t> widgetIndex = { 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef };

NormalWidget::NormalWidget()
{
}

NormalWidget::~NormalWidget()
{
    widgetIndex.push_back(m_wid);
}

NormalWidget_t NormalWidget::create()
{
    NormalWidget_t widget = NormalWidget_t(new NormalWidget());
    widget->m_type = Type::NORMAL;

    widget->m_wid = widgetIndex.front();
    widgetIndex.pop_front();
    return widget;
}

void NormalWidget::setInvertColor(Widget::InvertColor color)
{
    m_color = color;
}

void NormalWidget::setPosition(Widget::Position wPosition)
{
    m_position = wPosition;
}

void NormalWidget::setLayout(Widget::Layout wLayout)
{
    m_layout = wLayout;
}

} // namespace qmwp
