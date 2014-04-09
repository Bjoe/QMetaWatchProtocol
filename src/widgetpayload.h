#ifndef QMWP_WIDGETPAYLOAD_H
#define QMWP_WIDGETPAYLOAD_H

#include <cstdint>
#include <QByteArray>
#include "widget.h"
#include "page.h"

namespace qmwp {

class WidgetPayload
{
public:
    WidgetPayload(Page::Site aSite, Widget_t aWidget);
    WidgetPayload(uint8_t anId, uint8_t aByte);

    uint8_t id() const;
    Widget_t widget() const;
    Page::Site pageSite() const;

    uint8_t payload() const;

private:
    Page::Site m_site;
    Widget_t m_widget;
};

} // namespace qmwp

#endif // QMWP_WIDGETPAYLOAD_H
