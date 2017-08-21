#ifndef OBSERVEDESIGN_H_INCLUDED
#define OBSERVEDESIGN_H_INCLUDED

#include <string>
#include <map>
#include <list>
#include <iostream>

using namespace std;

typedef enum
{
    Event_Invalid = 0,
    Event_Login = 1,
    Event_Logout = 2,
}EVENT_ID;


struct MyEvent{
    EVENT_ID mEventId;
    int mUniqueIndex;

    MyEvent(EVENT_ID eventId, int uniqueIndex):
    mEventId(eventId),
    mUniqueIndex(uniqueIndex){

    }

    bool operator == (const MyEvent & rhs){
        return mEventId == rhs.mEventId;
    }

    bool operator < (const MyEvent & rhs) const;
};

struct LoginEvent: public MyEvent{
public:
    LoginEvent(EVENT_ID eventId, int uniqueIndex):
    MyEvent(eventId, uniqueIndex){

    }
};

struct LogoutEvent: public MyEvent{
public:
    LogoutEvent(EVENT_ID eventId, int uniqueIndex):
    MyEvent(eventId, uniqueIndex){
    }
};


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
    EventEngine(){

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


void fireEvent(MyEvent pEvent){
    EventEngine::getInstance()->fire(pEvent);
}
EventEngine* EventEngine::mInstance = NULL;


//观察者(建立该类的虚函数是为了让继承自它的类具体实现该虚函数，以便于在事件管理器的代码编写，事件触发时，直接调用CallBack()函数)
struct MyEntity
{
public:
    MyEntity(int pId):mId(pId){}
    virtual void CallBack() = 0;
    void subscribe(MyEvent pEvent){
        EventEngine::getInstance()->Attach(pEvent, this);
    }

    void unSubScribe(MyEvent pEvent){
        EventEngine::getInstance()->Detach(pEvent);
    }
    int getId(){return mId;}
private:
    int mId;
};

struct Hero: public MyEntity{
public:
    Hero(int pId):MyEntity(pId){}
    void CallBack(){
        cout <<"Hero: "<<getId() << " CallBack"<< endl;
    }
};

struct Monster: public MyEntity{
public:
    Monster(int pId):MyEntity(pId){}
    void CallBack(){
        cout << "Monster: "<<getId() <<" CallBack"<< endl;
    }
};

#endif // OBSERVEDESIGN_H_INCLUDED
