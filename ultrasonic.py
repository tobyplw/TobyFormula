#Libraries
import RPi.GPIO as GPIO
import time
import ledtest as led
 
#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BOARD)
 
#set GPIO Pins
GPIO_TRIGGER = 13
GPIO_ECHO = 18
 
#set GPIO direction (IN / OUT)
GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)
 
def distance():
    # set Trigger to HIGH
    GPIO.output(GPIO_TRIGGER, True)
    # set Trigger after 0.01ms to LOW
    time.sleep(0.00001)
    GPIO.output(GPIO_TRIGGER, False)
    StartTime = time.time()
    StopTime = time.time()
 
    # save StartTime
    while GPIO.input(GPIO_ECHO) == 0:
        StartTime = time.time()
    # save time of arrival
    while GPIO.input(GPIO_ECHO) == 1:
        StopTime = time.time()
    # time difference between start and arrival
    TimeElapsed = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distance = (TimeElapsed * 34300) / 2
 
    return distance

def initDist():
    GPIO.output(GPIO_TRIGGER, GPIO.LOW)
    print ("Waiting for sensor to settle")
    time.sleep(2)
    list =[0.0]*10 
    for i in range(0,10):
        list[i] = distance()
        time.sleep(.2)
    initVal = sum(list)/len(list)

    print(initVal)
    return initVal

def interupt(dist,wall):
    val = False
    #print(dist)
    #print(wall)
    if dist<0.8*wall or dist>1.2*wall:
        print("hand in the way")
        val = True
    return val

def cleanSensor():
    GPIO.cleanup()

def triggerSensor(wall):
    try:
        while not interupt(distance(), wall):
            dist = distance()
            print ("Measured Distance = %.1f cm" % dist)
            time.sleep(.1)
    except KeyboardInterrupt:
        cleanSensor()
    led.lightON()    
    while interupt(distance(), wall):
        print("still obstructed")
        time.sleep(.25)
    return True    
