// #include "std_msgs/msg/float32_multi_array.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

/* ros2 run mpu6050driver pitch_roll */

using std::placeholders::_1;

class PitchRoll : public rclcpp::Node{
public:
    PitchRoll();

private:
float pitch, roll;
rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;


void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg);

};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto pitch_roll = std::make_shared<PitchRoll>();
    rclcpp::spin(pitch_roll);
    rclcpp::shutdown();


}


PitchRoll::PitchRoll(): Node("pitchroll_node"){
    // init subscriber
    imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>("imu", 10, std::bind(&PitchRoll::imu_callback, this, _1));
}

void PitchRoll::imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg){
    auto roll = atan(msg->linear_acceleration.y/sqrt(pow(msg->linear_acceleration.x,2) + pow(msg->linear_acceleration.z, 2))) * 1 / (3.142 / 180);
    auto pitch = atan(-msg->linear_acceleration.x/sqrt(pow(msg->linear_acceleration.y,2) + pow(msg->linear_acceleration.z, 2))) * 1 / (3.142 / 180);
     
    RCLCPP_INFO(this->get_logger(),"Pitch: %f, roll: %f", pitch, roll);
}