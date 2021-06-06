#include "joy/ps_base.hpp"
// #include "../joy2twist/include/joy2twist/joy/ps_base.hpp"
#include "joy/ps5.hpp"

#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>

#define JOY_VERSION PS5

using namespace ps5;

class example_joy:public ros::NodeHandle, public ps
{
    private:
        ros::Publisher twist;
        geometry_msgs::Twist send_data;

        void sub_joy_thread(const sensor_msgs::Joy &msg)
        {
            get_data(msg);
            send_data.linear.x = -1*joy_left_x*127;
            send_data.linear.y = joy_left_y*127;
            send_data.angular.z = -1*joy_right_x*127;
            
            twist.publish(send_data);
        }

    public:
        example_joy()
        {
            sub_joy = this->subscribe("joy", 1, &example_joy::sub_joy_thread, this);
            twist = this->advertise<geometry_msgs::Twist>("cmd_vel",1);
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "joy_test");
	example_joy joy;
    ros::spin();
    ros::shutdown();
    return 0;
}