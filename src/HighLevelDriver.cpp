#include "../include/HighLevelDriver.h"
#include "../include/Context.h"
#include "../include/StateIni.h"
#include "ros/ros.h"

HighLevelDriver::HighLevelDriver()
{
    std::shared_ptr<State> tempS = std::make_shared<StateIni>(*this);
    setCurrentState(tempS);
}

HighLevelDriver::~HighLevelDriver()
{
}

void HighLevelDriver::setCurrentState(std::shared_ptr<State>& nState)
{
    if(currentState)
    {
        currentState->exit();
    }
    currentState = nState;
    currentState->entry();
}

void HighLevelDriver::addEvent(Event a)
{
    this->events.push_back(a);
}

void HighLevelDriver::run()
{
       while(!ros::ok())
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
        }
}