#!/usr/bin/env python
import rospy 
import math
from std_msgs.msg import Int64

def factorize(data):
    n = data.data
    rospy.loginfo("  ")
    print("%d = " % n)
    for i in range(2, int(math.sqrt(n)+1)):
        while n%i == 0:
            print(i)
            n/=i
    if n>1 :
        print(n)
    else:
        print("")

def listener():
    rospy.init_node('factorization', anonymous="True")
    rospy.Subscriber("number_msg", Int64, factorize)
    
    rospy.spin()

if __name__  == '__main__':
    listener()
