/*For ros
 * This roscpp app is written by chen lin
 */


//For ROS
#include "getStringMsg.h"
#include "ros/ros.h"
#include <string>
#include "std_msgs/String.h"
#include "sstream"
#include "iostream"

/*  constuctor  */
getStringMsg::getStringMsg()
{
    m_lon = 0;
    m_lat = 0;
    m_speed = 0;
    m_heading = 0;
        

}
getStringMsg::~getStringMsg()
{
}
void getStringMsg::SubscribedSetting()
{
    sub_cthung = m_nh.subscribe("cthung_msg",1000,&getStringMsg::cthung_msg_callback,this);

}
void getStringMsg::cthung_msg_callback(const std_msgs::String::ConstPtr& msg)
{
    string tmp = msg->data;
    /* cut string */
    int current = 0;
    string sequence[4];
    for(int i = 0; i< 4; i++)
    {
       int first =  tmp.find_first_of("=",current);
       int last = tmp.find_first_of(",",current);
        sequence[i] = tmp.substr(first + 1,last - first- 1 );
        current = last + 1;
    }
    m_lon = stod(sequence[0]);
    cout <<"LON= " <<sequence[0]<<"\n";
    m_lat = stod(sequence[1]);
    cout <<"LAT= " <<sequence[1]<<"\n";
    m_speed = stod(sequence[2]);
    cout<<"SPEED= "<<sequence[2]<<"\n";
    m_heading = stod(sequence[3]);
    cout<<"heading=  "<< sequence[3]<<"\n";
    getStringMsg::PublishedSetting();
    getStringMsg::PublishEverything();
}
//publish setting
void getStringMsg::PublishedSetting()
{
    lon_msg = m_nh.advertise<std_msgs::Float64>("NAV_LON",1000);
    lat_msg = m_nh.advertise<std_msgs::Float64>("NAV_LAT",1000);
    speed_msg = m_nh.advertise<std_msgs::Float64>("NAV_SPEED",1000);
    heading_msg = m_nh.advertise<std_msgs::Float64>("NAV_HEADING",1000);
}
void getStringMsg::PublishEverything()
{
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
    //Initialize ROS
    ros::init(argc, argv, "getStringMsg_node");
    getStringMsg getStringMsg_obj;
    getStringMsg_obj.SubscribedSetting();

    ros::spin();

    return 0;

}
