#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "sstream"
#include <iostream>

using namespace std;

void moveForward(double speed, double distance, bool isForward);
double deg2Rad(double deg);
void rotate2Angle(double speed, double des, int clockwise);
double rad2Deg(double rad);
//void print(sstream ss, double t);
//double t0 = 0;
double distance = 4;
double curr_dist = 0;
double speed = 1;
const double pi = 3.14;


ros::Publisher pub;
ros::Subscriber sub;
turtlesim::Pose currentPose;

void poseCallback(const turtlesim::Pose::ConstPtr &pose);


int main(int argv, char **argc){

    ros::init(argv, argc, "motionBot");
    ros::NodeHandle n;
    double angularSpeed;
    double angle_des;
    int clockwise;
    
    cout<<"Angular Speed : ";
    cin>> angularSpeed;
    cout<<"Desired AngDistance : ";
    cin>>angle_des;
    cout<<"Clockwise : ";
    cin>>clockwise;

    //rotate2Angle(deg2Rad(angularSpeed), deg2Rad(angle_des));
   // deg2Rad(angularSpeed);   deg2Rad(angle_des);

    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    sub = n.subscribe("/turtle1/pose", 10, poseCallback);
    try{
        rotate2Angle( deg2Rad(angularSpeed) ,   deg2Rad(angle_des), clockwise);
    }catch(ros::Exception &e){
        ROS_ERROR("Ros error occured %s", e.what());
    }
   
  
    return 0;
    
}

void rotate2Angle(double speed, double des, int clockwise){

    cout<<"Speed: " << speed << "Desired Anglular distance :" << des<< endl;

     geometry_msgs::Twist velocity;
     
   // double diffAngle = des - currentPose.theta;
   // cout<< "currentPose is : " << currentPose << endl;
    //cout<< "diff angle  is : " << diffAngle << endl;
   // print("Hello", 56);
    //bool clockwise = ((diffAngle > 0) ? false : true);

        velocity.linear.x = 0;
        velocity.linear.y = 0;
        velocity.linear.z = 0;
        
        velocity.angular.x = 0;
        velocity.angular.y = 0;

        if(clockwise){
            velocity.angular.z = -speed;
        }else{
            velocity.angular.z = speed;
        }
    // cout<< "Velocity is : " << velocity<<endl; 
    double angleCovered = 0.0;
    double t0 = ros::Time::now().toSec();
    double count = 0;
    ros::Rate loop_rate(100);
    try{
           // pub.publish(velocity);
        do{

            pub.publish(velocity);
            double diffAngle = des - angleCovered;
            double time = ros::Time::now().toSec() - t0;
            //cout<< "diffAngele is : "<< diffAngle << endl;
            //curr_dist = abs(speed) * ( ros::Time::now().toSec() - t0 );
            angleCovered = speed * time;
            //cout<< "angleCovered is : " << angleCovered << endl;
            ros::spinOnce();
            loop_rate.sleep();
            cout<< "pose is : "<< rad2Deg(currentPose.theta) << endl;
            //ros::Duration(2).sleep();
        }while(angleCovered < des);
        velocity.angular.z = 0;
        pub.publish(velocity);

    }catch(ros::Exception &e){
        ROS_ERROR("ROs error occured %s", e.what());
    }
     
}

void poseCallback(const turtlesim::Pose::ConstPtr &pose){
   currentPose.theta  = pose->theta;
  // cout<< "pose is : "<< rad2Deg(currentPose.theta) << endl;
}

double deg2Rad(double deg){
    return deg * pi / 180;
}

double rad2Deg(double rad){
    return rad * 180 / pi;
}

