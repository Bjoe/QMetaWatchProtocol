#include "setwidgetlistmessage.h"

#include <bitset>
#include <QByteArray>

namespace qmwp {

class SetWidgetListMessage::Private
{
public:
    QByteArray m_bytes{};
    std::bitset<8> m_option{ "00000000" };
};

SetWidgetListMessage::SetWidgetListMessage()
    : Message(
          [this](core::Protocol& protocol)
          {
            protocol.setType(0xa1);
            protocol.setOption(m_priv->m_option.to_ulong());
            protocol.setPayload(m_priv->m_bytes);
          },
          [this](core::Protocol& protocol)
          {
          },
          0xa1
    ),
    m_priv{ new Private }
{
}

SetWidgetListMessage::~SetWidgetListMessage()
{}

void SetWidgetListMessage::setTotalMessages(SetWidgetListMessage::TotalMessage total)
{
    m_priv->m_option &= std::bitset<8>("11110011");
    m_priv->m_option |= std::bitset<8>(static_cast<quint8>(total) << 2);
}

SetWidgetListMessage::TotalMessage SetWidgetListMessage::totalMessage() const
{
    std::bitset<8> result = (m_priv->m_option & std::bitset<8>("00001100")) >> 2;
    return static_cast<TotalMessage>(result.to_ulong());
}

void SetWidgetListMessage::setMessageIndex(SetWidgetListMessage::MessageIndex index)
{
    m_priv->m_option &= std::bitset<8>("11111100");
    m_priv->m_option |= std::bitset<8>(static_cast<quint8>(index));
}

SetWidgetListMessage::MessageIndex SetWidgetListMessage::messageIndex() const
{
    std::bitset<8> result = (m_priv->m_option & std::bitset<8>("00000011"));
    return static_cast<MessageIndex>(result.to_ulong());
}

void SetWidgetListMessage::addWidgetPayload(WidgetPayload payload)
{
    m_priv->m_bytes.push_back(payload.id());
    m_priv->m_bytes.push_back(payload.payload());
}

QList<WidgetPayload> SetWidgetListMessage::widgetPayload() const
{
    QList<WidgetPayload> list;

    for(int i = 0; m_priv->m_bytes.size() > i;) {
        uint8_t id = m_priv->m_bytes.at(i++);
        uint8_t data = m_priv->m_bytes.at(i++);
        WidgetPayload payload(id, data);
        list.append(payload);
    }

    return list;
}

} // namespace qmwp
