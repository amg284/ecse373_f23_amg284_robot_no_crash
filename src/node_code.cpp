#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float64.h"
#include <sstream>



ros::Publisher *p_pub;
bool movement_brake = false;
double wall_dist = 1.0;

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  geometry_msgs::Twist pt;
  pt.linear = msg->linear;
  pt.angular = msg->angular;
  if(movement_brake && pt.linear.x > 0){
    pt.linear.x = 0;
  }

  p_pub->publish(pt);
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  for(int i = 45; i <=225; i++){
    if(wall_dist > msg->ranges[i]){
      movement_brake = true;
      ROS_WARN("Detected Obstacle, please turn to continue.");
      break;
    }
    if(i==225){
      movement_brake = false;
    }
  }
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "cmd_vel");

  ros::NodeHandle n;
  ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);
  if (n.getParamCached("wall_dist", wall_dist)) {
    ROS_INFO("wall_dist was updated to: [%2.2f]", wall_dist);
  }
  

  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  p_pub = &cmd_vel_pub;


  ros::Subscriber twist_sub = n.subscribe("des_vel", 1000, twistCallback);
  ros::Subscriber laser_sub = n.subscribe("laser_0", 1000, laserCallback);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    geometry_msgs::Twist msg;
    cmd_vel_pub.publish(msg);
    
    ROS_INFO_ONCE("wall_dist is now: [%2.2f]", wall_dist);
  
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
