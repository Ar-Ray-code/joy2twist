#include "joy/ps_base.hpp"
#define JOY_VERSION PS5

#include <std_msgs/msg/int32.hpp>
#include <geometry_msgs/msg/twist.hpp>

#if JOY_VERSION == PS5
    #include "joy/ps5.hpp"
    using namespace ps5;
#elif JOY_VERSION == PS4
    #include "joy/ps4.hpp"
    using namespace ps4;
#elif JOY_VERSION == PS3
    #include "joy/ps3.hpp"
    using namespace ps3;
#endif

class example_joy:public rclcpp::Node, public ps
{
    public:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist;
        geometry_msgs::msg::Twist send_data;

        void sub_joy_thread(const sensor_msgs::msg::Joy::SharedPtr msg)
        {
            get_data(msg);
            send_data.linear.x = -1*joy_left_x*127;
            send_data.linear.y = joy_left_y*127;
            send_data.angular.z = -1*joy_right_x*127;
            
            twist->publish(send_data);
        } 

        example_joy(const std::string name, const rclcpp::NodeOptions & options):Node(name, options)
        {
            using namespace std::chrono_literals;
            sub_joy = this->create_subscription<sensor_msgs::msg::Joy>("joy", 1, std::bind(&ps::sub_joy_thread, this, std::placeholders::_1));
            twist = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel",1);
        }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto node = std::make_shared<example_joy>("joy_test",options);
	
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}