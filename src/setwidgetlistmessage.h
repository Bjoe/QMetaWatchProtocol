#ifndef QMWP_SETWIDGETLISTMESSAGE_H
#define QMWP_SETWIDGETLISTMESSAGE_H

#include <QSharedPointer>
#include <QList>

#include "core/metawatchmessage.h"
#include "widgetpayload.h"

namespace qmwp {

class SetWidgetListMessage : public core::Message
{
public:
    enum class TotalMessage { ONE = 1, TWO, THREE };
    enum class MessageIndex { FIRST, SECOND, THIRD };

    SetWidgetListMessage();
    virtual ~SetWidgetListMessage();

    void setTotalMessages(TotalMessage total);
    TotalMessage totalMessage() const;

    void setMessageIndex(MessageIndex index);
    MessageIndex messageIndex() const;

    void addWidgetPayload(WidgetPayload payload);
    QList<WidgetPayload> widgetPayload() const;

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

using SetWidgetListMessage_t = QSharedPointer<SetWidgetListMessage>;

} // namespace qmwp

#endif // QMWP_SETWIDGETLISTMESSAGE_H
