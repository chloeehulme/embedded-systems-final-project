'''
   Tests for the presence of a cup in front of the ultrasonic sensor and triggers a webhook in response.
   Uses:  RPi model 3, H-SR04 Ultrasonic Distance Sensor, Resistor
   Author: Chloe Hulme
'''

import RPi.GPIO as GPIO
import time
import requests
 
# GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)
 
# GPIO/variable setup
TRIG = 18
ECHO = 24

GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)


# Returns the current distance of a solid object
def get_distance():

    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    StartTime = time.time()
    StopTime = time.time()
 
    # Get StartTime
    while GPIO.input(ECHO) == 0:
        StartTime = time.time()
 
    # Get time of echo
    while GPIO.input(ECHO) == 1:
        StopTime = time.time()
 
    # Time difference between start and arrival
    TimeElapsed = StopTime - StartTime

    # Multiply with speed of sound (34300 cm/s)
    # divide by 2 as sounds travels there and back
    distance = TimeElapsed * 17150
 
    return distance
 

try:
    while 1:
        # Sends an HTML POST request to IFTTT for the event 'cup in front', else for the event 'not in front'
        if get_distance() < 10:
            r = requests.post('https://maker.ifttt.com/trigger/cup_in_front/with/key/dH8ev94dnFQG3FdaZNGEn5',
                              params={"value1":"none","value2":"none","value3":"none"})
            time.sleep(5)
        else:
            r = requests.post('https://maker.ifttt.com/trigger/not_in_front/with/key/dH8ev94dnFQG3FdaZNGEn5',
                              params={"value1":"none","value2":"none","value3":"none"})
            time.sleep(5)

        # kill command CTRL + C
except KeyboardInterrupt:
    print("Measurement stopped by User")
    GPIO.cleanup()
