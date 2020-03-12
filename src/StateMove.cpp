#include "../include/StateMove.h"
#include "../include/StateEmergency.h"
#include "../include/StateIdle.h"
#include <interface_opdracht/moveAction.h>

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
    ROS_INFO("STATE: MOVE");
    start = std::chrono::high_resolution_clock::now();
    RobotLD& arm = context.getArm();
    saveStartPositions(arm.getAxis());
    arm.sendCommand(this->context.getCurrentGoal());
}

bool StateMove::doActivity()
{
    
    actionlib::SimpleActionServer<interface_opdracht::moveAction>& as_ = this->context.getActionServer();
    interface_opdracht::moveFeedback& feedback_ = context.getFeedback();
     if(as_.isPreemptRequested() || !ros::ok())
     {
       RobotLD& arm = context.getArm();
       arm.sendStopCommand();
       setcurrentPositionsAsGoal(arm.getAxis(),std::chrono::duration<double,std::milli>(std::chrono::high_resolution_clock::now() - start).count(),context.getCurrentGoal().time);
       feedback_.sequence.clear();         
       as_.setPreempted();
       Event e(EVENT_NEW_GOAL);
       context.addEvent(e);
     
     }
     else
     {
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
            feedback_.sequence.push_back(std::chrono::duration<double,std::milli>(std::chrono::high_resolution_clock::now() - start).count());
            as_.publishFeedback(feedback_);
     
        }
     }
    
    return true;
}
void StateMove::setcurrentPositionsAsGoal(std::vector<Axis>& axis,double currentTime,double endTime)
{
    for(uint8_t i = 0; i < axis.size(); ++i)
    {
        axis[i].setGoal(calculatePosition(startPositions[i],axis[i].getGoal(),currentTime,endTime));
    }
}
void StateMove::saveStartPositions(std::vector<Axis>& axis)
{
    startPositions.clear();
    for(uint8_t i = 0; i < axis.size(); ++i)
    {
       startPositions.push_back(axis[i].getGoal());
    }
}
float StateMove::calculatePosition(float startPosition,float goal,double currentTime,double endTime)
{
            float ratioProgress = currentTime/endTime;
            
            float distance = goal - startPosition;
            float returnValue = startPosition + (distance * ratioProgress);
            return returnValue;
}

void StateMove::exit()
{

    std::cout << "exit Move" << std::endl;
}
