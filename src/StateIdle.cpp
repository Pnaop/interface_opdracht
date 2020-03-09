#include "../include/StateIdle.h"

#include<iostream>
StateIdle::StateIdle(HighLevelDriver& context):context(context)
{

}
StateIdle::~StateIdle()
{

}
void StateIdle::handleEvent(Event& event)
{
    //std::shared_ptr<State> ptr = std::make_shared<State>();
    switch (event.id)
    {
    case 1:
        break;
    
    default:
        break;
    }
    
}
void StateIdle::entry()
{
    std::cout << "Entry Idle" << std::endl;
}
bool StateIdle::doActivity()
{
    std::cout << "do Idle" << std::endl;
    Event a;
    a.id=1;
    return false;
}
void StateIdle::exit()
{
    std::cout << "exit Idle" << std::endl;
}
