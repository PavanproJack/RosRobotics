#include "ros/ros.h"
#include "ros_start/productFile.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "productClient");
  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }
  
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ros_start::productFile>("Multiply");
  ros_start::productFile srv;
  srv.request.num1 = atoll(argv[1]);
  srv.request.num2 = atoll(argv[2]);
  if (client.call(srv))
  {
    ROS_INFO("Product is : %ld", (long int)srv.response.pro);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}