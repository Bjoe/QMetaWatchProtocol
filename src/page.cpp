#include "page.h"

namespace qmwp {

Page::Page(Site aSite) : m_site(aSite)
{
}

Page::Site Page::site() const
{
    return m_site;
}

QMap<Widget::Position, Widget_t> Page::pageSite() const
{
    return m_pageMap;
}

void Page::addWidget(Widget_t widget)
{
    Widget::Position position = widget->position();
    m_pageMap.insert(position, widget);
}

} // namespace qmwp
