/**
 * @file main.cpp
 * @author Hemmy Gerrits en Jari van den Heuvel
 * @version 0.0.1
 */

#include "../include/HighLevelDriver.h"
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"robotNode");
    std::string rosNodeName = "move_arm";
    HighLevelDriver HLD(rosNodeName);
    HLD.run();
    return 0;
}