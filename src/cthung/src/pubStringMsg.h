/* For ros 
 * This roscpp template is written by cthung
*/

// For ROS
#include <ros/ros.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Int16.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"

using namespace std;

class pubStringMsg
{
    public:
        // Don't move
        pubStringMsg();                     // Constructor
        ~pubStringMsg();                    // Destructor
        void OnStartUp();
        void SubscribedSetting();
        void PublishedSetting();
        void Iterate(const ros::TimerEvent&);
        ros::NodeHandle m_nh;                         // Private node handler
        ros::Timer timer;
        double m_loopFreq;

        // Publisher
        ros::Publisher pub_msg;                   // Private publisher instance

        // Subscriber
        void start_callback(const std_msgs::Bool::ConstPtr& msg);
        ros::Subscriber sub_start;
        void lon_callback(const std_msgs::Float64::ConstPtr& msg);
        ros::Subscriber sub_lon;
        void lat_callback(const std_msgs::Float64::ConstPtr& msg);
        ros::Subscriber sub_lat;
        void speed_callback(const std_msgs::Float64::ConstPtr& msg);
        ros::Subscriber sub_speed;
        void heading_callback(const std_msgs::Float64::ConstPtr& msg);
        ros::Subscriber sub_heading;

    private:
        int m_startup_msg;
        double m_lon;
        double m_lat;
        double m_speed;
        double m_heading;
        
        bool m_start;
};

