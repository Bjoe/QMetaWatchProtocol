#ifndef QMWP_WRITELCDBUFFERMESSAGE_H
#define QMWP_WRITELCDBUFFERMESSAGE_H

#include <memory>

#include "core/metawatchmessage.h"

namespace qmwp {

class WriteLcdBufferMessage : public core::Message
{
public:
    WriteLcdBufferMessage();
    virtual ~WriteLcdBufferMessage();

    void test();

private:
    class Private;
    std::unique_ptr<Private> m_priv;
};

} // namespace qmwp

#endif // QMWP_WRITELCDBUFFERMESSAGE_H
