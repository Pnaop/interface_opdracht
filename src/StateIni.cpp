#include "../include/StateIni.h"
#include "../include/StateIdle.h"
#include <iostream>

StateIni::StateIni(HighLevelDriver& context):context(context)
{

}

StateIni::~StateIni()
{

}

void StateIni::handleEvent(Event& event)
{
    std::shared_ptr<State> idle = std::make_shared<StateIdle>(context);
    switch (event.id)
    {
    case 1:
          context.setCurrentState(idle);
        break;
    
    default:
        break;
    }
    
}
void StateIni::entry()
{
    std::cout << "Entry Ini" << std::endl;
}

bool StateIni::doActivity()
{
    std::cout << "do Ini" << std::endl;
    
    Event a;
    a.id=1;
    handleEvent(a);
    return false;
}

void StateIni::exit()
{    
    std::cout << "Exit Ini" << std::endl;
}
