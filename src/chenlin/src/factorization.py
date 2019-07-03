#!/usr/bin/env python
import rospy
from std_msgs.msg import Int64

def callback(data):
    n = data.data
    print 'data.data is ' + str(n)
    d = 2
    while d*d <= n:
        while (n % d)== 0:
            print(d)
            
            n /= d
        d += 1
    if n > 1:
        print n 
            
def factorization ():

    rospy.init_node('factorization',anonymous =True)

    rospy.Subscriber("number_msg",Int64, callback)
    rospy.spin()
if __name__ == '__main__':
    factorization()

