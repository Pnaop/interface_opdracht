
#ifndef STATEMOVE_H
#define STATEMOVE_H
#include <chrono>
#include "HighLevelDriver.h"
#include "State.h"

class StateMove : public State
{
private:

    std::chrono::high_resolution_clock::time_point start;/* data */
    HighLevelDriver& context;
public:
    void entry();
    bool doActivity();
    void exit();
    void handleEvent(Event& event);
    STATES getStateId();
   explicit  StateMove(HighLevelDriver& context);
    ~StateMove();
};
#endif /* STATEMOVE_H */
