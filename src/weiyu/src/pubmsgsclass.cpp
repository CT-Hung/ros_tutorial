#include "pubmsg.h"

StringCheck::StringCheck()
{
    lon = 0;
    lat = 0;
    speed = 0;
    heading = 0;
    activate = true;
}

void StringCheck::callbackfunc(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("%s",msg->data.c_str());
    string temp = msg->data.c_str();
    char *tmpc = new char[temp.length()+1];
    strcpy(tmpc, temp.c_str());

    const char* delim = ",";

    char *cut = strtok(tmpc,delim);

    for(int i = 0 ; cut ; i++){
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
        cut = strtok(NULL,delim);
    }
    advert();
    publishernode();
}

void StringCheck::advert(){
    lon_pub = n.advertise<std_msgs::Float64>("NAV_LON",1000);
    lat_pub = n.advertise<std_msgs::Float64>("NAV_LAT",1000);
    speed_pub = n.advertise<std_msgs::Float64>("NAV_SPEED",1000);
    heading_pub = n.advertise<std_msgs::Float64>("NAV_HEADING",1000);
}

void StringCheck::publishernode(){
    std_msgs::Float64 allmsg;
    allmsg.data = lon;
    lon_pub.publish(allmsg);

    allmsg.data = lat;
    lat_pub.publish(allmsg);

    allmsg.data = speed;
    speed_pub.publish(allmsg);

    allmsg.data = heading;
    heading_pub.publish(allmsg);
}

void StringCheck::listener(){
    std_msgs::Bool acti;
    acti.data = activate;
    pub_msg_act = n.advertise<std_msgs::Bool>("pub_msg",1000);
    pub_msg_act.publish(acti);
    suber = n.subscribe("cthung_msg",1000,&StringCheck::callbackfunc,this);
}

int main(int argc, char **argv){
    ros::init(argc,argv,"pubmsgs");
    StringCheck a;
    a.listener();
    ros::spin();
}
