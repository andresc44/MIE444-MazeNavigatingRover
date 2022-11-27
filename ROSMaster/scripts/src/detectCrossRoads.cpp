#include <ros/ros.h> //always keep
#include <std_msgs/Int8.h> //topic data types
#include <sensor_msgs/LaserScan.h>


class Crossroads {
    private:
        float leftD; //initialize variables
        float rightD;
        float frontD;
        float backD;
        ros::Publisher pub1; //create publisher object
        ros::Subscriber sub1; //subscriber object
        ros::Subscriber sub2; //subscriber object
    
    public:
    Crossroads(ros::NodeHandle *nh) {
        leftD = -1.0;
        rightD = -1.0;
        frontD = -1.0;
        backD = -1.0;

        startingMode = -1;
        pub1 = nh->advertise<std_msgs::Int8>("/operation_mode", 10); //publish to topic1, and set datatype
        sub1 = nh->subscribe("/operation_mode", 15, //topic, queueSize, 
            &Crossroads::callback_mode, this); //callback function

        sub2 = nh->subscribe("/scan", 15, //topic, queueSize, 
            &Crossroads::callback_laser, this); //callback function
        
    }

    void callback_laser(const sensor_msgs::LaserScan& msg) {
        //code to process or clean data before passing to foo

        frontD = msg.range[0]; //units in m
        leftD = msg.range[180];
        backD = msg.range[360];
        rightD = msg.range[540];
    }

    void callback_mode(const std_msgs::Int8& msg) {
        //code to process or clean data before passing to foo
        startingMode = msg.data; //units in mm
    }
    void publishAll() {

        std_msgs::Int8 mode;
        bool path1_config = ((frontD > 0.30) && (leftD > 0.61) && (rightD > 0.61) && (backD > 0.61));
        bool path2_config = ((frontD > 0.61) && (leftD > 0.30) && (rightD > 0.61) && (backD > 0.61))
        if ((path1_config or path2_config) && (startingMode == 3)) {
            mode.data = 4;
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
    Crossroads cn = Crossroads(&nh);
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