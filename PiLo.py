#!/usr/bin/python2.7
#PiLO.py
#Python version of PiLo
import serial
import time

class PiLo:

    def __init__(self):
        print("Loading up serial communication...")
        self.ser = serial.Serial(port='/dev/ttyUSB0', baudrate=19200)
        print("waiting for port to come online")
        time.sleep(1)
        if self.ser.isOpen:
            print("Port is working")
        else:
            print("Could not establish, please check the pins are in the right sockets and the EEPROM has been set correctly")
            exit(1)

    def sendLine(self, l):
        output= ""
        for c in l:
            output += c
            if len(output) == 8:
                self.ser.write(output.encode('utf-8'))
                self.ser.flush()
                output = ""
                time.sleep(0.000001)
        self.ser.write(output.encode('utf-8'))
        self.ser.flush()

    def sendCommand(self, t, l, r):
        print("Command type: " + ["TICK","SPEED"][t])
        com = ["MOVE","GO"][t] + ":{}:{}\r".format(l, r)
        self.sendLine(com)

        return com

if __name__ == "__main__":
    p = PiLo()
    print("Driving forward 20 ticks, if the robot doesn't move, you've done something wrong")
    p.sendCommand(0, 1, 1) #this shouldnt move the robot, but will warm up the servos
    p.sendCommand(0, 50, 50)
    time.sleep(1)
    p.sendCommand(0, -50, 52)
    time.sleep(1)
    p.sendCommand(0,50,50)
    time.sleep(1)
    p.sendCommand(0, 52, -50)
    time.sleep(1)
    print("done")
