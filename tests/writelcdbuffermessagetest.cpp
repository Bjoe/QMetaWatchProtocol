
#include <QtTest/QtTest>

#include "testconfig.h"

#include "writelcdbuffermessage.h"
#include "core/metawatchmessage.h"

namespace tests {

class WriteLcdBufferMessageTest : public QObject
{
    Q_OBJECT

private slots:
    void testExample();
};

void WriteLcdBufferMessageTest::testExample()
{
    qmwp::WriteLcdBufferMessage writeLcdBufferMessage;

    qmwp::core::Protocol protocol = writeLcdBufferMessage.createProtocol();

    QCOMPARE(protocol.type(), static_cast<quint8>(0x40));
    QCOMPARE(protocol.option(), static_cast<quint8>(0x00));
    QCOMPARE(protocol.payload().size(), 0);
}

}

QTEST_MAIN(tests::WriteLcdBufferMessageTest)
#include "moc_writelcdbuffermessagetest.cpp"
