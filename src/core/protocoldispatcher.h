#ifndef QMWP_CORE_PROTOCOLDISPATCHER_H
#define QMWP_CORE_PROTOCOLDISPATCHER_H

#include <boost/tr1/memory.hpp>
#include <QObject>
#include <QIODevice>

#include "core/metawatchprotocol.h"
#include "core/metawatchmessage.h"

namespace qmwp {
namespace core {

class ProtocolDispatcher : public QObject
{
	Q_OBJECT

public:
    ProtocolDispatcher();
    ~ProtocolDispatcher();

    void initializeDevice(QIODevice *device);
    qint64 send(const Message *message);

    void addHandler(Message *handler);

    void dispatch(Protocol protocol);

private slots:
	void read();

private:
    class Private;
    std::tr1::shared_ptr<Private> m_priv;
};

} // namespace core
} // namespace qmwp

#endif // QMWP_CORE_PROTOCOLDISPATCHER_H
