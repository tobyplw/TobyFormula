import cv2
import numpy as np
import os
import statistics 
from venmo_api import Client
import ultrasonic as us
import time
import button as button
import ledtest as led
def init():
    led.lightOFF()
    if button.button_push():
        wall = us.initDist()

    print(wall)
    return wall

def requestMoney(buyIndex):
                    
    if buyIndex!=0 and  buyIndex!=2:
        accounts = ['None', 'pettyzach','Tobyplw','Will-Blanton-8']
        sendTo = accounts[buyIndex]
        vendor = Client("edee12d099518ad5edeca9f08bac4acb59da0287572b9bba87b51fba42e79e11")        
        #get user ID
        buyer = vendor.user.get_user_by_username(sendTo)

        #request money
        try:
            vendor.payment.request_money(.5, "Drink expense", buyer.id)
        except:
            print("Error: can't find user")

    else:
        print("ID wasnt valid")



recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('../trainer/trainer.yml')
cascadePath = "../Cascades/haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath);

font = cv2.FONT_HERSHEY_SIMPLEX


# names related to ids: example ==> Marcelo: id=1,  etc
names = ['None', 'Zach', 'Toby', 'Will'] 

# venmo accounts related to ids


# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height

# Define min window size to be recognized as a face
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)


def getFace():
    id = 0
    counter = 0
    id_array = [0] * 25
    while counter < 25:
        ret, img =cam.read()
        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
        faces = faceCascade.detectMultiScale( 
            gray,
            scaleFactor = 1.2,
            minNeighbors = 5,
            minSize = (int(minW), int(minH)),
       )
        maxID = 0
        maxConfidence = 100
        for(x,y,w,h) in faces:
            cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)
            id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
            
            #print(confidence)
            #print(id)
            if confidence < maxConfidence:
                maxID = id

            # Check if confidence is less them 100 ==> "0" is perfect match 
            if (confidence < 100):
               # culprit = accounts[id]
                #id = names[id]
                confidence = "  {0}%".format(round(100 - confidence))
            else:
                #id = "unknown"
                confidence = "  {0}%".format(round(100 - confidence))
        
            cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
            cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)  
        
        id_array[counter] = maxID
        counter+=1
        cv2.imshow('camera',img) 

        k = cv2.waitKey(10) & 0xff # Press 'ESC' for exiting video
        if k == 27:
            break
    print(id_array)
    captured = 0

    try:
        captured = statistics.mode(id_array)
        print(captured)
    except StatisticsError:
        captured = 0

    return(captured)



def main():
    wall = init()
    i = 0
    try: 
        while True:
            #if sensor gets triggered
            if us.triggerSensor(wall):
                #get face ID and then request money
                print("Find face")
                time.sleep(2)
                requestMoney(getFace())
                time.sleep(1)
            led.lightOFF()
    except KeyboardInterrupt:
        # Do a bit of cleanup
        print("\n [INFO] Exiting Program and cleanup stuff")
        cam.release()
        cv2.destroyAllWindows()
        us.cleanSensor()

if __name__ == "__main__":
    main()

