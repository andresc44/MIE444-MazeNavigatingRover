#include <ros/ros.h> //always keep
#include <std_msgs/Bool.h>
#include <std_msgs/UInt8.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16MultiArray.h>
#include <cmath>
#include <iostream>
  #include <vector>
  using namespace std;

class DirectionCoversion {
    private:
        int block_state;
        bool in_loading_zone;
        
        const float max_F_speed = 0.2490; //!!!!!!BASED ON EXPERIMENTAL DATA UNDER LOAD IN FORWARD DIRECTION m/s !!!!!!!!!!!
        const int pwm_max = 255;
        const float wheel_radius = 0.029; //58mm diam in meters
        const float diam2centre = 0.102; //8cm in meters
        //const float exp_max_rpm = max_F_speed/wheel_radius*60/(2*pi); //conversion for forward speed to max wheel rpm
        //const int max_rpm = 82; //from experimental data, mutl by 2pi/60 for rad/s
        const float max_rps = max_F_speed/wheel_radius; //max rad/s of motor


        //max_lin_vel = max_rps*wheel_radius 0.2490m/s
        //max_rot_vel = max_lin_vel/diam2centre 2.4412rad/s

        //trans_matrix*cmd_vel ./ radius_wheel / max_rad/s
        const double conv_factor = pwm_max/(max_rps*wheel_radius);
        //const double conv_factor = (30/3.1416)/wheel_radius; //rpm values
        const double transform_matrix [3][3] = {
                                    {-0.5*conv_factor, -0.866*conv_factor, -diam2centre*conv_factor}, 
                                    {-0.5*conv_factor, 0.866*conv_factor, -diam2centre*conv_factor},
                                    {1*conv_factor, 0, -diam2centre*conv_factor}
                                    }; //accounts for all unit conversions. When multiplied by cmd_vel, will be pwms

        vector<double> speeds = {0, 0, 0};

        ros::Publisher pub; //create publisher object
        ros::Subscriber sub1; //subscriber object
        ros::Subscriber sub2; //subscriber object
        ros::Subscriber sub3; //subscriber object
    
    public:
    DirectionCoversion(ros::NodeHandle *nh) {
        block_state = 0;
        in_loading_zone = false;
        
        pub = nh->advertise<std_msgs::Int16MultiArray>("/wheelsPWM", 10); //publish to topic1, and set datatype
        sub1 = nh->subscribe("/blockState", 10, //topic, queueSize, 
            &DirectionCoversion::receive_cmd_callback, this); //callback function
        sub2 = nh->subscribe("/inLoadingZone", 10, //topic, queueSize, 
            &DirectionCoversion::loading_zone_callback, this); //callback function
        sub3 = nh->subscribe("/cmd_vel", 10, //topic, queueSize, 
            &DirectionCoversion::receive_cmd_callback, this); //callback function
    }
    void block_state_callback(const std_msgs::UInt8& msg) {
        block_state = msg.data;
    }
    void loading_zone_callback(const std_msgs::Bool& msg) {
        in_loading_zone = msg.data;
    }
    void receive_cmd_callback(const geometry_msgs::Twist& msg) {
        //code to process or clean data before passing to foo
        speeds = { 
                    -msg.linear.y, //converted from standard units to to the right
                    msg.linear.x, //converted to be robot forward
                    msg.angular.z //theta
                };
    }
    
    void publishAll() {
        std_msgs::Int16MultiArray wheel_msg;
        vector<int16_t> pwms;

        if (in_loading_zone && block_state != 3) {
            if (block_state == 0) { //search for block, add code
                pwms = {100, 100, 100}; //rotate rover counter clockwise
            }
            else if (block_state == 1) { //alligned with block, move forward
                pwms = {-100, 100, 0};
            }
            else { //lined up, now stop, block_state == 2
                pwms = {0, 0, 0};
            }
        }
        else { //follow cmd_velocity logic
            //blah blah matrix multiplication
            pwms = {0, 0, 0};
            for(int i=0; i<3;i++){
                for(int j=0;j<3;j++){
                    pwms[i]=pwms[i]+(speeds[j] * transform_matrix[i][j]);
                }
            }

        }
        wheel_msg.data = pwms;  
        //cout << pwms[0]<<" ";
        //cout << pwms[1]<<" "<<pwms[2]<<"\n";     
        pub.publish(wheel_msg);
    }
};

int main (int argc, char **argv)
{
    int sleep_rate = 30.0;
    ros::init(argc, argv, "wheelController"); //Name of the node
    ros::NodeHandle nh;
    //ros::param::get("/wheelController/global_rate", sleep_rate);

    ros::Rate r(sleep_rate); // Hz
    DirectionCoversion dc = DirectionCoversion(&nh);
    while (ros::ok())
        {         
            ros::spinOnce();
            dc.publishAll();
            r.sleep();
        }
    return 0;
}