#include "ObserveDesign.h"

bool MyEvent::operator<(const MyEvent & rhs) const{
    return mEventId < rhs.mEventId;
}

void EventEngine::Attach(MyEvent pEvent, MyEntity* pEntity){
    EventListMap::iterator iter = m_map.find(pEvent.mEventId);
    if(iter == m_map.end())
    {
        list<MyEntity* > entityList;
        entityList.push_front(pEntity);
        m_map.insert(EventListMap::value_type(pEvent.mEventId, entityList));
    }else{
        (iter->second).push_front(pEntity);
    }
}

void EventEngine::Detach(MyEvent pEvent){
    if(m_map.empty()){
        return;
    }
    EventListMap::iterator mIter = m_map.find(pEvent.mEventId);
    if(mIter != m_map.end()){
        EventListIter lIter = (mIter->second).begin();
        for(;lIter != (mIter->second).end(); ++lIter){
            if((*lIter)->getId() == pEvent.mUniqueIndex){
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

int main()
{
    Hero * h1 = new Hero(1);
    Hero * h2 = new Hero(2);

    Monster * m1 = new Monster(3);
    Monster * m2 = new Monster(4);

    LoginEvent l1(Event_Login, h1->getId());
    LoginEvent l2(Event_Logout, h1->getId());
    LogoutEvent l3(Event_Login, m1->getId());
    LogoutEvent l4(Event_Logout, m2->getId());

    h1->subscribe(l1);
    h1->subscribe(l2);
    m1->subscribe(l3);
    m1->subscribe(l4);

    fireEvent(l1);
    fireEvent(l3);

    return 0;
}
