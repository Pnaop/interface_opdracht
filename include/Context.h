#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <vector>
#include "State.h"
class Context
{
protected:
    Context(/* args */){};
    virtual ~Context(){};
    std::vector<Event> events;
    std::shared_ptr<State> currentState;

public:
    virtual void setCurrentState(const std::shared_ptr<State>& nState)=0;

  
};

#endif /* CONTEXT_H */