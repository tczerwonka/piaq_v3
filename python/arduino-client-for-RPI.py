#!/usr/bin/python

## 22 November 2015
## T. Czerwonka tczerwonka@gmail.com
## Mon 22 May 22:18:03 CDT 2017
##  updates to run on an RPI
## Mon May 29 00:14:31 CDT 2017
##  flash some gpio lights

import sys
import time
import os
import platform 
import subprocess
import serial
import re
from array import array
from socket import socket
import RPi.GPIO as GPIO





WAITING = 0
READING = 1
DONE = 2
RED = 5
YELLOW = 26
stream_state = WAITING
location = "basement"
GPIO.setmode(GPIO.BCM)
GPIO.setup(RED, GPIO.OUT)
GPIO.setup(YELLOW, GPIO.OUT)


CARBON_SERVER = '192.168.1.101'
CARBON_PORT = 2003


sock = socket()
try:
  sock.connect( (CARBON_SERVER,CARBON_PORT) )
except:
  print "Couldn't connect to %(server)s on port %(port)d, is carbon-agent.py running?" % { 'server':CARBON_SERVER, 'port':CARBON_PORT }
  sys.exit(1)



#open serial port for reading
#ser = serial.Serial('/dev/ttyAMA0', 9600)
#serial0 for raspberry pi 3
ser = serial.Serial('/dev/serial0', 9600)
line = []
carbondata = []
#reset the arduino -- the internal program waits two seconds
#not going to happen on the rpi
#ser.setDTR(False)
#time.sleep(1)
#ser.flushInput()
#ser.setDTR(True)

while stream_state != DONE:
	GPIO.output(26, GPIO.HIGH)
	for c in ser.read():
		if stream_state == WAITING:
        		#found EOF character from previous burst -- all after this is valid
        		if c == '\x18': 
				stream_state = READING
				break

        	#found EOF character -- we're done now
		if stream_state == READING:
        		if c == '\x18':
				stream_state = DONE
				break
			#ignore newline, tab, octothorpe
			if c == "\r": break
			if c == "\t": break
			if c == "#": break
			if c != "\n":
        			line.append(c)
        		if c == '\n':
  				now = int( time.time() )
				foo = array('B', map(ord,line)).tostring()
				#sometimes we get an empty line
				if foo == "": break
				#prepend house.environment
				foo = ''.join(('house.environment.',foo))
				#substitute location
				foo = re.sub(r'\$\$\$', location, foo)
				#debugging
            			print(foo)
  				carbondata.append("%s %d" % (foo,now))
            			line = []
            		break

		#we're done here
		if stream_state == DONE:
			ser.close()
			break

GPIO.output(26, GPIO.LOW)

message = '\n'.join(carbondata) + '\n' #all lines must end in a newline
#print "sending message\n"
#print message
sock.sendall(message)

sys.exit(0)

