#!/usr/bin/env python2

import rospy
from std_msgs.msg import Bool

def callback(data):
   rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)

  
if __name__ == '__main__':
   rospy.init_node('grabber', anonymous=True)
   rospy.Subscriber("chatter", Bool, callback)
   # spin() simply keeps python from exiting until this node is stopped
   rospy.spin()
