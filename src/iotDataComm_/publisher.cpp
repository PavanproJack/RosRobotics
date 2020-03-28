#include "ros/ros.h"
#include "ros_start/sensor.h"


int main(int argc, char **argv)
{ 
   std::cout<<"Msg #"<<std::endl;
  ros::init(argc, argv, "iotpub");

  ros::NodeHandle n;

  
  ros::Publisher iot_pub = n.advertise<ros_start::sensor>("iotData", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    count++;
    ros_start::sensor imsg;
    imsg.Age = 25;
    imsg.Name = "Pavan";
    imsg.Height = 5.8;
    imsg.Weight = 65.4;

    std::cout<<"Msg #"<< count<< ": Age :" << imsg.Age<<": Name :" << imsg.Name<<": Height :" << imsg.Height<<": Weight :" << imsg.Weight<< std::endl;

    iot_pub.publish(imsg);
    ros::spinOnce();
   
    loop_rate.sleep();
  }
    



   /* std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;*/
  


  return 0;
}