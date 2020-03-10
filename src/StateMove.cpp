#include "../include/StateMove.h"
#include "../include/StateEmergency.h"
#include "../include/StateIdle.h"

StateMove::StateMove(HighLevelDriver& context):context(context)
{

}

StateMove::~StateMove()
{

}

void StateMove::handleEvent(Event& event)
{
    switch (event.getEventType())
    {
        case EVENT_NEW_GOAL:
        case EVENT_GOAL_DONE:
        {
            if(EVENT_GOAL_DONE != event.getEventType())
            {
                Event e(EVENT_NEW_GOAL);
                context.addEvent(e);
            }
     
           std::shared_ptr<State> ptr = std::make_shared<StateIdle>(context);
        }
        break;
        case EVENT_EMERGENCY:
        default:
        {   
            std::shared_ptr<StateEmergency> ptr = std::make_shared<StateEmergency>(context);
            context.setCurrentState(ptr);
 
        }     
        break;
    }
}

void StateMove::entry()
{
    std::cout << "entry Move" << std::endl;

}

bool StateMove::doActivity()
{
    std::cout << "do Move" << std::endl;

    return true;
}

void StateMove::exit()
{

    std::cout << "exit Move" << std::endl;
}
