#include "ros/ros.h"
#include "ros_start/productFile.h"

bool mul(ros_start::productFile::Request &req,
         ros_start::productFile::Response &res){
        
        //res.pro = req.num1 * req.num2;
        
        return true;

        }


int main(int argc, char **argv){
    ros::init(argc, argv, "productServer");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("Multiply", mul);
    ros::spin();
    return 0; 

}