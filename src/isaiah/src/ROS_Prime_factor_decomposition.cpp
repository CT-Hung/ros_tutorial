//this is written by isaiah yang
//libraries for usage
#include<iostream> 
#include<stdlib.h>
#include<vector>
//libraries for ROS
#include "ros/ros.h"
#include "std_msgs/Int64.h"

using namespace std;
std::vector<int> prime_number_list;
std::vector<int> prime_factor_decomposition(int input_x);
int extend_prime_number_list();
void number_msg_callback(const std_msgs::Int64::ConstPtr& msg);


int main(int argc, char**argv){

    prime_number_list.clear();
    prime_number_list.push_back(2);
   
    ros::init(argc, argv, "dealing_number_msg");

    ros::NodeHandle n;

    ros::Subscriber sub_number = n.subscribe("number_msg", 1000, number_msg_callback);

    ros::spin(); 


    //system("pause"); 
    return 0;
    
}


void number_msg_callback(const std_msgs::Int64::ConstPtr& msg){
    int tmp = msg->data; 
    cout << "I heard: " << tmp << endl;
    vector<int> ans;
    
    
    ans = prime_factor_decomposition(tmp);

    cout << "prime factors is: " << endl; 
    for(int i=0; i<ans.size(); i++){
        cout << ans.at(i) << "  ";
    }
    cout << endl;
}




std::vector<int> prime_factor_decomposition(int input_x) {
    vector<int> prime_factor;
    prime_factor.clear();

    int examined_number = input_x;
    int i=0; 
    bool run = true;
    
    //devide by the prime number list
    while(run){
        if(examined_number % prime_number_list.at(i) == 0){
            examined_number = examined_number/prime_number_list.at(i);
            if(examined_number == 1){
                run = false;
            }

            //don't recount the prime in
            if(prime_factor.empty()){
                prime_factor.push_back(prime_number_list.at(i)); 
            }
            if(prime_factor.back() != prime_number_list.at(i)){
                prime_factor.push_back(prime_number_list.at(i));
            } 
            // do recount the prime
            i--;
        }

        //if the prime is not enought to count
        if(i == prime_number_list.size()-1){ 
            //cout << "extend_prime_list " << extend_prime_number_list() << endl;
            extend_prime_number_list();
        }
    
        i++;
    }
    
    
    return prime_factor;
}








int extend_prime_number_list() {
	int i=0;
	int last_prime = prime_number_list.back();
    //cout << last_prime << " is the last prime" << endl;
    int temp = last_prime + 1;
    //cout << "checking for " << temp << endl;
    
    bool temp_is_prime = false;
    while(!temp_is_prime){
    
    
        bool run = true;

        while(run && i<prime_number_list.size()){
       
            if( temp % prime_number_list.at(i) == 0){
                //cout<< temp <<"isn't a prime"<<endl;
                run = false; 
                temp_is_prime = false;
            }else if (prime_number_list.at(i)*prime_number_list.at(i) > temp ){
                //cout << temp << " is prime" << endl;
                run = false;
                temp_is_prime = true;
            }else{
                i++;
            }
        }

        if(!temp_is_prime){
            temp = temp+1;
            i=0;
        }
    }

    prime_number_list.push_back(temp);
    return temp;
}
     
