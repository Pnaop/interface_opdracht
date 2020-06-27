#include "../include/Event.h"

Event::Event(EVENT_TYPE eventType):eventType(eventType)
{

}

Event::~Event()
{

}

EVENT_TYPE Event::getEventType() const
{
    return eventType;
}