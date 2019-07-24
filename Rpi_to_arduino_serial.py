#!/usr/bin/python3

import serial
import time

ser=serial.Serial("/dev/ttyUSB0",9600, timeout=5)
time.sleep(1)

while 1:
        print("your desire : ")
        var = input()
        b=bytes( var , 'utf-8' )
        ser.write(b)


        desire2=ser.readline()
        desire2=int( desire2)
        print(desire2)
~                                                                               
~                                                                               
~                                                                               
~        
