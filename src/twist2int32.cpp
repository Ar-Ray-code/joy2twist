#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>

class example_cmd_vel:public ros::NodeHandle
{
    private:
        ros::Subscriber sub_cmd_vel;
        ros::Publisher motor0;
        ros::Publisher motor1;
        geometry_msgs::Twist sub_motor;

        void sub_cmd_vel_thread(const geometry_msgs::Twist &msg)
        {
            std_msgs::Int32 motor0_data;
            std_msgs::Int32 motor1_data;

            int z = msg.angular.z;
            int y = msg.linear.y;

            motor0_data.data = int(y/1.5-z/2);
            motor1_data.data = int(y/-1.5-z/2);
            
            motor0.publish(motor0_data);
            motor1.publish(motor1_data);
        }

    public:
        example_cmd_vel()
        {
            sub_cmd_vel = this->subscribe("cmd_vel", 1, &example_cmd_vel::sub_cmd_vel_thread, this);
            motor0 = this->advertise<std_msgs::Int32>("motor0",1);
            motor1 = this->advertise<std_msgs::Int32>("motor1",1);
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cmd_vel_test");
	example_cmd_vel cmd_vel;
    ros::spin();
    ros::shutdown();
    return 0;
}