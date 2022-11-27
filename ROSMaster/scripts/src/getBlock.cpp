#include <ros/ros.h> //always keep
#include <std_msgs/UInt16.h> //topic data types
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Twist.h>

class Searcher { //Classes convention are capitalized
    private:
        uint16_t tofFrontDistance = 1000; //not sure if I can make this a float since TOF gives Uint16. Want to make it float for comparison later
        uint8_t opMode = 1; //consider declaring in public for tofFrontDistance

        ros::Publisher pub1; //create publisher objects, could make more descriptive
        ros::Publisher pub2; 
        ros::Publisher pub3;
        ros::Subscriber sub1; //subscriber objects
        ros::Subscriber sub2; 
    
    public:

    Searcher(ros::NodeHandle *nh) {
        pub1 = nh->advertise<std_msgs::Int8>("/operation_mode", 10); //publish to operation_mode, and set datatype to Int8
        pub2 = nh->advertise<std_msgs::Bool>("/servo", 10); //publish to servo, and set datatype to Boolean
        pub3 = nh->advertise<geometry_msgs::Twist>("/cmd_vel", 10); //publish to cmd_vel and set data type to Twist

        sub1 = nh->subscribe("/TOF", 20, //topic, queueSize,
            &Searcher::TOF_Cb, this); //callback function
        sub2 = nh->subscribe("/operation_mode", 15, 
            &Searcher::operation_mode_Cb, this);
    }

    void TOF_Cb(const std_msgs::UInt16& msg) {
        
        tofFrontDistance = msg.data; //front distance from TOF, unit in mm
    }

    void operation_mode_Cb(const std_msgs::Int8& msg) {

        opMode = msg.data; //stores operation mode of rover 
    }
    
    void publishAll() {

        std_msgs::Int8 operationMode; //I think we need to declare variables within publish FN to be able to publish them
        std_msgs::Bool servoState;
        geometry_msgs::Twist wheel_msg; 

        if(opMode == 2){

            if(tofFrontDistance > 95){ //once we are close enough, actuate servo, what happens from 90-95
                wheel_msg.linear.x = 0.2; //need to make sure of slow approach speed, probably can't go that slow and straight. Maybe 0.2
                wheel_msg.linear.y = 0.0;
                wheel_msg.linear.z = 0.0;

                wheel_msg.angular.x = 0.0;
                wheel_msg.angular.y = 0.0;
                wheel_msg.angular.z = 0.0;
            }
            
            else if (tofFrontDistance <= 95) { //once block is onboard, change rover state, change to =<95?
                wheel_msg.linear.x = 0.0;
                wheel_msg.linear.y = 0.0;
                wheel_msg.linear.z = 0.0;

                wheel_msg.angular.x = 0.0;
                wheel_msg.angular.y = 0.0;
                wheel_msg.angular.z = 0.0;

                servoState.data = true; 
                operationMode.data = 3; 
            }
        
            pub1.publish(operationMode);
            pub2.publish(servoState);
            pub3.publish(wheel_msg);
        }
    }
};

int main (int argc, char **argv)
{
    ros::init(argc, argv, "getBlock"); //Name of the node. Convention is file has same name as node
    ros::NodeHandle nh;

    ros::Rate r(20); // Hz
    Searcher cn = Searcher(&nh);
    while (ros::ok())
        {
            //ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1); To set different rates for subs
            //ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);
            //If rates differ throughout, then can associate publish events into timed callbacks
            
            ros::spinOnce();
            cn.publishAll();
            r.sleep();
        }
    return 0;
}