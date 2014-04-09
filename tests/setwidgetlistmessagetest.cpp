
#include <QtTest/QtTest>
#include <QByteArray>

#include "testconfig.h"

#include "core/protocoldispatcher.h"
#include "widgetpayload.h"


#include "normalwidget.h"
#include "page.h"
#include "screen.h"

#include "setwidgetlistmessage.h"

namespace tests {

class SetWidgetListMessageTest : public QObject
{
    Q_OBJECT

private slots:

    void testCreateRequest();
    void testSetTotalMessages();
    void testMessageIndex();
    void testAddWidgetPayload();
};

void SetWidgetListMessageTest::testCreateRequest()
{
    qmwp::SetWidgetListMessage message;

    qmwp::core::Protocol protocol = message.createProtocol();

    QCOMPARE(protocol.type(), static_cast<quint8>(0xa1));
}

void SetWidgetListMessageTest::testSetTotalMessages()
{
    qmwp::SetWidgetListMessage message;
    message.setTotalMessages(qmwp::SetWidgetListMessage::TotalMessage::TWO);

    qmwp::core::Protocol protocol = message.createProtocol();

    QCOMPARE(protocol.option(), static_cast<quint8>(0x08));
    QCOMPARE(message.totalMessage(), qmwp::SetWidgetListMessage::TotalMessage::TWO);
}

void SetWidgetListMessageTest::testMessageIndex()
{
    qmwp::SetWidgetListMessage message;
    message.setMessageIndex(qmwp::SetWidgetListMessage::MessageIndex::SECOND);

    qmwp::core::Protocol protocol = message.createProtocol();

    QCOMPARE(protocol.option(), static_cast<quint8>(0x01));
    QCOMPARE(message.messageIndex(), qmwp::SetWidgetListMessage::MessageIndex::SECOND);
}

void SetWidgetListMessageTest::testAddWidgetPayload()
{
    qmwp::WidgetPayload payload(0x23, 0x42);

    qmwp::SetWidgetListMessage message;

    message.addWidgetPayload(payload);

    qmwp::core::Protocol protocol = message.createProtocol();

    QList<qmwp::WidgetPayload> payloads = message.widgetPayload();
    qmwp::WidgetPayload revPayload = payloads.at(0);
    QCOMPARE(revPayload.id(), static_cast<uint8_t>(0x23));
    QCOMPARE(revPayload.payload(), static_cast<uint8_t>(0x42));

    QByteArray bytes = protocol.payload();
    QCOMPARE(bytes.size(), 2);
    QCOMPARE(bytes.at(0), static_cast<char>(0x23));
    QCOMPARE(bytes.at(1), static_cast<char>(0x42));
}

}

QTEST_MAIN(tests::SetWidgetListMessageTest)
#include "moc_setwidgetlistmessagetest.cpp"
