#ifndef ROBOTLD_H
#define ROBOTLD_H

#include "Axis.h"
#include <vector>
#include <boost/asio.hpp>
#include <interface_opdracht/moveAction.h>

class RobotLD
{

public:
RobotLD();
~RobotLD();
float getGoalAxis(uint32_t id);
void sendStopCommand();
bool sendCommand(const interface_opdracht::moveGoal& goal);
std::vector<Axis>& getAxis();

bool checkMoveValid(uint8_t id, float position, uint64_t time);
protected:

private:
  /// USB CONNECTIE

  boost::asio::io_service ioservice;
 //   boost::asio::serial_port serial;
  uint32_t BAUD;



void setOffset();
float convertDegrees(float degrees,Axis& ax);
uint64_t convertTime(uint64_t milliseconds);
std::vector<Axis> axis;
void sendSerial(std::string& text);
const uint16_t CONVERTTIMERATIO = 1;
};



#endif