#ifndef QMWP_CLOCKWIDGET_H
#define QMWP_CLOCKWIDGET_H

#include <QSharedPointer>

#include "widget.h"

namespace qmwp {

class ClockWidget;
using ClockWidget_t = QSharedPointer<ClockWidget>;

class ClockWidget : public Widget
{
public:
    enum Type { UP_LEFT, UP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT,
                UP_HORIZONTAL, BOTTOM_HORIZONTAL, LOGO, BIG, FISH, HANZI };

    ~ClockWidget();

    static ClockWidget_t create(Type type);

    void setInvertColor(InvertColor color);
    Type clockType() const;

private:
    ClockWidget();

    Type m_clockType = UP_LEFT;
};

} // namespace qmwp

#endif // QMWP_CLOCKWIDGET_H
