#!/usr/bin/env python
import rospy
from performance_tests.msg import SuperAwesome
from std_msgs.msg import Float32

#------ Global variables: ------
pub = rospy.Publisher('/measured_frequency', Float32, queue_size=1000)
count = 0
data_points = 1000
last_time = 0
curr_time = 0
#------------------------------
def performanceCallback_py(data):
    global count
    global last_time
    if (count > data_points):
        curr_time = rospy.get_rostime()
        diff_py=curr_time-last_time;
        last_time = curr_time;
        rate_freq = data_points / diff_py.to_sec()

        rospy.loginfo("%s",data.awesome)
        rospy.loginfo("Python Received message at: %#.2f hz (Approximately)", rate_freq)
        rospy.loginfo("----------------------------------------------------")

        pub.publish(rate_freq)
        count = 0

    count += 1
    
def performance_sub():
    global last_time
    rospy.init_node('performance_subscriber', anonymous=True)
    last_time = rospy.get_rostime()

    rospy.Subscriber("performance_pub", SuperAwesome, performanceCallback_py, queue_size=1000)
    rospy.spin()

if __name__ == '__main__':
    performance_sub()