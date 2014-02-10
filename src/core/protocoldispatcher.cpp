#include "protocoldispatcher.h"

#include <QHash>
#include <QByteArray>

#include <QDebug>

namespace qmwp {
namespace core {

class ProtocolDispatcher::Private
{
public:
	Private() :
		m_device(nullptr),
		m_handlers()
	{}

    qint64 send(const QByteArray &data)
    {
        if(m_device)
            return m_device->write(data);
        return 0;
    }

    QIODevice *m_device;
    QHash<int, Message*> m_handlers;
};

ProtocolDispatcher::ProtocolDispatcher() :
    m_priv{new Private}
{
}

ProtocolDispatcher::~ProtocolDispatcher()
{
}

void ProtocolDispatcher::initializeDevice(QIODevice *device)
{
    connect(device, SIGNAL(readyRead()), this, SLOT(read()));
    m_priv->m_device = device;
}

void ProtocolDispatcher::read()
{
    QByteArray data = m_priv->m_device->readAll();
    qDebug() << "Read data: " << data.toHex().data();
    Protocol protocol = Protocol::createProtocol(data);
    dispatch(protocol);
}

qint64 ProtocolDispatcher::send(const Message* message)
{
    Protocol protocol = message->createProtocol();
    QByteArray bytes = protocol.createMessage();
    qDebug() << "Send data: " << bytes.toHex().data();
    return m_priv->send(bytes);
}

void ProtocolDispatcher::addHandler(Message *handler)
{
    int type = handler->responseType();
    m_priv->m_handlers.insert(type, handler);
}

void ProtocolDispatcher::dispatch(Protocol protocol)
{
    int type = protocol.type();
    if(m_priv->m_handlers.contains(type)) {
        Message *handler = m_priv->m_handlers.value(type);
        handler->handle(protocol);
    }
}

} // namespace core
} // namespace qmwp
