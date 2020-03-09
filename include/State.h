#ifndef STATE_H
#define STATE_H
#include "Event.h"
class Context;
class State
{
public:
   virtual void handleEvent(Event& event) = 0;
   virtual void entry() = 0 ;
   virtual bool doActivity() = 0;
   virtual void exit() = 0; 
protected:
   State(){}
   virtual ~State(){}
};

#endif