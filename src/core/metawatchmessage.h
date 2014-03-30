#ifndef QMWP_CORE_METAWATCHMESSAGE_H
#define QMWP_CORE_METAWATCHMESSAGE_H

#include <boost/tr1/functional.hpp>

#include "core/metawatchprotocol.h"

namespace qmwp {
namespace core {

class Message
{
public:
    Message();
    virtual ~Message();

    Protocol createProtocol() const;
    int responseType() const;
    void handle(Protocol& protocol);

protected:
    Message(std::tr1::function<void (Protocol&)> request,
            std::tr1::function<void (Protocol&)> response,
            int responseType);

private:
    std::tr1::function<void (Protocol&)> m_requestHandler;
    std::tr1::function<void (Protocol&)> m_responseHandler;
    int m_responseType;
};

} // namespace core
} // namespace qmwp

#endif // QMWP_CORE_METAWATCHMESSAGE_H
