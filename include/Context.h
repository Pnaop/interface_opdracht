#include "State.h"

#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <vector>

class Context
{
protected:
    Context(/* args */){};
    virtual ~Context(){};
    std::vector<Event> events;
    std::shared_ptr<State> currentState;

public:
    virtual void setCurrentState(std::shared_ptr<State> nState)=0;

  
};

#endif /* CONTEXT_H */