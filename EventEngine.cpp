#include "EventEngine.h"

EventEngine* EventEngine::mInstance = NULL;

void EventEngine::Attach(MyEvent pEvent, MyEntity* pEntity)
{
    EventListMap::iterator iter = m_map.find(pEvent.mEventId);
    if(iter == m_map.end())
    {
        list<MyEntity* > entityList;
        entityList.push_front(pEntity);
        m_map.insert(EventListMap::value_type(pEvent.mEventId, entityList));
    }
    else
    {
        (iter->second).push_front(pEntity);
    }
}

void EventEngine::Detach(MyEvent pEvent)
{
    if(m_map.empty())
    {
        return;
    }
    EventListMap::iterator mIter = m_map.find(pEvent.mEventId);
    if(mIter != m_map.end())
    {
        EventListIter lIter = (mIter->second).begin();
        for(; lIter != (mIter->second).end(); ++lIter)
        {
            if((*lIter)->getId() == pEvent.mUniqueIndex)
            {
                (mIter->second).erase(lIter);
                return ;
            }
        }
    }
}

void EventEngine::DetachAll()
{
    EventListMapIter mIter  = m_map.begin();
    for(; mIter != m_map.end(); ++mIter )
    {
        mIter->second.clear();
    }
    m_map.clear();
}

void EventEngine::fire(MyEvent pEvent)
{
    EventListMapIter mIter = m_map.find(pEvent.mEventId);
    if(mIter == m_map.end())
        return;
    EventListIter lIter = (mIter->second).begin();
    for(; lIter != (mIter->second).end(); ++lIter)
    {
        if((*lIter)->getId() == pEvent.mUniqueIndex)
        {
            (*lIter)->CallBack();
            return;
        }
    }
}
