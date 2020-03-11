#include "../include/StateIni.h"
#include "../include/StateIdle.h"
#include "../include/StateEmergency.h"
#include <iostream>

StateIni::StateIni(HighLevelDriver& context):context(context)
{
    id = STATES::INI;
}

StateIni::~StateIni()
{
    
}
STATES StateIni::getStateId()
{
      return id;
}

void StateIni::handleEvent(Event& event)
{
   
    switch (event.getEventType())
    {
     case EVENT_INI_DONE:
       { std::shared_ptr<State> ptr = std::make_shared<StateIdle>(context);
        context.setCurrentState(ptr);
       }break;
    
    default:
    { std::shared_ptr<State> ptr = std::make_shared<StateEmergency>(context);
        context.setCurrentState(ptr);
       }
        break;
    }
    
}
void StateIni::entry()
{
    ROS_INFO("STATE: INI");
    interface_opdracht::moveGoal goal = this->context.moveToPark();
    goal.time = 1;
        
    this->context.getArm().sendCommand(goal);

    Event a(EVENT_INI_DONE);
    context.addEvent(a);
}

bool StateIni::doActivity()
{
    std::cout << "do Ini" << std::endl;
    return false;
}

void StateIni::exit()
{    
    std::cout << "Exit Ini" << std::endl;
}
