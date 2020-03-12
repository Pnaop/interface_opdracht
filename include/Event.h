#ifndef EVENT_H
#define EVENT_H
enum EVENT_TYPE{
    EVENT_INI_DONE,
    EVENT_NEW_GOAL,
    EVENT_GOAL_DONE,
    EVENT_EMERGENCY
};

/**
 * @class Event
 * @brief The class that holds all data regarding an event.
 */
class Event
{
public:
    explicit Event(EVENT_TYPE eventType);
    virtual ~Event();
    EVENT_TYPE eventType;
    EVENT_TYPE getEventType();
};
#endif  /* EVENT_H */