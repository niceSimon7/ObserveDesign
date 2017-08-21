#include "Entity.h"
#include "EventEngine.h"

void MyEntity::subscribe(MyEvent pEvent){
        EventEngine::getInstance()->Attach(pEvent, this);
    }

void MyEntity::unSubScribe(MyEvent pEvent){
        EventEngine::getInstance()->Detach(pEvent);
    }
