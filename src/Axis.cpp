#include "../include/Axis.h"

Axis::Axis(AXIS id, float minDegrees, float maxDegrees, float offset, float goal, float step, bool special, uint16_t aMaxSpeed):id(id), minDegrees(minDegrees), maxDegrees(maxDegrees)
, offset(offset), goal(goal), step(step), special(special), cMaxSpeed(aMaxSpeed)
{

}

AXIS Axis::getId()
{
    return this->id;
}

float Axis::getMinDegrees()
{
    return this->minDegrees;
}

float Axis::getMaxDegrees()
{
    return this->maxDegrees;
}

int32_t Axis::getOffset()
{
    return this->offset;
}

float Axis::getGoal()
{

    return this->goal;
}

float Axis::getStep()
{
    return this->step;
}

bool Axis::getSpecial()
{
    return this->special;
}

uint16_t Axis::getMaxSpeed()
{
    return this->cMaxSpeed;
}

//setters
void Axis::setGoal(float goal)
{
    this->goal = goal;
}

void Axis::setStep(float nStep)
{   
    this->step = nStep;
}