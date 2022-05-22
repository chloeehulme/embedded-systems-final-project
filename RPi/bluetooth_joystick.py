'''
   Reads in values from serial port sent by paired device via serial bluetooth communication. 
   Then sends out a webhook in response detailing events.
   Uses:  RPi model 3
   Author: Chloe Hulme
'''

import serial
import time
import requests

port = serial.Serial("/dev/rfcomm0", baudrate=9600)


# Sends an HTML POST request to IFTTT for the event 'water'
def dispense():
    r = requests.post('https://maker.ifttt.com/trigger/water/with/key/dH8ev94dnFQG3FdaZNGEn5', params={"value1":"none","value2":"none","value3":"none"})


# Sends an HTML POST request to IFTTT for the event 'retract'
def retract():
    r = requests.post('https://maker.ifttt.com/trigger/retract/with/key/dH8ev94dnFQG3FdaZNGEn5', params={"value1":"none","value2":"none","value3":"none"})


# Reading data from arduino serially.
try:
    while 1:
        value = port.readline().decode()
        print(int(value))
    
        if int(value) > 900:
            dispense()
        
        if int(value) < 100:
            retract()

        time.sleep( 3 )
        
except KeyboardInterrupt:
    print("Measurement stopped by User")
