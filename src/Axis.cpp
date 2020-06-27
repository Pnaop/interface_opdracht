#include "../include/Axis.h"

Axis::Axis(AXIS id, float minDegrees, float maxDegrees, float offset, float goal,bool special, uint16_t aMaxSpeed):id(id), minDegrees(minDegrees), maxDegrees(maxDegrees)
, offset(offset), goal(goal), special(special), cMaxSpeed(aMaxSpeed)
{

}

AXIS Axis::getId() const
{
    return this->id;
}

float Axis::getMinDegrees() const
{
    return this->minDegrees;
}

float Axis::getMaxDegrees() const
{
    return this->maxDegrees;
}

int32_t Axis::getOffset() const
{
    return this->offset;
}

float Axis::getGoal() const
{

    return this->goal;
}
bool Axis::getSpecial() const
{
    return this->special;
}

uint16_t Axis::getMaxSpeed() const
{
    return this->cMaxSpeed;
}

//setters
void Axis::setGoal(float goal)
{
    this->goal = goal;
}
