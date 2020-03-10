
#ifndef STATEINI_H
#define STATEINI_H
#include "State.h"
#include "HighLevelDriver.h"
class StateIni : public State
{
private:
    /* data */
    HighLevelDriver& context;
public:
    void entry();
    bool doActivity();
    void exit();
    void handleEvent(Event& event);
    STATES getStateId();
   explicit  StateIni(HighLevelDriver& context);
    ~StateIni();
};
#endif /* STATEINI_H */
