#include "../include/HighLevelDriver.h"
#include "../include/Context.h"
#include "../include/EnumMode.h"
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
RobotLD& HighLevelDriver::getArm()
{
    return arm;
}
void HighLevelDriver::parseCurrentGoal(const interface_opdracht::moveGoalConstPtr &goal)
{
    switch (goal->modeType)
    {
    case FREEMODE:
      if (validateGoal(goal))
      {
        currentGoal = *goal;
      }
      else
      {
          /*invalid goal*/
          Event e(EVENT_EMERGENCY);
          addEvent(e);
      }
      break;
    case PROGRAM_UP:
      currentGoal = this->moveToUp();
      break;
    case PROGRAM_READY:
      currentGoal = this->moveToReady();
      break;
    case PROGRAM_PARK:
      currentGoal = this->moveToPark();
      break;
    default:
      currentGoal = this->moveToReady();
      break;
    }
    currentGoal.time = goal->time;
}
interface_opdracht::moveGoal HighLevelDriver::moveToReady()
{
  interface_opdracht::moveGoal tempGoal;
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::BASE_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::SHOULDER)));
  tempGoal.move_to.push_back(27);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::ELBOW)));
  tempGoal.move_to.push_back(99);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST)));
  tempGoal.move_to.push_back(-14);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.time = 0;
  return tempGoal;
}

interface_opdracht::moveGoal HighLevelDriver::moveToPark()
{
  interface_opdracht::moveGoal tempGoal;

  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::BASE_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::SHOULDER)));
  tempGoal.move_to.push_back(50);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::ELBOW)));
  tempGoal.move_to.push_back(135);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST)));
  tempGoal.move_to.push_back(-90);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.time = 0;
  return tempGoal;
}

interface_opdracht::moveGoal HighLevelDriver::moveToUp()
{
  interface_opdracht::moveGoal tempGoal;

  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::BASE_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::SHOULDER)));
  tempGoal.move_to.push_back(2);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::ELBOW)));
  tempGoal.move_to.push_back(15);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST)));
  tempGoal.move_to.push_back(0);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.time = 0;
  return tempGoal;
}

bool HighLevelDriver::validateGoal(const interface_opdracht::moveGoalConstPtr &goal)
{
  bool result = true;

  for(uint8_t i = 0; i < goal->axis.size(); ++i)
  {
    result = arm.checkMoveValid(goal->axis[int(i)], goal->move_to[goal->axis[i]], goal->time);
  } 

  return result;
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
  parseCurrentGoal(goal);
  Event ev(EVENT_NEW_GOAL);
  addEvent(ev);
  while (as_.isActive()){};
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