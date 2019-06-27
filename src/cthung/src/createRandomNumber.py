#!/usr/bin/env python 
# this rospy templete is written by cthung
import rospy 
import random
import time
from std_msgs.msg import Int64, Float64

class createRandomNumber(object):
    def __init__(self):
        # Initulize
        self.loopFreq = 4
        self.order = 10
        self.orderStart = 2

        #On Start up 
        self.OnStartUp()
        random.seed(self.orderStart)

        #Iterate Function
        rospy.Timer(rospy.Duration(self.loopFreq), self.Iterate)

        #Publisher
        self.pub_number = rospy.Publisher("number_msg", Int64, queue_size=1)

    def OnStartUp(self):
        #Set the params at yaml file
        if rospy.has_param('~loopFreq'):
            self.loopFreq = rospy.get_param('~loopFreq')
        if rospy.has_param('~order'):
            self.order = rospy.get_param('~order')
        if rospy.has_param('~orderMin'):
            self.orderStart = rospy.get_param('~orderMin')

    def Iterate(self, event):
        #do ur thing here
        self.sendRandomNumber()

    def sendRandomNumber(self):
        randomOrder = random.randrange(self.orderStart, self.order)
        random.seed(time.time())
        sendNumber = random.randrange(10**self.orderStart, 10**(randomOrder+1))
        self.pub_number.publish(sendNumber)

    def callBack(self, msg):
        self.count = msg.data
        rospy.loginfo("Sub : [%f]", self.count)

    def onShutdown(self):
        rospy.loginfo("[%s] Shutdown." %(self.node_name))

if __name__ == '__main__':
    rospy.init_node('createRandomNumber_node', anonymous=False)
    createRandomNumber_obj = createRandomNumber()
    rospy.on_shutdown(createRandomNumber_obj.onShutdown)
    rospy.spin()

