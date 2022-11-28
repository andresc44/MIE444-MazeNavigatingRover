#! /usr/bin/env python3

import rospy
from sensor_msgs.msg import LaserScan

def callback(msg):
    print('\n\n Straight: ')
    print (msg.ranges[0])
    print('\t Left: ')
    print (msg.ranges[180])
    print('\t Backward: ')
    print (msg.ranges[360])
    print('\t Right: ')
    print (msg.ranges[540])
    print(len(msg.ranges))

rospy.init_node('scan_values') 
sub = rospy.Subscriber('/scan', LaserScan, callback)
rospy.spin()