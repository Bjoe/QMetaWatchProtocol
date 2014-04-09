
#include <QtTest/QtTest>

#include "testconfig.h"

#include <QSharedPointer>

#include "widget.h"
#include "normalwidget.h"

namespace tests {

class WidgetTest : public QObject
{
    Q_OBJECT

private slots:
    void testNormalWidget();
};

void WidgetTest::testNormalWidget()
{
    qmwp::NormalWidget_t normalWidget = qmwp::NormalWidget::create();
    normalWidget->setLayout(qmwp::Widget::Layout::HORIZONTAL);

    qmwp::Widget_t widget = qSharedPointerCast<qmwp::Widget, qmwp::NormalWidget>(normalWidget);
    QCOMPARE(widget->layout(), qmwp::Widget::Layout::HORIZONTAL);
}

}

QTEST_MAIN(tests::WidgetTest)
#include "moc_widgettest.cpp"

