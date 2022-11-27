#!/usr/bin/env python3
#remove or add the library/libraries for ROS
import rospy, time
import RPi.GPIO as GPIO
#remove or add the message type
from std_msgs.msg import Int8, Bool
blueLED = 27
redLED = 22
greenLED = 23
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(blueLED, GPIO.OUT)
GPIO.setup(redLED, GPIO.OUT)
GPIO.setup(greenLED, GPIO.OUT)


#define function/functions to provide the required functionality
def light_callback(msg):
    mode = msg.data
    if (mode==1):
        GPIO.output(blueLED, GPIO.HIGH)
        GPIO.output(redLED, GPIO.LOW)
        GPIO.output(greenLED, GPIO.LOW)
    elif (mode==2):
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.HIGH)
        GPIO.output(greenLED, GPIO.LOW)
    elif (mode==3):
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.LOW)
        GPIO.output(greenLED, GPIO.HIGH)
    elif (mode==4):
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.LOW)
        GPIO.output(greenLED, GPIO.HIGH)
        pub.publish(False)
    else:
        GPIO.output(blueLED, GPIO.HIGH)
        GPIO.output(redLED, GPIO.HIGH)
        GPIO.output(greenLED, GPIO.HIGH)



if __name__=='__main__':
    #Add here the name of the ROS. In ROS, names are unique named.
    rospy.init_node('light_node', anonymous=True)
    #subscribe to a topic using rospy.Subscriber class
    sub=rospy.Subscriber('/operation_mode', Int8, light_callback)
    #publish messages to a topic using rospy.Publisher class
    pub=rospy.Publisher('/servo', Bool, queue_size=10)
    while not rospy.is_shutdown():
        rospy.spin()

    GPIO.cleanup()



