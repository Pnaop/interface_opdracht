#include "../include/HighLevelDriver.h"
#include "../include/Context.h"
#include "../include/StateIni.h"
#include "ros/ros.h"
#include <chrono>
#include <thread>

HighLevelDriver::HighLevelDriver(std::string& rosNodeName):as_(nh_,"move_arm", boost::bind(&HighLevelDriver::executeCB,this, _1),false)
{
    as_.start();
    std::shared_ptr<State> tempS = std::make_shared<StateIni>(*this);
    this->server_service = nh_.advertiseService("emergency", &HighLevelDriver::emergency, this);
    setCurrentState(tempS);
}

HighLevelDriver::~HighLevelDriver()
{
}

void HighLevelDriver::setCurrentState(const std::shared_ptr<State>& nState)
{
    if(currentState)
    {
        currentState->exit();
    }
    currentState = nState;
    currentState->entry();
}

void HighLevelDriver::addEvent(Event& a)
{
    this->events.push_back(a);
}
interface_opdracht::moveFeedback& HighLevelDriver::getFeedback()
{
    return this->feedback_;
}
interface_opdracht::moveResult& HighLevelDriver::getResult()
{
    return this->result_;
}

interface_opdracht::moveGoal& HighLevelDriver::getCurrentGoal()
{
    return currentGoal;
}
void HighLevelDriver::executeCB(const interface_opdracht::moveGoalConstPtr &goal)
{
      // if(true) /// validate goal(
        //{
            
             this->currentGoal = *goal;
             Event ev(EVENT_NEW_GOAL);
             addEvent(ev);
            while (as_.isActive()){};
        //}
}
actionlib::SimpleActionServer<interface_opdracht::moveAction>& HighLevelDriver::getActionServer()
{
    return as_;
}
bool HighLevelDriver::emergency(interface_opdracht::emergency::Request &reg, interface_opdracht::emergency::Response &res)
{
  if (reg.error)
  {
      Event e(EVENT_EMERGENCY);
      addEvent(e);
      res.result = true;
   }

  return true;
}
void HighLevelDriver::run()
{  
       while(ros::ok())
       {
            if(!events.empty())
            {
                currentState->handleEvent(events[0]);
                events.erase(events.begin());
            }
            else
            {
              currentState->doActivity();
            }
           ros::spinOnce();
        }
}