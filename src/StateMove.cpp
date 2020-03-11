#include "../include/StateMove.h"
#include "../include/StateEmergency.h"
#include "../include/StateIdle.h"
#include <interface_opdracht/moveAction.h>

StateMove::StateMove(HighLevelDriver& context):context(context)
{
    id = STATES::MOVE;
}

StateMove::~StateMove()
{

}
STATES StateMove::getStateId()
{
      return id;
}

void StateMove::handleEvent(Event& event)
{
    switch (event.getEventType())
    {
        case EVENT_NEW_GOAL:
        case EVENT_GOAL_DONE:
        {
           std::shared_ptr<State> ptr = std::make_shared<StateIdle>(context);
           context.setCurrentState(ptr);
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
    start = std::chrono::high_resolution_clock::now();
    context.getArm().sendCommand(this->context.getCurrentGoal());
}

bool StateMove::doActivity()
{
    
    actionlib::SimpleActionServer<interface_opdracht::moveAction>& as_ = this->context.getActionServer();
    interface_opdracht::moveFeedback& feedback_ = context.getFeedback();
     if(as_.isPreemptRequested() || !ros::ok())
     {
       context.getArm().sendStopCommand();
       feedback_.sequence.clear();         
       as_.setPreempted();
       Event e(EVENT_NEW_GOAL);
       context.addEvent(e);
     
     }
    if(std::chrono::duration<double,std::milli>(std::chrono::high_resolution_clock::now() - start).count() >= this->context.getCurrentGoal().time)
    {
       interface_opdracht::moveResult& result_ = context.getResult();
       result_.sequence = feedback_.sequence;
       feedback_.sequence.clear();
       as_.setSucceeded(result_);
       Event e(EVENT_GOAL_DONE);
       context.addEvent(e);
    }
    else
    {
            /* just time feedback*/
            
            feedback_.sequence.push_back(std::chrono::duration<double,std::milli>(std::chrono::high_resolution_clock::now() - start).count());
            as_.publishFeedback(feedback_);
     
    }
    
    return true;
}

void StateMove::exit()
{

    std::cout << "exit Move" << std::endl;
}
