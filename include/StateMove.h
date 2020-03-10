
#ifndef STATEMOVE_H
#define STATEMOVE_H

#include "HighLevelDriver.h"
#include "State.h"

class StateMove : public State
{
private:
    /* data */
    HighLevelDriver& context;
public:
    void entry();
    bool doActivity();
    void exit();
    void handleEvent(Event& event);
   explicit  StateMove(HighLevelDriver& context);
    ~StateMove();
};
#endif /* STATEMOVE_H */
