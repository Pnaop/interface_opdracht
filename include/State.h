#ifndef STATE_H
#define STATE_H

#include "Event.h"

/**
 * @class State
 * @brief Interface for each state implementation.
 */
class State
{
public:
   /**
   ** @brief handles event - implementation is state depended
   ** @param event that was triggered and needs to be handled 
   **/
   virtual void handleEvent(Event& event) = 0;

   /**
    * @brief entry of the state -- only execute once when entering the state
    **/
   virtual void entry() = 0;

   /**
    * @brief entry of the state -- only execute while state is active
    **/
   virtual bool doActivity() = 0;

   /**
    * @brief entry of the state -- only execute once when exiting the state
    **/
   virtual void exit() = 0; 
protected:
   State(){}
   virtual ~State(){}
};

#endif /* STATE_H */