
#include <QtTest/QtTest>

#include "testconfig.h"

#include <cstdint>

#include "clockwidget.h"

namespace tests {

class ClockWidgetTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreateClock();
    void testId();
};

void ClockWidgetTest::testCreateClock()
{
    qmwp::ClockWidget_t widget = qmwp::ClockWidget::create(qmwp::ClockWidget::LOGO);

    QCOMPARE(widget->id(), static_cast<uint8_t>(0x21));
    QCOMPARE(widget->type(), qmwp::Widget::Type::CLOCK);
    QCOMPARE(widget->clockType(), qmwp::ClockWidget::LOGO);
}

void ClockWidgetTest::testId()
{
    qmwp::ClockWidget_t widget1 = qmwp::ClockWidget::create(qmwp::ClockWidget::HANZI);

    qmwp::ClockWidget_t widget2 = qmwp::ClockWidget::create(qmwp::ClockWidget::BIG);

    QCOMPARE(widget1->id(), static_cast<uint8_t>(0x52));
    QCOMPARE(widget2->id(), static_cast<uint8_t>(0x33));
}

}

QTEST_MAIN(tests::ClockWidgetTest)
#include "moc_clockwidgettest.cpp"

