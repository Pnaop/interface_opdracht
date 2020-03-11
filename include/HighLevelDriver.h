#ifndef HIGHLEVELDRIVER_H
#define HIGHLEVELDRIVER_H

#include <memory>

#include <actionlib/server/simple_action_server.h>

#include <interface_opdracht/moveAction.h>
#include <interface_opdracht/emergency.h>
#include "RobotLD.h"
#include "Context.h"

/**
 * @class HighLevelDriver
 * @brief Handles the ROSnode and communication with LowLevelDriver.
 * 
 * Derives from Context, has statemachine implementation.
 */
class HighLevelDriver : public Context 
{
private:
  /// Handler for the ROSnode.
  ros::NodeHandle nh_;
  /// Server for the moveAction.
  actionlib::SimpleActionServer<interface_opdracht::moveAction> as_;
  /// Message for the current goal.
  interface_opdracht::moveGoal currentGoal;
  /// Message for action feedback.
  interface_opdracht::moveFeedback feedback_;
  /// Message for action result.
  interface_opdracht::moveResult result_;
  /// The ROS server.
  ros::ServiceServer server_service;

  /// Predefined message to move to Ready position.
  interface_opdracht::moveGoal moveToReady();
  /// Predefined message to move to StraightUp position.
  interface_opdracht::moveGoal moveToUp();

  /// Low Level Driver
  RobotLD arm; 
public:
  /// Constructor
  explicit HighLevelDriver(std::string& rosNodeName);
  /// Destructor
  ~HighLevelDriver();

  /// Getters
  interface_opdracht::moveGoal& getCurrentGoal();
  interface_opdracht::moveFeedback& getFeedback();
  RobotLD& getArm(); 
  interface_opdracht::moveResult& getResult();
  actionlib::SimpleActionServer<interface_opdracht::moveAction>& getActionServer();

  /// Predefined message to move to Park position.
  interface_opdracht::moveGoal moveToPark();
  /// Handles the request so that the message is parsed correctly.
  void parseCurrentGoal(const interface_opdracht::moveGoalConstPtr &goal);
  /// Checks whether the requested positions are valid.
  bool validateGoal(const interface_opdracht::moveGoalConstPtr &goal);
  /// Immediatly starts emergency protocol.
  bool emergency(interface_opdracht::emergency::Request &reg , interface_opdracht::emergency::Response &res);
  /// Callback for Low Level Driver.
  void executeCB(const interface_opdracht::moveGoalConstPtr &goal);
  /// State transition.
  void setCurrentState(const std::shared_ptr<State>& nState);
  /// Event transition.
  void addEvent(Event& event);
  /// Run the statemachine.
  void run();
};
#endif /* HIGHLEVELDRIVER_H */
