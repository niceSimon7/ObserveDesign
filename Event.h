#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include "Enum.h"

struct MyEvent
{
    EVENT_ID mEventId;
    int mUniqueIndex;

    MyEvent(EVENT_ID eventId, int uniqueIndex):
        mEventId(eventId),
        mUniqueIndex(uniqueIndex)
    {

    }

    bool operator == (const MyEvent & rhs)
    {
        return mEventId == rhs.mEventId;
    }

    bool operator < (const MyEvent & rhs) const
    {
        return mEventId < rhs.mEventId;
    }
};


struct LoginEvent: public MyEvent
{
public:
    LoginEvent(EVENT_ID eventId, int uniqueIndex):
        MyEvent(eventId, uniqueIndex)
    {
    }
};


struct LogoutEvent: public MyEvent
{
public:
    LogoutEvent(EVENT_ID eventId, int uniqueIndex):
        MyEvent(eventId, uniqueIndex)
    {
    }
};

#endif // EVENT_H_INCLUDED
