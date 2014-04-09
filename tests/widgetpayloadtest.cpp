
#include <QtTest/QtTest>

#include "testconfig.h"

#include <cstdint>
#include <bitset>
#include <QByteArray>
#include "widget.h"
#include "normalwidget.h"
#include "clockwidget.h"
#include "page.h"

#include "widgetpayload.h"

namespace tests {

class WidgetPayloadTest : public QObject
{
    Q_OBJECT

private slots:
    void testId();
    void testType();
    void testColor();
    void testPage();
    void testLayout();
    void testPosition();
    void testCreateFromByte();
};

void WidgetPayloadTest::testId()
{
    qmwp::NormalWidget_t widget = qmwp::NormalWidget::create();

    qmwp::WidgetPayload payload(qmwp::Page::FOURTH, widget);

    QCOMPARE(payload.id(), static_cast<uint8_t>(0xe0));
}

void WidgetPayloadTest::testType()
{
    qmwp::ClockWidget_t widget = qmwp::ClockWidget::create(qmwp::ClockWidget::BIG);

    qmwp::WidgetPayload payload(qmwp::Page::FOURTH, widget);

    std::bitset<8> widgetSetting = std::bitset<8>("10000000");
    QVERIFY(payload.payload() & widgetSetting.to_ulong());
}

void WidgetPayloadTest::testColor()
{
    qmwp::NormalWidget_t widget = qmwp::NormalWidget::create();
    widget->setInvertColor(qmwp::Widget::InvertColor::INVERT);

    qmwp::WidgetPayload payload(qmwp::Page::FOURTH, widget);

    std::bitset<8> widgetSetting = std::bitset<8>("01000000");
    QVERIFY(payload.payload() & widgetSetting.to_ulong());
}

void WidgetPayloadTest::testPage()
{
    qmwp::NormalWidget_t widget = qmwp::NormalWidget::create();

    qmwp::WidgetPayload payload(qmwp::Page::FOURTH, widget);

    std::bitset<8> widgetSetting = std::bitset<8>("00110000");
    QVERIFY(payload.payload() & widgetSetting.to_ulong());
}

void WidgetPayloadTest::testLayout()
{
    qmwp::NormalWidget_t widget = qmwp::NormalWidget::create();
    widget->setLayout(qmwp::Widget::Layout::HORIZONTAL);

    qmwp::WidgetPayload payload(qmwp::Page::FOURTH, widget);

    std::bitset<8> widgetSetting = std::bitset<8>("00001100");
    QVERIFY(payload.payload() & widgetSetting.to_ulong());
}

void WidgetPayloadTest::testPosition()
{
    qmwp::NormalWidget_t widget = qmwp::NormalWidget::create();
    widget->setPosition(qmwp::Widget::Position::BOTTOM_RIGHT);

    qmwp::WidgetPayload payload(qmwp::Page::FOURTH, widget);

    std::bitset<8> widgetSetting = std::bitset<8>("00000011");
    QVERIFY(payload.payload() & widgetSetting.to_ulong());
}

void WidgetPayloadTest::testCreateFromByte()
{
    qmwp::WidgetPayload payload(0x44,0xFF);

    QCOMPARE(payload.payload(), static_cast<quint8>(0xFF));
    QCOMPARE(payload.pageSite(), qmwp::Page::Site::FOURTH);

    qmwp::Widget_t w = payload.widget();
    QCOMPARE(w->type(), qmwp::Widget::Type::CLOCK);
    QCOMPARE(w->invertColor(), qmwp::Widget::InvertColor::INVERT);
    QCOMPARE(w->layout(), qmwp::Widget::Layout::FULL);
    QCOMPARE(w->position(), qmwp::Widget::Position::BOTTOM_RIGHT);
}

}

QTEST_MAIN(tests::WidgetPayloadTest)
#include "moc_widgetpayloadtest.cpp"
