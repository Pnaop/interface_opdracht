#ifndef AXIS_H
#define AXIS_H

#include <cstdint>
#include "EnumAxis.h"

class Axis
{
    public:
    Axis(AXIS id, float minDegrees, float maxDegrees, float offset, float goal, bool special, uint16_t aMaxSpeed);
    
    /// Getters
    AXIS getId();
    float getMinDegrees();
    float getMaxDegrees();
    int32_t getOffset();
    float getGoal();
    bool getSpecial();
    uint16_t getMaxSpeed();

    // Setters
    void setGoal(float position);

    private:
    // IS of the axis.
    AXIS id;
    // Limits of axis in degrees.
    float minDegrees;
    float maxDegrees;
    // THE OFFSET
    int32_t offset;
    // Current goal of axis.
    float goal;
    // Has a special middlepoint.
    bool special;
    // The maximum speed of the servo in ms/60°.
    const uint16_t cMaxSpeed;
};
#endif /* AXIS_H */