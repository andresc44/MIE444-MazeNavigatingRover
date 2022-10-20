#!/usr/bin/env python3
 
#remove or add the library/libraries for ROS
import rospy, time, math, cv2, sys
 
#remove or add the message type
from std_msgs.msg import String, Float32, Image, LaserScan, Int32
 
varS=None
 
#define function/functions to provide the required functionality
def fnc_callback(msg):
    global varS
    varS==do_something(msg.data)
 
if __name__=='__main__':
    #Add here the name of the ROS. In ROS, names are unique named.
    rospy.init_node('NODE_NAME')
    #subscribe to a topic using rospy.Subscriber class
    sub=rospy.Subscriber('TOPIC_NAME', THE_TYPE_OF_THE_MESSAGE, fnc_callback)
    #publish messages to a topic using rospy.Publisher class
    pub=rospy.Publisher('TOPIC_NAME', THE_TYPE_OF_THE_MESSAGE, queue_size=1)
    rate=rospy.Rate(10)
 
    while not rospy.is_shutdown():
        if varS<= var2:
            varP=something()
        else:
            varP=something()
 
        pub.publish(varP)
        rate.sleep()



#!/usr/bin/env python3
import rospy
from std_msgs.msg import Uint8, Bool, Uint16 #all message types used

class SampleClass:
    def __init__(self):
        #where you define 'global' variables
        self.variable1 = True
        self.variable2 = False
        self.rate = rospy.Rate(10) # 10hz
        self.pub = rospy.Publisher("/pubTopic1", Bool, queue_size=10)
        self.subscriber1 = rospy.Subscriber("/subTopic1", Uint8, self.callback1)
        self.subscriber2 = rospy.Subscriber("/subTopic1", Uint8, self.callback2)
        self.reset_service = rospy.Service("/serviceTopic1", Uint16, self.callback_reset_counter)
        
        while not rospy.is_shutdown():
            if self.variable:
                rospy.loginfo("hello")

            rate.sleep()

    def callback1(self, msg):
        self.variable1 += msg.data
        new_msg = Int64()
        new_msg.data = self.counter
        self.pub.publish(new_msg)

    def callback2(self, msg):
        self.counter += msg.data
        new_msg = Int64()
        new_msg.data = self.counter
        self.pub.publish(new_msg)
    def callback_reset_counter(self, req):
        if req.data:
            self.counter = 0
            return True, "Counter has been successfully reset"
        return False, "Counter has not been reset"

if __name__ == '__main__':
    rospy.init_node('nodeName') #node name
    try:
        SampleClass() #instance of class
    except rospy.ROSInterruptException:
        pass
