#!/usr/bin/env python 
# this rospy templete is written by cthung
import rospy 
from std_msgs.msg import Int64
from cthung.msg import PrimeMsg
from collections import deque

class primeFactor(object):
    def __init__(self):
        # Initulize
        self.loopFreq = 4
        self.inputNumber = deque()
        self.haltNumber = deque()
        self.inputcount = 0
        self.outputcount = 0
        self.primeList = [2]

        #On Start up 
        self.OnStartUp()

        #Iterate Function
        rospy.Timer(rospy.Duration(self.loopFreq), self.Iterate)

        #Publisher
        self.pub_prime = rospy.Publisher("pub_prime", PrimeMsg, queue_size=1)

        #Subscriber
        self.sub_number = rospy.Subscriber("number_msg", Int64, self.callBack, queue_size=1)

    def OnStartUp(self):
        #Set the params at yaml file
        if rospy.has_param('~loopFreq'):
            self.loopFreq = rospy.get_param('~loopFreq')
        if rospy.has_param('~count'):
            self.count = rospy.get_param('~count')

    def Iterate(self, event):
        #do ur thing here
        self.primeSolver()
       # rospy.loginfo("Iterate : [%f]", self.count)
       # self.pub_bar.publish(self.count)

    def primeSolver(self):
        if len(self.inputNumber) > 0:
            number, inputID, prime = self.firstSolve()
            self.primeList.sort()
            self.publishInfo(number, inputID, prime)

    def firstSolve(self):
        number, inputID = self.inputNumber.popleft()
        solvedPrime = deque()
        finishedFlag, lastNumber, knownPrime = self.knownPrimeSlover(number)
        solvedPrime += knownPrime
        if finishedFlag == True:
            return number, inputID, slovedPrime
        finishedFlag, lastNumber, newPrime = self.primeFinder(lastNumber, self.primeList[-1])
        solvedPrime += newPrime
        return number, inputID, solvedPrime


    def knownPrimeSlover(self, inputNumber):
        tmp = inputNumber
        prime = deque()
        for i in range(0,len(self.primeList)):

            if tmp < self.primeList[i]:
                return(False, tmp, prime)
            elif tmp % self.primeList[i] == 0:
                prime.append(self.primeList[i])
            while tmp % self.primeList[i] == 0:
                tmp = tmp/self.primeList[i]
            if tmp == 1:
                return(True, tmp, prime)
        return(False, tmp, prime)

    def primeFinder(self, inputNumber, startFind):
        tmp = inputNumber
        prime = deque()
        if inputNumber**0.5 < startFind+1:
            prime.append(inputNumber)
            return(True, inputNumber, prime) 

        for i in range(3, int(inputNumber**0.5)):
            if tmp % i == 0:
                prime.append(i)
                self.primeList.append(i)
            while tmp % i == 0:
                tmp = tmp/i
        if tmp != 1:
            prime.append(tmp)
        return(True, tmp, prime)

    def publishInfo(self, number, inputID, prime):
        msg = PrimeMsg()
        self.outputcount = self.outputcount+1
        msg.Number = str(number)
        msg.InputID = str(inputID)
        msg.OutputID = str(self.outputcount)
        msg.Prime = ""
        #msg.Prime = str(prime[0])
        for i in prime:
            msg.Prime = msg.Prime+str(i)+","
        self.pub_prime.publish(msg)

    def callBack(self, msg):
        self.inputcount = self.inputcount+1
        self.inputNumber.append((msg.data, self.inputcount))

    def onShutdown(self):
        rospy.loginfo("[%s] Shutdown." %(self.node_name))

if __name__ == '__main__':
    rospy.init_node('primeFactor_node', anonymous=False)
    primeFactor_obj = primeFactor()
    rospy.on_shutdown(primeFactor_obj.onShutdown)
    rospy.spin()

