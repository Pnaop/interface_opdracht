#include "../include/HighLevelDriver.h"
#include "../include/Context.h"
#include "../include/EnumMode.h"
#include "../include/StateIni.h"
#include "ros/ros.h"
#include <chrono>
#include <thread>

HighLevelDriver::HighLevelDriver(std::string& rosNodeName):as_(nh_,"move_arm", boost::bind(&HighLevelDriver::executeCB,this, _1),false)
{
  /// Start the actionserver.
  as_.start();
  /// Initialise pointer for statemachine.
  std::shared_ptr<State> tempS = std::make_shared<StateIni>(*this);
  // Set up the service to call the emergency stop.
  this->server_service = nh_.advertiseService("emergency", &HighLevelDriver::emergency, this);
  /// Set the state to Initialise.
  setCurrentState(tempS);
}

HighLevelDriver::~HighLevelDriver()
{
}

void HighLevelDriver::setCurrentState(const std::shared_ptr<State>& nState)
{
  /// Exit the currentState en transition to new state.
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
  /// Call the correct function for the selected mode.
  switch (goal->modeType)
  {
  case FREEMODE:
    currentGoal = *goal;
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
std::string HighLevelDriver::eventEnumToString(EVENT_TYPE e)
{
  std::string returnValue = "";
  switch(e)
  {
    case EVENT_EMERGENCY:
          returnValue = EVENTEMERGENCY;
    break;
    case EVENT_NEW_GOAL:
          returnValue = EVENTNEWGOAL;
    break;
    case EVENT_GOAL_DONE:
          returnValue = EVENTGOALDONE;
    break;
    default:
          returnValue = EVENTINI;
    break;
  }
  return returnValue;
}
interface_opdracht::moveGoal HighLevelDriver::moveToUp()
{
  interface_opdracht::moveGoal tempGoal;

  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::BASE_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::SHOULDER)));
  tempGoal.move_to.push_back(2);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::ELBOW)));
  tempGoal.move_to.push_back(17);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST)));
  tempGoal.move_to.push_back(0);
  tempGoal.axis.push_back(std::stoi(std::to_string(AXIS::WRIST_ROTATION)));
  tempGoal.move_to.push_back(0);
  tempGoal.time = 0;
  return tempGoal;
}

bool HighLevelDriver::validateGoal(const interface_opdracht::moveGoalConstPtr &goal)
{
  /// If the boolean is still true after the test, the goal is valid.
  bool result = true;

  /// Loop over all selected axes.
  for(uint8_t i = 0; i < goal->axis.size(); ++i)
  {
    /// Check if the goal for each axis is valid.
    result = arm.checkMoveValid(goal->axis[int(i)], goal->move_to[goal->axis[i]], goal->time);
    if(!result)
    {
      return result;
    }
  } 

  /// True when all goals are valid.
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
  if(validateGoal(goal))
  {
      Event ev(EVENT_NEW_GOAL);
      addEvent(ev);
  }
  else
  {     /*invalid goal*/
    Event e(EVENT_EMERGENCY);
    addEvent(e);
  }

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
      ROS_DEBUG("EVENT: {%s}" ,eventEnumToString(events[0].getEventType()).c_str());
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