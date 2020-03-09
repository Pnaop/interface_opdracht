
#ifndef STATEIDLE_H
#define STATEIDLE_H
#include "HighLevelDriver.h"
#include "State.h"

class StateIdle : public State
{
private:
    /* data */
    HighLevelDriver& context;
public:
    void entry();
    bool doActivity();
    void exit();
    void handleEvent(Event& event);
    StateIdle(HighLevelDriver& context);
    ~StateIdle();
};
#endif /* STATEIDLE_H */
