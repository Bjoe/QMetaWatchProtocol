#ifndef QMWP_SCREEN_H
#define QMWP_SCREEN_H

#include <QMap>
#include <QList>

#include "page.h"
#include "setwidgetlistmessage.h"

namespace qmwp {

class Screen
{
public:

    Screen();

    void addPage(Page_t page);

    QMap<Page::Site, Page_t> pages() const;

    QList<SetWidgetListMessage_t> createMessages() const;

private:
    QMap<Page::Site, Page_t> m_screen {};
};

} // namespace qmwp

#endif // QMWP_SCREEN_H
