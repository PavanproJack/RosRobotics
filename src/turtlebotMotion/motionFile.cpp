#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "sstream"
#include <iostream>

using namespace std;

void moveForward();
void rotate2Angle();
double rad2Deg(double rad);
double deg2Rad(double deg);
void poseCallback(const turtlesim::Pose::ConstPtr &pose);

const double pi = 3.14;
double zSpeed, xSpeed;
double angle_des, x_distance;
int clockwise = 0;
 


ros::Publisher pub;
ros::Subscriber sub;
turtlesim::Pose currentPose;


int main(int argv, char **argc){

    ros::init(argv, argc, "motionBot");
    ros::NodeHandle n;
    
    /*    
    cout<<"Angular Speed : ";
    cin>> angularSpeed;
    cout<<"Desired AngDistance : ";
    cin>>angle_des;
    cout<<"Clockwise : ";
    cin>>clockwise;
    cout<<"xSpeed : ";
    cin>> xSpeed;
    cout<<"Desired Distance : ";
    cin>>x_distance;
    cout<<"Forward : ";
    cin>>forward;*/

    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    sub = n.subscribe("/turtle1/pose", 10, poseCallback);
    try{
        //rotate2Angle();
        moveForward();
    }catch(ros::Exception &e){
        ROS_ERROR("Ros error occured %s", e.what());
    }
    return 0;
}

void moveForward(){
    int forward;
    ros::Rate loop_rate(100);
    cout<<"xSpeed : ";
    cin>> xSpeed;
    cout<<"Desired Distance : ";
    cin>>x_distance;
    cout<<"Forward : ";
    cin>>forward;
       
    geometry_msgs::Twist linearSpeed;

    if(forward){
        linearSpeed.linear.x = xSpeed;
    }else{
        linearSpeed.linear.x = -xSpeed;
    }
        
    linearSpeed.linear.y = 0;
    linearSpeed.linear.z = 0;

    linearSpeed.angular.x = 0;
    linearSpeed.angular.y = 0;
    linearSpeed.angular.z = 0;

    double t0 = ros::Time::now().toSec();
    double distanceCovered = 0;
        do{
            pub.publish(linearSpeed);
            double time = ros::Time::now().toSec() - t0;
            distanceCovered = xSpeed * time;
            cout<< "distanceCovered is : " << distanceCovered << endl;
            ros::spinOnce();
            loop_rate.sleep();
            cout<< "pose is : "<< rad2Deg(currentPose.theta) << endl;
         }while(distanceCovered < x_distance);
        linearSpeed.linear.x = 0;
        pub.publish(linearSpeed);

}


void rotate2Angle(){

    //cout<<"Speed: " << speed << "Desired Anglular distance :" << des<< endl;
    cout<<"Angular Speed : ";
    cin>> zSpeed;
    cout<<"Desired AngDistance : ";
    cin>>angle_des;
    cout<<"Clockwise : ";
    cin>>clockwise;

    zSpeed = deg2Rad(zSpeed);
    angle_des = deg2Rad(angle_des);
     
     geometry_msgs::Twist velocity;

        velocity.linear.x = 0;
        velocity.linear.y = 0;
        velocity.linear.z = 0;
        
        velocity.angular.x = 0;
        velocity.angular.y = 0;

        if(clockwise){
            velocity.angular.z = -zSpeed;
        }else{
            velocity.angular.z = zSpeed;
        }
    double angleCovered = 0.0;
    double t0 = ros::Time::now().toSec();
    double count = 0;
    ros::Rate loop_rate(100);
    try{
        do{
            pub.publish(velocity);
            double diffAngle = angle_des - angleCovered;
            double time = ros::Time::now().toSec() - t0;
            //cout<< "diffAngele is : "<< diffAngle << endl;
            //curr_dist = abs(speed) * ( ros::Time::now().toSec() - t0 );
            angleCovered = zSpeed * time;
            cout<< "angleCovered is : " << angleCovered << endl;
            ros::spinOnce();
            loop_rate.sleep();
            cout<< "pose is : "<< rad2Deg(currentPose.theta) << endl;
            //ros::Duration(2).sleep();
        }while(angleCovered < angle_des);
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

