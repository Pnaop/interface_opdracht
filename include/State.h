#ifndef STATE_H
#define STATE_H

#include "Event.h"
enum STATES{
INI,
IDLE,
MOVE,
EMERGENCY
};
class State
{
public:
   virtual STATES getStateId() = 0;
   virtual void handleEvent(Event& event) = 0;
   virtual void entry() = 0 ;
   virtual bool doActivity() = 0;
   virtual void exit() = 0; 
protected:
   State(){}
   virtual ~State(){}
   STATES id;
};

#endif /* STATE_H */