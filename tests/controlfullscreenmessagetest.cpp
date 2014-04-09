#include <QtTest/QtTest>

#include "testconfig.h"

#include "controlfullscreenmessage.h"

namespace tests {

class ControlFullScreenMessageTest : public QObject
{
    Q_OBJECT
private slots:
    void testCreateRequest();
};

void ControlFullScreenMessageTest::testCreateRequest()
{
    qmwp::ControlFullScreenMessage message;
    message.setFullScreenChecked(true);

    qmwp::core::Protocol protocol = message.createProtocol();

    QCOMPARE(protocol.type(), static_cast<quint8>(0x42));
    QCOMPARE(protocol.option(), static_cast<quint8>(0x01));
    QCOMPARE(protocol.payload().size(), 0);
}

} // namespace tests

QTEST_MAIN(tests::ControlFullScreenMessageTest)
#include "moc_controlfullscreenmessagetest.cpp"
