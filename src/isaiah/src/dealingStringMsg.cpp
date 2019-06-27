/* For ros practice
* This roscpp app is written by Isaiah (kangaroo02)
*/
// For ROS
#include "dealingStringMsg.h"

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sstream"
#include "iostream"
#include <vector>
#include <string>

/*  Constructor  */
dealingStringMsg::dealingStringMsg()
{
	m_lon = 0;
	m_lat = 0;
	m_speed = 0;
	m_heading = 0;
}

/*  Destructor  */
dealingStringMsg::~dealingStringMsg()
{
}

/*  Set the callback function of subscriber  */
void dealingStringMsg::cthung_msg_callback(const std_msgs::String::ConstPtr& msg){
	string tmp = msg->data.c_str();
	char *c_tmp = new char[tmp.length() + 1];
	strcpy(c_tmp, tmp.c_str());
	ROS_INFO("I heard: [%s]", c_tmp);
    // 設置切割字符
    const char* delim = ",";

    // 切割字串
    char* pch=strtok(c_tmp,delim);
	int index = 0;
    while(pch) {
        //printf("%s  ", pch);
		//int length = strlen(pch);
		//cout << length << endl;
		string nu = strstr(pch, "=");
		nu = nu.erase(0, 1);
		cout << nu << endl;
		stringstream conver(nu);
		if(index == 0){conver >> m_lon;}
		if(index == 1){conver >> m_lat;}
		if(index == 2){conver >> m_speed;}
		if(index == 3){conver >> m_heading;};
		index ++;
        pch=strtok(NULL, delim);
    }
  dealingStringMsg::PublishedSetting();
  dealingStringMsg::PublishEverything();

}


/* Set the subscribers here. */
void dealingStringMsg::SubscribedSetting(){
	sub_cthung = m_nh.subscribe("cthung_msg", 1000, &dealingStringMsg::cthung_msg_callback, this);
	ROS_INFO("Staring eavesdroping\n");
}   

/* Set the publisher here  */
void dealingStringMsg::PublishedSetting(){
	lon_msg = m_nh.advertise<std_msgs::Float64>("NAV_LON", 1000);
	lat_msg = m_nh.advertise<std_msgs::Float64>("NAV_LAT", 1000);
	speed_msg = m_nh.advertise<std_msgs::Float64>("NAV_SPEED", 1000);
	heading_msg = m_nh.advertise<std_msgs::Float64>("NAV_HEADING", 1000);
}



/*  PublishEverything  */
void dealingStringMsg::PublishEverything(){
	std_msgs::Float64 msg;

	msg.data = m_lon;
	lon_msg.publish(msg);
	
	msg.data = m_lat;
	lat_msg.publish(msg);

	msg.data = m_speed;
	speed_msg.publish(msg);

	msg.data = m_heading;
	heading_msg.publish(msg);
}







int main(int argc, char**argv)
{
  // Initialize ROS
  ros::init(argc, argv, "dealingStringMsg_node");

  // Create object
  dealingStringMsg dealingStringMsg_obj;
  //ros::Subscriber sub_dealing = dealingStringMsg_obj.subscribe("cthung_msg", 1000, cthung_msg_callback);
  dealingStringMsg_obj.SubscribedSetting();

  ros::spin();

  return 0;
}
