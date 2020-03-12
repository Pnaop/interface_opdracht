#include "../include/StateEmergency.h"
#include<iostream>

StateEmergency::StateEmergency(HighLevelDriver& context):context(context)
{
}

StateEmergency::~StateEmergency()
{
}

void StateEmergency::handleEvent(Event& event)
{
}

void StateEmergency::entry()
{
    this->context.getArm().sendStopCommand();
    actionlib::SimpleActionServer<interface_opdracht::moveAction>& as_ = this->context.getActionServer();
    interface_opdracht::moveResult& result_ = this->context.getResult();
    if (as_.isActive())
    {
      result_.sequence.push_back(0);
      as_.setAborted(result_);
    }
    ROS_INFO("STATE : EMERGENCY");

}

bool StateEmergency::doActivity()
{
    return false;
}

void StateEmergency::exit()
{
    std::cout << "exit  Emergency" << std::endl;
}
