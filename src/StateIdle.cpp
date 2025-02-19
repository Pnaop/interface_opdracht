#include "../include/StateIdle.h"
#include "../include/StateMove.h"
#include "../include/StateEmergency.h"
#include<iostream>

StateIdle::StateIdle(HighLevelDriver& context):context(context)
{
}

StateIdle::~StateIdle()
{
}

void StateIdle::handleEvent(Event& event)
{
    switch (event.getEventType())
    {
        case EVENT_NEW_GOAL:
        {
            std::shared_ptr<State> ptr = std::make_shared<StateMove>(context);
            context.setCurrentState(ptr);
        }  
        break;
        case EVENT_EMERGENCY:
        default:
        {
            std::shared_ptr<State> ptr = std::make_shared<StateEmergency>(context);
            context.setCurrentState(ptr);
        }
        break;
    }
}

void StateIdle::entry()
{
    ROS_INFO("STATE: IDLE");
}

bool StateIdle::doActivity()
{
    return false;
}

void StateIdle::exit()
{
    std::cout << "exit Idle" << std::endl;
}
