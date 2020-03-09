#include "Context.h"

#ifndef HIGHLEVELDRIVER_H
#define HIGHLEVELDRIVER_H

#include <memory>

class HighLevelDriver : public Context 
{
private:
    /* data */
public:
    HighLevelDriver();
    ~HighLevelDriver();

    void setCurrentState(std::shared_ptr<State>& nState);
    void addEvent(Event);
    void run();
};
#endif /* HIGHLEVELDRIVER_H */
