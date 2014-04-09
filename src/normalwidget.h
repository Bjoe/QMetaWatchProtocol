#ifndef QMWP_NORMALWIDGET_H
#define QMWP_NORMALWIDGET_H

#include <QSharedPointer>

#include "widget.h"

namespace qmwp {

class NormalWidget;
using NormalWidget_t = QSharedPointer<NormalWidget>;

class NormalWidget : public Widget
{
public:
    virtual ~NormalWidget();

    static NormalWidget_t create();

    void setLayout(Layout wLayout);
    void setInvertColor(InvertColor color);
    void setPosition(Position wPosition);

private:
    NormalWidget();
};

} // namespace qmwp

#endif // QMWP_NORMALWIDGET_H
