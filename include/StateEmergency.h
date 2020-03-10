#ifndef STATE_EMERGENCY_H
#define STATE_EMERGENCY_H

#include "State.h"
#include "HighLevelDriver.h"

class StateEmergency : public State
{
private:
    /* data */
    HighLevelDriver& context;


public:
    void entry();
    bool doActivity();
    void exit();
    void handleEvent(Event& event);
   explicit StateEmergency(HighLevelDriver& context);
    ~StateEmergency();
};
#endif /* STATE_EMERGENCY */
