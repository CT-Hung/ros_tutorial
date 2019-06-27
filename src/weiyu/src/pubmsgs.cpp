#include "ros/ros.h"
#include <sstream>
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float64.h"
#include <string.h>
#include <iostream>
using namespace ros;
using namespace std;

double lon = 0 , lat = 0 , speed = 0 , heading = 0;

void callbackfunc(const std_msgs::String::ConstPtr& msg){
    string temp = msg->data.c_str();
    char *tmpc = new char[temp.length()+1];
    strcpy(tmpc, temp.c_str());
    
    const char* delim = ",";

    char *cut = strtok(tmpc,delim);
    
    int i = 0;
    while(cut){
        string a = strstr(cut, "=");
        a.erase(0,1);
        stringstream pub_out(a);
        switch(i){
            case 0:
                pub_out >> lon;
                break;
            case 1:
                pub_out >> lat;
                break;
            case 2:
                pub_out >> speed;
                break;
            case 3:
                pub_out >> heading;
                break;
        }
        i++;
        cut = strtok(NULL,delim);
    }

}

int main (int argc, char **argv){
    init(argc,argv,"pubmsgs_node");
    std_msgs::Float64 allmsg;
    std_msgs::Bool activate;
    NodeHandle n;
    
    Publisher lon_pub = n.advertise<std_msgs::Float64>("NAV_LON",1000);
    Publisher lat_pub = n.advertise<std_msgs::Float64>("NAV_LAT",1000);
    Publisher speed_pub = n.advertise<std_msgs::Float64>("NAV_SPEED",1000);
    Publisher heading_pub = n.advertise<std_msgs::Float64>("NAV_HEADING",1000);
    Publisher pub_msg_pub = n.advertise<std_msgs::Bool>("pub_msg",1000);
    Rate loop_rate(10);
    while(ok()){
        activate.data = true;
        pub_msg_pub.publish(activate);
        
        Subscriber sub = n.subscribe("cthung_msg",1000,callbackfunc);
        allmsg.data = lon;
        lon_pub.publish(allmsg);
    
        allmsg.data = lat;
        lat_pub.publish(allmsg);

        allmsg.data = speed;
        speed_pub.publish(allmsg);

        allmsg.data = heading;
        heading_pub.publish(allmsg);
        loop_rate.sleep();
        spin();
        
    }
}
