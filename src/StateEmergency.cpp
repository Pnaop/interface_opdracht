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
    std::cout << "Entry Emergency" << std::endl;
}

bool StateEmergency::doActivity()
{
    std::cout << "do  Emergency" << std::endl;
    return false;
}

void StateEmergency::exit()
{
    std::cout << "exit  Emergency" << std::endl;
}
