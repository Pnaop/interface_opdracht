#ifndef ROBOTLD_H
#define ROBOTLD_H

#include "Axis.h"
#include <vector>
#include <boost/asio.hpp>
#include <interface_opdracht/moveAction.h>

/**
 * @class RobotLD
 * @brief The LowLevelDriver that communicates with the robotarm.
 * 
 * Responsible for serial connection with hardware and safety checks.
 */
class RobotLD
{
public:
  RobotLD();
  ~RobotLD();
  /**
   * @brief Get the current goal of the given axis
   * @param id - index of the axis
   * @return float - goal of the axis
   **/
  float getGoalAxis(uint32_t id);
  /** @brief send stopcommand to the robot
  *
  **/
  void sendStopCommand();
  /**
   * @brief send a command to the robot with the given goal
   * @param goal - const goal where the robot needs to go
   * @return  if the command has been send
   **/
  bool sendCommand(const interface_opdracht::moveGoal& goal);
  /** @brief get all axis of the robot in a vector
   * @return the vector that contains the axis
   */
  std::vector<Axis>& getAxis();

  /** @brief Check that the axis is able to move to the goal within the requested time.
   ** @param id - index of the ax
   ** @param position - the position where the axis needs to go
   ** @param time - time that the ax needs to reach the goal
   */
  bool checkMoveValid(uint8_t id, float position, uint64_t time);
protected:

private:
  /**
  * @brief ioservice for usbconnection 
  **/
  boost::asio::io_service ioservice;
  /// @brief serial the serial of the usb connection 
  //   boost::asio::serial_port serial;
  /// @brief baudrate of the serial connection
  uint32_t BAUD;

  /**
   * @brief sends the offset to the robot
   **/
  void setOffset();

  /**
   * @convert degrees into pwm
   * @return the pwm in float value
   **/
  float convertDegrees(float degrees,Axis& ax);

  /**
   * @brief convert given time into converted time (what the robot needs)
   * @param millisecons - time that needs to be converted for the robot
   * @return the converted time
   **/

  uint64_t convertTime(uint64_t milliseconds);

  /// vector of the axis
  std::vector<Axis> axis;

  /**
   * @brief sends the given text to the robot with the serial connection
   * @param text - the text that needs to be send to the robot
   **/
  void sendSerial(std::string& text);

  /// convert time-ratio of the robot  s : 0.001 ms : 1 , nano: 10 
  const uint16_t CONVERTTIMERATIO = 1;
};

#endif /* ROBOTLD_H */