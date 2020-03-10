#include "Context.h"

#ifndef HIGHLEVELDRIVER_H
#define HIGHLEVELDRIVER_H
#include <memory>
#include <actionlib/server/simple_action_server.h>
#include <interface_opdracht/moveAction.h>
#include <interface_opdracht/emergency.h>

class HighLevelDriver : public Context 
{
private:
    /* data */
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<interface_opdracht::moveAction> as_;
  interface_opdracht::moveGoal currentGoal;
   // create messages that are used to published feedback/result
  interface_opdracht::moveFeedback feedback_;
  interface_opdracht::moveResult result_;
  ros::ServiceServer server_service;
public:
    explicit HighLevelDriver(std::string& rosNodeName);
    ~HighLevelDriver();
    interface_opdracht::moveGoal& getCurrentGoal();
    interface_opdracht::moveFeedback& getFeedback();
    interface_opdracht::moveResult& getResult();
    actionlib::SimpleActionServer<interface_opdracht::moveAction>& getActionServer();
    bool emergency(interface_opdracht::emergency::Request &reg , interface_opdracht::emergency::Response &res);
    void executeCB(const interface_opdracht::moveGoalConstPtr &goal);
    void setCurrentState(const std::shared_ptr<State>& nState);
    void addEvent(Event& event);
    void run();
};
#endif /* HIGHLEVELDRIVER_H */
