#include "Context.h"

#ifndef HIGHLEVELDRIVER
#define HIGHLEVELDRIVER
#include <memory>
class HighLevelDriver : public Context 
{
private:
    /* data */
public:
    HighLevelDriver();
    ~HighLevelDriver();
    void setCurrentState(std::shared_ptr<State>& nSate);
    void addEvent(Event);
    void run();
};
#endif
