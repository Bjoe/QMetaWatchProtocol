
#include <QtTest/QtTest>

#include "testconfig.h"

#include <QSharedPointer>
#include <QMap>
#include <QList>

#include "normalwidget.h"
#include "setwidgetlistmessage.h"
#include "page.h"

#include "screen.h"

namespace tests {

class ScreenTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreate();
    void testCreateMessage();
};

void ScreenTest::testCreate()
{
    qmwp::Page_t page = qmwp::Page_t(new qmwp::Page(qmwp::Page::FIRST));

    qmwp::Screen screen;

    screen.addPage(page);

    QMap<qmwp::Page::Site, qmwp::Page_t> pages = screen.pages();

    qmwp::Page_t result = pages.value(qmwp::Page::FIRST);
    QCOMPARE(result, page);
}

void ScreenTest::testCreateMessage()
{
    qmwp::NormalWidget_t widget1 = qmwp::NormalWidget::create();
    qmwp::NormalWidget_t widget2 = qmwp::NormalWidget::create();
    qmwp::NormalWidget_t widget3 = qmwp::NormalWidget::create();
    widget3->setPosition(qmwp::NormalWidget::Position::UP_RIGHT);
    qmwp::NormalWidget_t widget4 = qmwp::NormalWidget::create();
    widget4->setPosition(qmwp::NormalWidget::Position::BOTTOM_LEFT);
    qmwp::NormalWidget_t widget5 = qmwp::NormalWidget::create();
    widget5->setPosition(qmwp::NormalWidget::Position::BOTTOM_RIGHT);
    qmwp::NormalWidget_t widget6 = qmwp::NormalWidget::create();
    widget6->setPosition(qmwp::NormalWidget::Position::BOTTOM_RIGHT);
    qmwp::NormalWidget_t widget7 = qmwp::NormalWidget::create();
    widget7->setPosition(qmwp::NormalWidget::Position::BOTTOM_LEFT);
    qmwp::NormalWidget_t widget8 = qmwp::NormalWidget::create();
    widget8->setPosition((qmwp::NormalWidget::Position::BOTTOM_RIGHT));

    qmwp::Page_t page1 = qmwp::Page_t(new qmwp::Page(qmwp::Page::FIRST));
    qmwp::Page_t page2 = qmwp::Page_t(new qmwp::Page(qmwp::Page::THIRD));
    qmwp::Page_t page3 = qmwp::Page_t(new qmwp::Page(qmwp::Page::SECOND));

    page1->addWidget(widget2);
    page2->addWidget(widget1);
    page2->addWidget(widget3);
    page3->addWidget(widget4);
    page3->addWidget(widget5);
    page1->addWidget(widget6);
    page1->addWidget(widget7);
    page2->addWidget(widget8);

    qmwp::Screen screen;

    screen.addPage(page1);
    screen.addPage(page2);
    screen.addPage(page3);

    QList<qmwp::SetWidgetListMessage_t> messages = screen.createMessages();

    QCOMPARE(messages.size(), 2);

    qmwp::SetWidgetListMessage_t widgetListMessage = messages.at(0);
    QCOMPARE(widgetListMessage->totalMessage(), qmwp::SetWidgetListMessage::TotalMessage::TWO);
    QCOMPARE(widgetListMessage->messageIndex(), qmwp::SetWidgetListMessage::MessageIndex::FIRST);

    QList<qmwp::WidgetPayload> payloads = widgetListMessage->widgetPayload();

    qmwp::WidgetPayload payload = payloads.at(0);

    QCOMPARE(payload.id(), static_cast<uint8_t>(0xe0));
    QCOMPARE(payload.payload(), static_cast<uint8_t>(0x20));

    payload = payloads.at(1);
    QCOMPARE(payload.id(), static_cast<uint8_t>(0xe1));
    QCOMPARE(payload.payload(), static_cast<uint8_t>(0x00));

    widgetListMessage = messages.at(1);
    QCOMPARE(widgetListMessage->totalMessage(), qmwp::SetWidgetListMessage::TotalMessage::TWO);
    QCOMPARE(widgetListMessage->messageIndex(), qmwp::SetWidgetListMessage::MessageIndex::SECOND);
}

}

QTEST_MAIN(tests::ScreenTest)
#include "moc_screentest.cpp"

