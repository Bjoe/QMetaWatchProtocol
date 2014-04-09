#include "writelcdbuffermessage.h"

#include <QByteArray>

namespace qmwp {

class WriteLcdBufferMessage::Private
{
public:
    QByteArray m_bytes{};
    quint8 m_option = 0;
};

WriteLcdBufferMessage::WriteLcdBufferMessage()
    : Message(
          [this](core::Protocol& protocol)
          {
            protocol.setType(0x40);
            protocol.setOption(m_priv->m_option);
            protocol.setPayload(m_priv->m_bytes);
          },
          [this](core::Protocol& protocol)
          {
          },
          0x40
    ),
    m_priv{ new Private }
{
}

WriteLcdBufferMessage::~WriteLcdBufferMessage()
{}

void WriteLcdBufferMessage::test()
{
    m_priv->m_option = 0x80;

    m_priv->m_bytes.append(static_cast<char>(0x11)) // Widget ID
            .append(static_cast<char>(0)) // Row

            .append(static_cast<char>(0))
            .append(static_cast<char>(0))
            .append(static_cast<char>(0))
            .append(static_cast<char>(0))
            .append(static_cast<char>(0))

            .append(static_cast<char>(0))
            .append(static_cast<char>(0))
            .append(static_cast<char>(0))
            .append(static_cast<char>(0))
            .append(static_cast<char>(0))

            .append(static_cast<char>(0))
            .append(static_cast<char>(0));
}




} // namespace qmwp
