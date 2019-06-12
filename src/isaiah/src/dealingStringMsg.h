/* For ros 
 * This roscpp template is written by cthung
 * and by Isaiah (kangaroo02)
*/

// For ROS
#include <ros/ros.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Int16.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"

using namespace std;

class dealingStringMsg
{
    public:
        // Don't move
        dealingStringMsg();                     // Constructor
        ~dealingStringMsg();                    // Destructor

        //void OnStartUp();
        void SubscribedSetting();
	void PublishedSetting();
        void PublishEverything();

        //void Iterate(const ros::TimerEvent&);
        ros::NodeHandle m_nh;                         // Private node handler
        //ros::Timer timer;
        //double m_loopFreq;

        // Publisher
        ros::Publisher lon_msg;                   // Private publisher instance
	ros::Publisher lat_msg;
	ros::Publisher speed_msg;
	ros::Publisher heading_msg;

        // Subscriber
        void cthung_msg_callback(const std_msgs::String::ConstPtr& msg);
        ros::Subscriber sub_cthung;




    private:
        //int m_startup_msg;
        double m_lon;
        double m_lat;
        double m_speed;
        double m_heading;
        
        //bool m_start;
};

