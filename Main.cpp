#include "ObserveDesign.h"
#include "Event.h"
#include "Entity.h"
#include "EventEngine.h"
#include <iostream>

using namespace std;

void fireEvent(MyEvent pEvent){
    EventEngine::getInstance()->fire(pEvent);
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
