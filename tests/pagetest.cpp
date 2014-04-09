
#include <QtTest/QtTest>

#include "testconfig.h"

#include <QSharedPointer>
#include <QMap>
#include "widget.h"
#include "normalwidget.h"

#include "page.h"

namespace tests {

class PageTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreate();
};

void PageTest::testCreate()
{
    qmwp::NormalWidget_t widget = qmwp::NormalWidget::create();
    widget->setPosition(qmwp::Widget::Position::BOTTOM_LEFT);

    qmwp::Page page(qmwp::Page::FIRST);

    page.addWidget(widget);

    QMap<qmwp::Widget::Position, qmwp::Widget_t> site = page.pageSite();

    qmwp::Widget_t result = site.value(qmwp::Widget::Position::BOTTOM_LEFT);
    qmwp::Widget_t expected = qSharedPointerCast<qmwp::Widget, qmwp::NormalWidget>(widget);
    QCOMPARE(result, expected);
    QCOMPARE(page.site(), qmwp::Page::FIRST);
}

}

QTEST_MAIN(tests::PageTest)
#include "moc_pagetest.cpp"
