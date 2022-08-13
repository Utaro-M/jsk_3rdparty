#include <msl_hand_interface.h>
#include <m5stack_ros.h>
#include <sensor_msgs/Joy.h>

sensor_msgs::Joy joy_msg;
ros::Publisher joy_pub("joy", &joy_msg);
int pin_list[6] = {12,13,15,16,18,19};
void setup() {
  setupM5stackROS("M5Stack ROS MSL HAND INTERFACE");
  setupMslHandInterface(pin_list);
  nh.advertise(joy_pub);
}

void loop() {

  // Read MslHandInterface
  readMslHandInterface(pin_list);
  displayMslHandInterface();

  // Publish ROS topic
  joy_msg.header.stamp = nh.now();
  joy_msg.buttons = buttons;
  joy_msg.buttons_length = 6;
  joy_pub.publish(&joy_msg);
  nh.spinOnce();

  delay(10);
}
