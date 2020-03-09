#include "State.h"

#ifndef CONTEXT_H
#define CONTEXT_H
#include <memory>
#include <vector>
class Context
{

protected:
std::vector<Event> events;
 Context(/* args */){};
 virtual ~Context(){};
std::shared_ptr<State> currentState;
public:

  
};

#endif