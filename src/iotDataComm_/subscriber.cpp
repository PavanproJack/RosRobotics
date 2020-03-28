#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros_start/sensor.h"

void chatterCallback(const ros_start::sensor& imsg)
{
  //ROS_INFO("I heard: [%s]", msg.Age);
  //->data.c_str()
std::cout<<": Age :" << imsg.Age<<": Name :" << imsg.Name<<": Height :" << imsg.Height<<": Weight :" << imsg.Weight<< std::endl;

}

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "iotsub");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("iotData", 1000, chatterCallback);

  ros::spin();

  return 0;
}