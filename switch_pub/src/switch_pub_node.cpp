#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <pigpiod_if2.h>

#define pin 21 //pin_number

int main(int argc, char **argv){

	ros::init(argc, argv, "switch_pub_node");
	ros::NodeHandle nh;

	ros::Publisher switch_pub = nh.advertise<std_msgs::Bool>("switch_state",100);
	ros::Rate loop_rate(10);

	int pi = pigpio_start(0, 0);
	set_pull_up_down(pi, pin, PI_PUD_DOWN);

	while(ros::ok())
	{
		std_msgs::Bool state;

		if(gpio_read(pi, pin) == 1)
		{
			state.data = true;
			ROS_INFO("ON");
		}
		else
		{
			state.data = false;
			ROS_INFO("OFF");
		}
	
	switch_pub.publish(state);
	loop_rate.sleep();
	
	}

	pigpio_stop(pi);
	return 0;
}
