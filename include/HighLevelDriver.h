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

  /** @brief Predefined message to move to Park position.
   * @return moveGoal - converted goal for the action
   **/
  interface_opdracht::moveGoal moveToPark();
  /**
   * @brief Handles the request so that the message is parsed correctly.
  ** @param goal const moveGoalConstPtr to parse 
  **/
  void parseCurrentGoal(const interface_opdracht::moveGoalConstPtr &goal);
  /**
  * @brief Checks whether the requested positions are valid.
  * @param goal const moveGoalConstPtr to validate 
  * @return bool - is the goal valid
  **/ 
  bool validateGoal(const interface_opdracht::moveGoalConstPtr &goal);
  /** @brief function that will be called by the service emergency
   * @param  req emergency servicerequest
   * @param res emergency serviceresponse
   * @return bool - is the requesthandled 
   **/ 
  bool emergency(interface_opdracht::emergency::Request &reg , interface_opdracht::emergency::Response &res);
  /** @brief callback execute for rosAction
  * @param goal const moveGoalConstPtr to set the goal for the action 
  **/
  void executeCB(const interface_opdracht::moveGoalConstPtr &goal);
  /// State transition.
  void setCurrentState(const std::shared_ptr<State>& nState);
  /** @brief adds a Event  to the event array.
   *  @param event The event that needs to be triggered   
   **/
  void addEvent(Event& event);
  /** @brief Run the statemachine.
   *  
   * */
  void run();
};
#endif /* HIGHLEVELDRIVER_H */
