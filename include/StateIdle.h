
#ifndef STATEIDLE_H
#define STATEIDLE_H
#include "HighLevelDriver.h"
#include "State.h"

/**
 * @class StateIdle
 * @brief Derives from State.
 */
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
   explicit  StateIdle(HighLevelDriver& context);
    ~StateIdle();
};
#endif /* STATEIDLE_H */
