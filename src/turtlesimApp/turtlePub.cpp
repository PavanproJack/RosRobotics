#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "turtleMove");


  ros::NodeHandle n;

  
  //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  //ros::Rate loop_rate(10);

    ros::Subscriber sub = n.subscribe("/turtle1/pose", 1000, chatterCallback);

    ros::spin();
 
 /* int count = 0;
  while (ros::ok())
  {
   
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

   
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }*/

  return 0;
}