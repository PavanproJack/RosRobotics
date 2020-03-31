#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "sstream"
#include <iostream>

using namespace std;

void moveForward(double speed, double distance, bool isForward);
double deg2Rad(double deg);
void rotate2Angle(double speed, double des);
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
    double angularSpeed = 0;
    double angle_des = 0;
   
    cout<<"Angular Speed : ";
    cin>> angularSpeed;
    cout<<"Desired Orientation : ";
    cin>>angle_des;

    //rotate2Angle(deg2Rad(angularSpeed), deg2Rad(angle_des));
    deg2Rad(angularSpeed);   deg2Rad(angle_des);

    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    sub = n.subscribe("/turtle1/pose", 10, poseCallback);
    rotate2Angle( angularSpeed,  angle_des);

  
    return 0;
    
}

void rotate2Angle(double speed, double des){
     geometry_msgs::Twist velocity;
     
    double diffAngle = des - currentPose.theta;
   // cout<< "currentPose is : " << currentPose << endl;
    cout<< "diff angle  is : " << diffAngle << endl;
   // print("Hello", 56);
    bool clockwise = ((diffAngle > 0) ? false : true);

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
    ros::Rate loop_rate(10);
    try{

        do{
            pub.publish(velocity);
            //cout<< "Count is : "<< count++ << endl;
            double time = ros::Time::now().toSec() - t0 ;
            //curr_dist = abs(speed) * ( ros::Time::now().toSec() - t0 );
            //angleCovered = speed * time;
            cout<< "timeCovered is : " << speed * time << endl;
            ros::spinOnce();
            loop_rate.sleep();
            //ros::Duration(2).sleep();
        }while(angleCovered < 1.57);
        velocity.angular.z = 0;
        pub.publish(velocity);

    }catch(ros::Exception &e){
        ROS_ERROR("ROs error occured %s", e.what());
    }
     

     
    
}

void poseCallback(const turtlesim::Pose::ConstPtr &pose){
    
   currentPose.theta  = pose->theta;
   cout<< "pose is : "<< currentPose.theta << endl;
   
}

//void print(sstream ss, double t){
 //    cout<< ss << t << endl;
//}

double deg2Rad(double deg){
    cout<<"Angular values in Radians: ";
    cout<< deg * pi/180;
   
    return deg * pi / 180;
}

double rad2Deg(double rad){
    return rad * 180 / pi;
}

