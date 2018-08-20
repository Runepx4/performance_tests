#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include "chrono"
#include "std_msgs/Float32.h"

int count = 0;
int data_points = 3000;
std::chrono::system_clock::time_point last_time; 
std::chrono::system_clock::time_point curr_time;
std::chrono::duration<double> delay;

ros::Publisher measured_frequency_publisher;

void performanceCallback(const performance_tests::SuperAwesome::ConstPtr& msg)
{
  if (count >= data_points)
  {
    //Measure the time-duration since last-time we were in this loop: 
    curr_time = std::chrono::system_clock::now();
    delay = curr_time - last_time;
    last_time = curr_time;

    //Calculate the frequency based on our data-points / samples:
    double rate_freq = double(data_points)/delay.count();

    ROS_INFO("%s",msg->awesome.c_str());
    ROS_INFO("C++ Received message at: %6.2f Hz (Approximately)", rate_freq);
    ROS_INFO("------------------------------------------------");
    
    //Publish the measured frequency, so it can be plotted in rqt_plot:  
    std_msgs::Float32 msg_freq;
    msg_freq.data=float(rate_freq);
    measured_frequency_publisher.publish(msg_freq);

    count = 0;
  }
  count++;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "performance_subscriber_cpp");
  ros::NodeHandle n;

  //last_time is initialized to the current time (now). It is used to measure the actual rate of our subscriber. 
  last_time = std::chrono::system_clock::now(); 

  ros::Subscriber sub = n.subscribe("performance_pub", 1000, performanceCallback);

  // Used to publish the measured frequency to be ploted in rqt_plot
  measured_frequency_publisher = n.advertise<std_msgs::Float32>("/measured_frequency", 1000);

  ros::spin();

  return 0;
}