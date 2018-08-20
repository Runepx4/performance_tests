#!/usr/bin/env python
import rospy
from performance_tests.msg import SuperAwesome
from std_msgs.msg import Float32


def timer_callback(event):
    global rate, update_rate
    step_size = rospy.get_param('~step_size_hz',1000)
    frequency_end = rospy.get_param('~end_frequency_hz',10000)

    update_rate = update_rate + step_size

    if (update_rate > frequency_end):
        update_rate = frequency_end

    rate = rospy.Rate(update_rate)


def performance_pub():
    global rate, update_rate
    pub = rospy.Publisher('performance_pub', SuperAwesome, queue_size=100)
    freq_pub = rospy.Publisher('/real_frequency', Float32, queue_size=100)
    rospy.init_node('performance_test', anonymous=False)

    #Get private parameters from launch file: 
    step_time_sec = rospy.get_param('~step_time_sec',4)
    update_rate = rospy.get_param('~start_frequency_hz',1000)
    
    rate = rospy.Rate(update_rate)

    rospy.Timer(rospy.Duration(step_time_sec), timer_callback)

    while not rospy.is_shutdown():
        performance_str = "Python publish rate set to %#.2f Hz" % update_rate
        pub.publish(performance_str)
        freq_pub.publish(update_rate) #Real Rate message publication
        rate.sleep()


if __name__ == '__main__':
    try:
        performance_pub()
    except rospy.ROSInterruptException:
        pass

