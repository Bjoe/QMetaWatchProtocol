#include "widgetpayload.h"

#include <bitset>

namespace qmwp {

WidgetPayload::WidgetPayload(Page::Site aSite, Widget_t aWidget)
    : m_site(aSite), m_widget(aWidget)
{
}

WidgetPayload::WidgetPayload(uint8_t anId, uint8_t aByte)
    : m_site(Page::FIRST), m_widget(nullptr)
{
    std::bitset<8> bType = (std::bitset<8>(aByte) &
                            std::bitset<8>("10000000")) >> 7;
    Widget::Type type = static_cast<Widget::Type>(bType.to_ulong());

    std::bitset<8> bColor = (std::bitset<8>(aByte) &
                            std::bitset<8>("01000000")) >> 6;
    Widget::InvertColor color = static_cast<Widget::InvertColor>(bColor.to_ulong());

    std::bitset<8> bSite = (std::bitset<8>(aByte) &
                           std::bitset<8>("00110000")) >> 4;
    m_site = static_cast<Page::Site>(bSite.to_ulong());

    std::bitset<8> bLayout = (std::bitset<8>(aByte) &
                              std::bitset<8>("00001100")) >> 2;
    Widget::Layout layout = static_cast<Widget::Layout>(bLayout.to_ulong());

    std::bitset<8> bPosition = (std::bitset<8>(aByte) &
                                std::bitset<8>("00000011"));
    Widget::Position position = static_cast<Widget::Position>(bPosition.to_ulong());

    m_widget = Widget_t(new Widget(anId, type, color, layout, position));
}

uint8_t WidgetPayload::id() const
{
    return m_widget->id();
}

Widget_t WidgetPayload::widget() const
{
    return m_widget;
}

Page::Site WidgetPayload::pageSite() const
{
    return m_site;
}

uint8_t WidgetPayload::payload() const
{
    uint8_t result = 0;

    result |= (static_cast<uint8_t>(m_widget->type()) << 7);
    result |= (static_cast<uint8_t>(m_widget->invertColor()) << 6);
    result |= (static_cast<uint8_t>(m_site) << 4);
    result |= (static_cast<uint8_t>(m_widget->layout()) << 2);
    result |= static_cast<uint8_t>(m_widget->position());

    return result;
}

} // namespace qmwp
