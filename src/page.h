#ifndef QMWP_PAGE_H
#define QMWP_PAGE_H

#include <QSharedPointer>
#include <QMap>

#include "widget.h"

namespace qmwp {

class Page
{
public:
    enum Site { FIRST, SECOND, THIRD, FOURTH };

    Page(Site aSite);

    void addWidget(Widget_t widget);

    Site site() const;
    QMap<Widget::Position, Widget_t> pageSite() const;

private:
    QMap<Widget::Position, Widget_t> m_pageMap {};
    Site m_site;
};

using Page_t = QSharedPointer<Page>;

} // namespace qmwp

#endif // QMWP_PAGE_H
