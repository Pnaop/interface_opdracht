#include <thread>
#include <ros/ros.h>
#include "../include/RobotLD.h"
#include "../include/RobotLDOffset.h"

#define ZEROPOINT 1500
#define SPECIALZEROPOINT 500
#define POINTDEGREES 11.11
#define USBPORT "/dev/pts/5"

RobotLD::RobotLD()//:serial(ioservice,USBPORT)
{
    // Initialize all the axes, every axis has it's own config.
    axis.push_back(Axis(BASE_ROTATION, -90, 90, OBASE_ROTATION, -90,0, false, 220));
    axis.push_back(Axis(SHOULDER, -30, 90, OSHOULDER, 0, 0, false, 190));
    axis.push_back(Axis(ELBOW, 0, 135, OELBOW, 0, 0, true, 280));
    axis.push_back(Axis(WRIST, -90, 90, OWRIST, 0, 0, false, 240));
    axis.push_back(Axis(GRIPPER, -10, 80, OGRIPPER, 0, 0, false, 140));
    axis.push_back(Axis(WRIST_ROTATION, -90, 90, OWRIST_ROTATION, 0, 0, false, 210));

    BAUD = 112500;
  /*  serial.set_option(boost::asio::serial_port_base::baud_rate(BAUD));
    serial.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
    serial.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
    serial.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
    serial.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));
    */setOffset();
}

RobotLD::~RobotLD()
{
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
/*
   if (serial.is_open())
   {
	 	serial.close();
   }*/
}

float RobotLD::convertDegrees(float degrees, Axis& ax)
{
    float output = -1;

    if (degrees >= ax.getMinDegrees() && degrees <= ax.getMaxDegrees())
    {
        output = (degrees * POINTDEGREES);

        if (!ax.getSpecial())
        {
            output += ZEROPOINT;
        }
        else
        {
            output += SPECIALZEROPOINT;
        }
    }
    output = round(output);
    return output;
}

uint64_t RobotLD::convertTime(uint64_t milliseconds)
{
    if (milliseconds > 0)
    {
        return milliseconds * CONVERTTIMERATIO;
    }
    else
    {
        return 0;
    }
}

float RobotLD::getGoalAxis(uint32_t id)
{
    return axis[id].getGoal();
}

std::vector<Axis> &RobotLD::getAxis()
{
    return axis;
}

void RobotLD::setOffset()
{
    std::string command = "";

    for (uint32_t i = 0; i < axis.size(); ++i)
    {
        command += " #" + std::to_string(i) + " PO" + std::to_string(axis[i].getOffset());
    }

    sendSerial(command);
}

bool RobotLD::sendCommand(const interface_opdracht::moveGoal &goal)
{
    std::string command = "";
    for (uint32_t index = 0; index < goal.axis.size(); ++index)
    {
        float convertedDegr = convertDegrees(goal.move_to[index], this->axis[goal.axis[index]]);
        if (convertedDegr < 0)
        {

            return false;
        }

        command += " #" + std::to_string(goal.axis[index]);
        this->axis[goal.axis[index]].setGoal(goal.move_to[index]);
        command += " P" + std::to_string(uint32_t(std::ceil(convertedDegr)));
    }
    command += " T" + std::to_string(convertTime(goal.time));

    sendSerial(command);

    return true;
}

void RobotLD::sendStopCommand()
{
    for (uint32_t i = 0; i < axis.size(); ++i)
    {
        std::string command = " STOP " + std::to_string(axis[i].getId());
        sendSerial(command);
    }
}

void RobotLD::sendSerial(std::string &text)
{
    std::cout << text << std::endl;
    /*
    boost::asio::streambuf b;
    std::ostream os(&b);
    os << text << "\n\r";
    boost::asio::write(serial, b.data());
    os.flush();*/
    
}

bool RobotLD::checkMoveValid(uint8_t id, float position, uint64_t time)
{
  // If the boolean is still true after the test, the move is valid.
  bool result = true;

  // Get the axis for the move.
  Axis a = axis.at(id);

  // Convert the goal to check that it is valid.
  float positionConverted = convertDegrees(position, a);

  // Check if the position is valid.
  if (positionConverted < 0)
  {
      result = false;
  }
  
  // Calculate the distance of the movement.
  float movement = fabs(position - a.getGoal());

  // Calculate the fastest time that the movement would take.
  float minimumDuration = (movement / 60) * a.getMaxSpeed();

  // Predict if the time is physically possible.
  if(minimumDuration > time)
  {
      ROS_INFO("QoS­Warning: requested time not achievable, expected duration: %s ms", std::to_string(int(minimumDuration)).c_str());
      result = false;
  }

  return result;
}