#include "screen.h"

#include <algorithm>
#include "widgetpayload.h"

namespace qmwp {

Screen::Screen()
{
}

void Screen::addPage(Page_t page)
{
    Page::Site site = page->site();
    m_screen.insert(site, page);
}

QMap<Page::Site, Page_t> Screen::pages() const
{
    return m_screen;
}

QList<SetWidgetListMessage_t> Screen::createMessages() const
{
    QList<WidgetPayload> payloads;
    QList<Page::Site> pageSites = m_screen.keys();
    for(Page::Site site : pageSites) {
        Page_t page = m_screen.value(site);
        QMap<Widget::Position, Widget_t> widgets = page->pageSite();
        QList<Widget::Position> positions = widgets.keys();
        for(Widget::Position position : positions) {
            Widget_t widget = widgets.value(position);
            payloads.append(WidgetPayload(site, widget));
        }
    }

    std::sort(payloads.begin(), payloads.end(),
    [](const WidgetPayload& payload1, const WidgetPayload& payload2)
    {
        return payload1.id() < payload2.id();
    });

    QList<SetWidgetListMessage_t> list;

    SetWidgetListMessage::TotalMessage totalMessages = static_cast<SetWidgetListMessage::TotalMessage>((payloads.size() / 7) + 1);
    int messageIndex = 0;
    int count = 0;
    int newMessage = 0;
    SetWidgetListMessage_t widgetList;
    for(WidgetPayload payload : payloads) {
        if(count >= newMessage) {
            SetWidgetListMessage::MessageIndex index = static_cast<SetWidgetListMessage::MessageIndex>(messageIndex);

            widgetList = SetWidgetListMessage_t(new SetWidgetListMessage());
            widgetList->setTotalMessages(totalMessages);
            widgetList->setMessageIndex(index);

            list.append(widgetList);
            ++messageIndex;
            newMessage += 7;
        }

        widgetList->addWidgetPayload(payload);
        ++count;
    }
    return list;
}

} // namespace qmwp
