#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "performance_tests/SuperAwesome.h"
#include <sstream>


int main(int argc, char **argv)
{
  double start_frequency, end_frequency, step_time_sec, step_size_hz;

  ros::init(argc, argv, "performance_test");
  ros::NodeHandle n;
  ros::NodeHandle nhPriv("~");
  nhPriv.param<double>("start_frequency_hz", start_frequency, 10000.0);
  nhPriv.param<double>("end_frequency_hz", end_frequency, 30000.0);
  nhPriv.param<double>("step_time_sec", step_time_sec, 4);
  nhPriv.param<double>("step_size_hz", step_size_hz, 2000.0);
  //Used to plot the frequency in rqt_plot:
  ros::Publisher frequency_publisher = n.advertise<std_msgs::Float32>("/real_frequency", 1000);
  //performance_pub topic is setup to publish the SuperAwesome message (string):  
  ros::Publisher performance_pub = n.advertise<performance_tests::SuperAwesome>("performance_pub", 1000.0);

  // update_rate sets the frequency of the publisher:
  double update_rate = start_frequency;
  ros::Rate loop_rate(update_rate);

  //time_next is used to increased the publish rate with a timer interval of "step_time_sec": 
  ros::Time time_next = ros::Time::now() + ros::Duration(int(step_time_sec),0);
  
  while (ros::ok())
  {
    // Publish the SuperAwesome message:
    performance_tests::SuperAwesome msg;
    std::stringstream ss;
    ss << "C++ publish rate set to: " << std::fixed << std::setprecision(2) << update_rate << " Hz";
    msg.awesome = ss.str();
    performance_pub.publish(msg);

    // Check if we need to update the published frequency: 
    if (ros::Time::now() >= time_next)
    {
      time_next = ros::Time::now() + ros::Duration(int(step_time_sec),0);
      update_rate = update_rate + step_size_hz;
      
      if (update_rate > end_frequency) // Have we reached the user defined max frequency?
        update_rate = end_frequency;

      // Update the loop rate to the new frequency:
      loop_rate = ros::Rate(update_rate); 
    }

    // Publish the current frequency to the the topic "/real_frequency", so it can be displayed in rqt_plot.
    std_msgs::Float32 msg_freq;
    msg_freq.data=float(update_rate);
    frequency_publisher.publish(msg_freq);

    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}