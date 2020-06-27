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
    Axis(AXIS id, float minDegrees, float maxDegrees, float offset, float goal, bool special, uint16_t aMaxSpeed);
    
    /// Getters
    AXIS getId() const;
    float getMinDegrees() const;
    float getMaxDegrees() const;
    int32_t getOffset() const;
    float getGoal() const;
    bool getSpecial() const;
    uint16_t getMaxSpeed() const;

    // Setters
    void setGoal(float goal);

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