#ifndef AXIS_H
#define AXIS_H

#include <cstdint>
#include "EnumAxis.h"

/**
 * @class Axis
 * @brief Holds the relevant data for every axis.
 */
class Axis
{
    public:
    /// Constructor
    Axis(AXIS id, float minDegrees, float maxDegrees, float offset, float goal, float step, bool special, uint16_t aMaxSpeed);
    
    /// Getters
    AXIS getId();
    float getMinDegrees();
    float getMaxDegrees();
    int32_t getOffset();
    float getGoal();
    float getStep();
    bool getSpecial();
    uint16_t getMaxSpeed();

    // Setters
    void setGoal(float position);
    void setStep(float nStep);

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
    // Amount the ax need to make next step.
    float step;
    // Has a special middlepoint.
    bool special;
    // The maximum speed of the servo in ms/60°.
    const uint16_t cMaxSpeed;
};
#endif /* AXIS_H */