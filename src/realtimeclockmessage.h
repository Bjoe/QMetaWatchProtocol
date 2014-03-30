#ifndef QMWP_REALTIMECLOCKMESSAGE_H
#define QMWP_REALTIMECLOCKMESSAGE_H

#include <boost/tr1/memory.hpp>

#include <QDate>
#include <QTime>
#include <QDateTime>

#include "core/metawatchmessage.h"

namespace qmwp {

class RealTimeClockMessage : public core::Message
{
public:
    RealTimeClockMessage();
    virtual ~RealTimeClockMessage();

    void setDateTime(const QDateTime dateTime);
    void setDate(const QDate date);
    void setTime(const QTime time);

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void septDayOfWeek(int dayOfWeek);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

private:
    class Private;
    std::tr1::shared_ptr<Private> m_priv;
};

} // namespace qmwp

#endif // QMWP_REALTIMECLOCKMESSAGE_H
