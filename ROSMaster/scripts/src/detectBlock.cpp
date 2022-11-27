#include <ros/ros.h> //always keep
#include <std_msgs/Int8.h> //topic data types
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/UInt16.h>


class BlockTracker {
    private:
        int tof_dist; //initialize variables
        int lidar_dist;
        int startingMode;
        ros::Publisher pub1; //create publisher object
        ros::Subscriber sub1; //subscriber object
        ros::Subscriber sub2; //subscriber object
        ros::Subscriber sub3; //subscriber object
    
    public:
    BlockTracker(ros::NodeHandle *nh) {
        tof_dist = 1000;
        lidar_dist = 1000;
        startingMode = -1;
        pub1 = nh->advertise<std_msgs::Int8>("/operation_mode", 10); //publish to topic1, and set datatype
        sub1 = nh->subscribe("/TOF", 15, //topic, queueSize, 
            &BlockTracker::callback_tof, this); //callback function
        sub2 = nh->subscribe("/scan", 15, //topic, queueSize, 
            &BlockTracker::callback_laser, this); //callback function
        sub3 = nh->subscribe("/operation_mode", 15, //topic, queueSize, 
            &BlockTracker::callback_mode, this); //callback function
    }

    void callback_tof(const std_msgs::UInt16& msg) {
        //code to process or clean data before passing to foo
        tof_dist = msg.data;
    }

    void callback_laser(const sensor_msgs::LaserScan& msg) {
        //code to process or clean data before passing to foo
        lidar_dist = 1000*msg.range[0]; //units in mm
    }

    void callback_mode(const std_msgs::Int8& msg) {
        //code to process or clean data before passing to foo
        startingMode = msg.data; //units in mm
    }
    void publishAll() {

        std_msgs::Int8 mode;
        if ((tof_dist + 200 < lidar_dist) && (tof_dist < 400) && (startingMode == 1)) {
            mode.data = 2;
            pub1.publish(mode);
        }
    }
};

int main (int argc, char **argv)
{
    int sleep_rate = 10; //10 Hz
    ros::init(argc, argv, "detectBlock"); //Name of the node
    ros::NodeHandle nh;
    // ros::param::get("/my_param_name", sleep_rate);

    ros::Rate r(sleep_rate); // Hz
    BlockTracker cn = BlockTracker(&nh);
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