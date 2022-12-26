#!/usr/bin/env python3
#remove or add the library/libraries for ROS
import rospy
import RPi.GPIO as GPIO
import time
#remove or add the message type
from std_msgs.msg import Int8, Bool
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan

blueLED = 27
redLED = 22
greenLED = 23
lidar_left=0
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(blueLED, GPIO.OUT)
GPIO.setup(redLED, GPIO.OUT)
GPIO.setup(greenLED, GPIO.OUT)
GPIO.output(blueLED, GPIO.LOW)
GPIO.output(redLED, GPIO.LOW)
GPIO.output(greenLED, GPIO.LOW)

#define function/functions to provide the required functionality
def light_callback(msg):
    mode = msg.data
    if (mode==1):
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.LOW)
        GPIO.output(greenLED, GPIO.LOW)
    elif (mode==2):
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.HIGH)
        GPIO.output(greenLED, GPIO.LOW)
    elif (mode==3):
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.LOW)
        GPIO.output(greenLED, GPIO.LOW)
    elif (mode==4):
        move_cmd = Twist()
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.HIGH)
        GPIO.output(greenLED, GPIO.LOW)

        #if the distnace is greater than 50cm, then it must be approaching from the bottom, therefore go straight
        if lidar_left > 50:
            move_cmd.linear.x = 0.26
            move_cmd.linear.y = 0
            move_cmd.linear.z = 0
            move_cmd.angular.x = 0
            move_cmd.angular.y = 0
            move_cmd.angular.z = 0
            pub2.publish(move_cmd)
            time.sleep(1.1)
       
        #else it must be approaching from side, therefore turn left
        else:
            #move forward
            move_cmd.linear.x = 0.26
            move_cmd.linear.y = 0
            move_cmd.linear.z = 0
            move_cmd.angular.x = 0
            move_cmd.angular.y = 0
            move_cmd.angular.z = 0
            pub2.publish(move_cmd)
            time.sleep(0.4)

            #rotation
            move_cmd.linear.x = 0
            move_cmd.linear.y = 0
            move_cmd.linear.z = 0
            move_cmd.angular.x = 0
            move_cmd.angular.y = 0
            move_cmd.angular.z = -1.6
            pub2.publish(move_cmd)
            time.sleep(2)


            move_cmd.linear.x = 0.26
            move_cmd.linear.y = 0
            move_cmd.linear.z = 0
            move_cmd.angular.x = 0
            move_cmd.angular.y = 0
            move_cmd.angular.z = 0
            pub2.publish(move_cmd)
            time.sleep(1)

        #backing up the robot
        pub.publish(False)
        move_cmd.linear.x = -0.26
        move_cmd.linear.y = 0
        move_cmd.linear.z = 0
        move_cmd.angular.x = 0
        move_cmd.angular.y = 0
        move_cmd.angular.z = 0
        pub2.publish(move_cmd)
        time.sleep(0.5)

        #stop moving robot
        move_cmd.linear.x = 0
        move_cmd.linear.y = 0
        move_cmd.linear.z = 0
        move_cmd.angular.x = 0
        move_cmd.angular.y = 0
        move_cmd.angular.z = 0
        pub2.publish(move_cmd)

    else:
        GPIO.output(blueLED, GPIO.LOW)
        GPIO.output(redLED, GPIO.LOW)
        GPIO.output(greenLED, GPIO.LOW)

def laser_callback(msg):
    global lidar_left
    lidar_left = msg.ranges[180]

if __name__=='__main__':
    #Add here the name of the ROS. In ROS, names are unique named.
    rospy.init_node('light_node', anonymous=False)
    #subscribe to a topic using rospy.Subscriber class
    sub=rospy.Subscriber('/operation_mode', Int8, light_callback)
    sub=rospy.Subscriber('/scan',LaserScan, laser_callback)

    #publish messages to a topic using rospy.Publisher class
    pub=rospy.Publisher('/servo', Bool, queue_size=10)
    pub2=rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    while not rospy.is_shutdown():
        rospy.spin()

    GPIO.cleanup()