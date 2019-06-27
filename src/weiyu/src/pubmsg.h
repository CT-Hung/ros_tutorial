#include "ros/ros.h"
#include <sstream>
#include <string.h>
#include <iostream>
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float64.h"
using namespace std;

class StringCheck{
    private:
        double lon;
        double lat;
        double heading;
        double speed;
        bool activate;
    public:
        StringCheck();
        ~StringCheck(){};
        void callbackfunc(const std_msgs::String::ConstPtr& msg);
        void advert();
        void publishernode();
        void listener();
        ros::NodeHandle n;
        ros::Publisher pub_msg_act;
        ros::Publisher lon_pub;
        ros::Publisher lat_pub;
        ros::Publisher speed_pub;
        ros::Publisher heading_pub;
        ros::Subscriber suber;
};
