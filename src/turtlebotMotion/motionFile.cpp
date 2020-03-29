#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
void moveForward(double speed, double distance, bool isForward);

//double t0 = 0;
double distance = 4;
double curr_dist = 0;
double speed = 1;
double pi = 22/7;
ros::Publisher pub;
ros::Subscriber sub;
int main(int argv, char **argc){

    ros::init(argv, argc, "motionBot");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);
    double t0 = ros::Time::now().toSec();

    pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    sub = n.subscribe(/turtle1/pose, 10, poseCallback);

    geometry_msgs::Twist velocity;
    cout<<"Angular Speed : ";
    cin>> angularSpeed;
    cout<<"Desired Orientation";
    cin>>angle_des;

    rotate2Angle(deg2Rad(angularSpeed), deg2Rad(angle_des));

   
}

void rotate2Angle(double speed, double des){
    double diffAngle = des - currentPose;

        velocity.linear.x = 0;
        velocity.linear.y = 0;
        velocity.linear.z = 0;
        
        velocity.angular.x = 0;
        velocity.angular.y = 0;
        velocity.angular.z = speed;

     while(curr_dist < distance){
       
        curr_dist = abs(speed) * ( ros::Time::now().toSec() - t0 );
        pub.publish(velocity);
        ros::spinOnce();
        loop_rate.sleep();
    }
     velocity.linear.x = 0;
     pub.publish(velocity);
    
}

void poseCallback(const turtlesim::pose::Constptr &pose){
   currentPose  = pose.theta;
   cout<<"currentPose is : "<< currentPose;
}

double deg2Rad(double deg){
    return deg * pi / 180;
}

