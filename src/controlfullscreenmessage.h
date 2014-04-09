#ifndef QMWP_CONTROLFULLSCREENMESSAGE_H
#define QMWP_CONTROLFULLSCREENMESSAGE_H

#include <QObject>

#include "core/metawatchmessage.h"

namespace qmwp {

class ControlFullScreenMessage : public QObject, public core::Message
{
    Q_OBJECT

    Q_PROPERTY(bool fullScreenChecked READ fullScreenChecked WRITE setFullScreenChecked NOTIFY fullScreenChanged)

public:
    ControlFullScreenMessage(QObject *parent = nullptr);
    virtual ~ControlFullScreenMessage();

    bool fullScreenChecked() const;
    void setFullScreenChecked(bool isFullScreen);

signals:
    void fullScreenChanged();

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

} // namespace qmwp

#endif // QMWP_CONTROLFULLSCREENMESSAGE_H
