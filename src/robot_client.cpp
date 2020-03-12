#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <interface_opdracht/moveAction.h>
#include <interface_opdracht/emergency.h>
#include "../include/EnumMode.h"
#include "../include/EnumAxis.h"
#include <cstring>
typedef actionlib::SimpleActionClient<interface_opdracht::moveAction> Client;
class MyNode
{
public:
  MyNode() : ac("move_arm", true)
  {
    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();
  }
  void demo()
  {
    // • Voorgeprogrammeerde posities: Straight up.

    interface_opdracht::moveGoal goal;
    goal.modeType = MODES::PROGRAM_UP;
    goal.axis.push_back(std::stoi(std::to_string(AXIS::BASE_ROTATION)));
    goal.move_to.push_back(10);
    goal.time = 2000;
    this->doStuff(goal);
    ac.waitForResult();
    goal.modeType = MODES::PROGRAM_READY;
    this->doStuff(goal);
    ac.waitForResult();
    // • Verschillende opeenvolgende armverplaatsingen naar verschil-
    // lende locaties. ZELF LATEN INVULLEN
    std::vector<interface_opdracht::moveGoal> goalsList;
    std::string line = "";
    std::vector<std::string> servoPositionsLine;
    char ch = ' ';
    const std::string exitString = "go";
    goal.axis.clear();
    goal.move_to.clear();
    goal.modeType = FREEMODE;

    ROS_INFO("Waar wilt u de robot heen verplaatsen? format = -i {servo id} -d {degrees} -t {time} (meerdere mogelijk uitzondering van tijd)");

    ROS_INFO("Moeten 2 verschillende goals opgeven. Dit kan beste 2 tegeovergestelde goals doen. per goal een enter");
    ROS_INFO("toets %s en dan enter om het uit te voeren", exitString.c_str());
    while (line != exitString)
    {

      std::getline(std::cin, line);
      if (exitString != line)
      {
        std::string tempString = "";
        for (size_t i = 0; i < line.size(); ++i)
        {
          ch = line[i];
          if (ch != ' ')
          {
            tempString += ch;
          }
          else
          {
            servoPositionsLine.push_back(tempString);
            tempString = "";
          }
        }
        servoPositionsLine.push_back(tempString);
      

      for (size_t i = 0; i < servoPositionsLine.size() - 1; ++i)
      {
        if ("-i" == servoPositionsLine[i])
        {
          goal.axis.push_back(std::stoi(servoPositionsLine[i + 1]));
        }
        else if ("-d" == servoPositionsLine[i])
        {
          goal.move_to.push_back(std::stof(servoPositionsLine[i + 1]));
        }
        else if ("-t" == servoPositionsLine[i])
        {
          goal.time = std::stoll(servoPositionsLine[i + 1]);
        }
      }
      }
      servoPositionsLine.clear();
      goalsList.push_back(goal);
    }
    this->doStuff(goalsList[0]);
    ac.waitForResult();
    /// goals list verzenden
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<interface_opdracht::emergency>("emergency");
    // •  Noodstop (werking moet duidelijk zichtbaar zijn).
    ROS_INFO("Druk op enter om dezelfde actie's nog een keer uit te voeren en daarna weer op enter om de emercenystop te activeren en dan weer enter om naar park te gaan");
    std::getline(std::cin, line);
    this->doStuff(goalsList[1]);
    std::getline(std::cin, line);
    /// goals list verzenden
    interface_opdracht::emergency srv;
    srv.request.error = true;
    /*if (!client.call(srv))
    {
      ROS_ERROR("Er ging iets fout bij het aanroepen van emergency");
    }
    */
    ROS_INFO("DRUK ENTER VOOR VERDER TE GAAN.");
    std::getline(std::cin, line);

    goal.modeType = MODES::PROGRAM_PARK;
    goal.axis.push_back(std::stoi(std::to_string(AXIS::BASE_ROTATION)));
    goal.move_to.push_back(0);
    goal.time = 4000;

    doStuff(goal);
    ac.waitForResult();
  }

  void doStuff(interface_opdracht::moveGoal &goal)
  {
    //ROS_INFO(std::to_string(goal.move_to).c_str());
    // Need boost::bind to pass in the 'this' pointer
    ac.sendGoal(goal,
                boost::bind(&MyNode::doneCb, this, _1, _2),
                boost::bind(&MyNode::activeCb, this),
                boost::bind(&MyNode::feedbackCb, this, _1));
  }

  // Called once when the goal completes
  void doneCb(const actionlib::SimpleClientGoalState &state,
              const interface_opdracht::moveResultConstPtr &result)
  {
    ROS_INFO("Finished in state [%s]", state.toString().c_str());
    ROS_INFO("Answer: %i", result->sequence.back());
  }

  // Called once when the goal becomes active
  void activeCb()
  {
    ROS_INFO("Goal just went active");
  }

  // Called every time feedback is received for the goal
  void feedbackCb(const interface_opdracht::moveFeedbackConstPtr &feedback)
  {
    ROS_INFO("Time: %s",std::to_string(feedback->sequence[feedback->sequence.size()-1]).c_str());
  }


private:
  Client ac;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "moveClient");
  MyNode my_node;
  my_node.demo();

  return 0;
}