#ifndef EVENTENGINE_H_INCLUDED
#define EVENTENGINE_H_INCLUDED

#include <string>
#include <map>
#include <list>
#include <iostream>
#include "Enum.h"
#include "Event.h"
#include "Entity.h"

using namespace std;

struct MyEntity;

struct EventEngine
{
public:
    void Attach(MyEvent pEvent, MyEntity *pEntity);
    void Detach(MyEvent pEvent);
    void DetachAll();
    void fire(MyEvent pEvent);

private:
    typedef list<MyEntity* > EventList;
    typedef map<EVENT_ID, EventList > EventListMap;
    typedef EventList::iterator EventListIter;
    typedef EventListMap::iterator EventListMapIter;
    EventListMap m_map;
    static EventEngine *mInstance;
    EventEngine()
    {

    }
public:
    static EventEngine* getInstance()
    {
        if(mInstance == NULL)
        {
            mInstance = new EventEngine();
        }
        return mInstance;
    }
};


#endif // EVENTENGINE_H_INCLUDED
