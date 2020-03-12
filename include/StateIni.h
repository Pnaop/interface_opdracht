
#ifndef STATEINI_H
#define STATEINI_H
#include "State.h"
#include "HighLevelDriver.h"

/**
 * @class StateIni
 * @brief Derives from State and implements the functionalities for initialisation.
 */
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
   explicit  StateIni(HighLevelDriver& context);
    ~StateIni();
};
#endif /* STATEINI_H */
