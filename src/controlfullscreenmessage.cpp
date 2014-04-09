#include "controlfullscreenmessage.h"

namespace qmwp {

class ControlFullScreenMessage::Private
{
public:
    quint8 m_options = 0;
};

ControlFullScreenMessage::ControlFullScreenMessage(QObject *parent)
    : QObject(parent), Message(
          [this](core::Protocol& protocol)
          {
            protocol.setType(0x42);
            protocol.setOption(m_priv->m_options);
          },
          [this](core::Protocol& protocol)
          {},
          0x42
          ),
      m_priv{ new Private }
{
}

ControlFullScreenMessage::~ControlFullScreenMessage()
{}

bool ControlFullScreenMessage::fullScreenChecked() const
{
    bool result = false;
    if(m_priv->m_options == 0x01) {
        result = true;
    }
    return result;
}

void ControlFullScreenMessage::setFullScreenChecked(bool isFullScreen)
{
    if(isFullScreen) {
        m_priv->m_options = 0x01;
    } else {
        m_priv->m_options = 0x00;
    }
    emit fullScreenChanged();
}

} // namespace qmwp
