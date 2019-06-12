/* For ros 
 * This roscpp app is written bycthung
*/

// For ROS
#include "pubStringMsg.h"

#include "sstream"
#include "iostream"
/*  Constructor  */
pubStringMsg::pubStringMsg()
{
    m_loopFreq = 4;
    m_lon = 23.5;
    m_lat = 121.34;
    m_speed = 5.5;
    m_heading = 30.2;
    m_start = false;
}

/*  Destructor  */
pubStringMsg::~pubStringMsg()
{
}

/* Set the start varible here from yaml file. */
void pubStringMsg::OnStartUp()
{
    // Import parameter from yaml file
    string key;
    if (ros::param::search("loopFreq", key))
        ros::param::get(key, m_loopFreq);
}

/* Set the publihers here. */
void pubStringMsg::PublishedSetting()
{
    pub_msg = m_nh.advertise<std_msgs::String>("cthung_msg", 10);
}

/* Set the subscribers here. */
void pubStringMsg::SubscribedSetting()
{
    sub_start = m_nh.subscribe("pub_msg", 1000, &pubStringMsg::start_callback, this);
    sub_lon = m_nh.subscribe("NAV_LON", 1000, &pubStringMsg::lon_callback, this);
    sub_lat = m_nh.subscribe("NAV_LAT", 1000, &pubStringMsg::lat_callback, this);
    sub_speed = m_nh.subscribe("NAV_SPEED", 1000, &pubStringMsg::speed_callback, this);
    sub_heading = m_nh.subscribe("NAV_HEADING", 1000, &pubStringMsg::heading_callback, this);
}

/* Set the callback function of subscriber. */
void pubStringMsg::start_callback(const std_msgs::Bool::ConstPtr& msg)
{
    if (msg->data == true)
        m_start = true;
}

void pubStringMsg::lon_callback(const std_msgs::Float64::ConstPtr& msg)
{
    double tmp = msg->data;
    cout << "LON = " << tmp << endl;
    if(tmp == m_lon)
        cout << "LON is correct." << endl;
    else
        cout << "LON is not correct." << endl;
}

void pubStringMsg::lat_callback(const std_msgs::Float64::ConstPtr& msg)
{
    double tmp = msg->data;
    cout << "LAT = " << tmp << endl;
    if(tmp == m_lat)
        cout << "LAT is correct." << endl;
    else
        cout << "LAT is not correct." << endl;
}
void pubStringMsg::speed_callback(const std_msgs::Float64::ConstPtr& msg)
{
    double tmp = msg->data;
    cout << "SPEED = " << tmp << endl;
    if(tmp == m_speed)
        cout << "SPEED is correct." << endl;
    else
        cout << "SPEED is not correct." << endl;
}
void pubStringMsg::heading_callback(const std_msgs::Float64::ConstPtr& msg)
{
    double tmp = msg->data;
    cout << "HEADING = " << tmp << endl;
    if(tmp == m_heading)
        cout << "HEADING is correct." << endl;
    else
        cout << "HEADING is not correct." << endl;
}
/* Loop setting. Do your main thing here. */
void pubStringMsg::Iterate(const ros::TimerEvent&)
{
    if (m_start == true)
    {
        stringstream msg;
        std_msgs::String finalMsg;
        m_lon += 0.23;
        m_lat -= 0.19;
        m_speed += 0.12;
        m_heading += 0.32;
        msg << "LON=" << m_lon;
        msg << ",LAT=" << m_lat;
        msg << ",SPEED=" << m_speed;
        msg << ",HEADING=" << m_heading;
        m_start = false;
        finalMsg.data = msg.str();
        pub_msg.publish(finalMsg);
    }
}

/* main function */ 
/* Don't change this part normally.*/
int main (int argc, char** argv)
{
    // Initialize ROS
    ros::init(argc, argv, "pubStringMsg_node");

    // Create object
    pubStringMsg  pubStringMsg_obj;
    pubStringMsg_obj.OnStartUp();
    pubStringMsg_obj.PublishedSetting();
    pubStringMsg_obj.SubscribedSetting();
    pubStringMsg_obj.timer = pubStringMsg_obj.m_nh.createTimer(ros::Duration(pubStringMsg_obj.m_loopFreq), &pubStringMsg::Iterate, &pubStringMsg_obj);
    ros::spin();

    return 0;
}

