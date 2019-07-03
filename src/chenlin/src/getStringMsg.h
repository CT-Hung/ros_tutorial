#include <ros/ros.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Int16.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"

using namespace std;

class getStringMsg
{
    public:
        getStringMsg();
        ~getStringMsg();
    
        void SubscribedSetting();
        void PublishedSetting();
        void PublishEverything();

        ros::NodeHandle m_nh;
        ros::Publisher lon_msg;
        ros::Publisher lat_msg;
        ros::Publisher speed_msg;
        ros::Publisher heading_msg;
        //subscriber
        void cthung_msg_callback(const std_msgs::String::ConstPtr& msg);
        ros::Subscriber sub_cthung;    

    private:
        double m_lon;
        double m_lat;
        double m_speed;
        double m_heading;
};
