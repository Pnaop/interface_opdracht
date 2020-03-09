#ifndef AXIS_H
#define AXIS_H

#include <cstdint>
#include "EnumAxis.h"

class Axis
{
    public:
    Axis(AXIS id,float minDegrees,float maxDegrees,float offset , float goal,float step,bool special);
    
    /// get functies
    AXIS getId();
    float getMinDegrees();
    float getMaxDegrees();
    int32_t getOffset();
    float getGoal();
    float getStep();
    bool getSpecial();

    //setters
    void setGoal(float position);
    void setStep(float nStep);

    private:
    // ID OF AX
    AXIS id;
    //SAFETY AX in DEGREES
    float minDegrees;
    float maxDegrees;
    // THE OFFSET
    int32_t offset;
    // current goal off axis
    float goal;
    // amount the ax need to make next step
    float step;
    // has a special middlepoint
    bool special;
};
#endif /* AXIS_H */