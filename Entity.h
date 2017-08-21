#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "EventEngine.h"
#include <iostream>

using namespace std;

//观察者(建立该类的虚函数是为了让继承自它的类具体实现该虚函数，以便于在事件管理器的代码编写，事件触发时，直接调用CallBack()函数)
struct MyEntity
{
public:
    MyEntity(int pId):mId(pId) {}
    virtual void CallBack() = 0;
    void subscribe(MyEvent pEvent);  //注册

    void unSubScribe(MyEvent pEvent); //取消注册
    int getId()
    {
        return mId;
    }
private:
    int mId;
};

struct Hero: public MyEntity
{
public:
    Hero(int pId):MyEntity(pId) {}
    void CallBack()
    {
        cout <<"Hero: "<<getId() << " CallBack"<< endl;
    }
};

struct Monster: public MyEntity
{
public:
    Monster(int pId):MyEntity(pId) {}
    void CallBack()
    {
        cout << "Monster: "<<getId() <<" CallBack"<< endl;
    }
};

#endif // ENTITY_H_INCLUDED
