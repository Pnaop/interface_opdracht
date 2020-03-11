
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
    std::vector<float> startPositions;
    void setcurrentPositionsAsGoal(std::vector<Axis>& axis,double currentTime,double endTime);
    void saveStartPositions(std::vector<Axis>& axis);
    float calculatePosition(float startPosition,float goal,double currentTime,double endTime);
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
