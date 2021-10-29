#include <LiquidCrystal.h>
#include <HC595.h>
//HC595 library is written by
//j-bellavance. (2016). HC595. Retrieved from github: https://github.com/j-bellavance/HC595  
//used for simplified use of shift registers in series

const int chipCount = 3;  // Number of serialy connected 74HC595 (8 maximum)
const int latchPin = 5;  // Pin ST_CP (12) of the 74HC595
const int clockPin = 6;  // Pin SH_CP (11) of the 74HC595
const int dataPin = 4;   // Pin DS (14) of the 74HC595

//define pins constants
const int XPin =A0;
const int YPin =A1;
int JoyValX=500;
int JoyValY=500;
int HighBound=800;
int LowBound = 200;


//initialize Color array for each LED
int Colors1[3]= {ON, ON, ON};
int Colors2[3]= {ON, ON, ON};
int Colors3[3]= {ON, ON, ON};
int Colors4[3]= {ON, ON, ON};
int Colors5[3]= {ON, ON, ON};
int Colors6[3]= {ON, ON, ON};
int Colors7[3]= {ON, ON, ON};
int Colors8[3]= {ON, ON, ON};
int Flash[3] ={OFF, OFF, OFF};

//set up shift register outputs for each LED
int LED1[3]= {0, 1, 2};
int LED2[3]= {3, 4, 5};
int LED3[3]= {6, 7, 8};
int LED4[3]= {9, 10, 11};
int LED5[3]= {12, 13, 14};
int LED6[3]= {15, 16, 17};
int LED7[3]= {18, 19, 20};
int LED8[3]= {21, 22, 23};

//initialize selection variable for each LED
int selection = 1;
int Colors1Sel =6;
int Colors2Sel =6;
int Colors3Sel =6;
int Colors4Sel =6;
int Colors5Sel =6;
int Colors6Sel =6;
int Colors7Sel =6;
int Colors8Sel =6 ;


//set up status variable for each LED
int status1=0;
int status2=0;
int status3=0;
int status4=0;
int status5=0;
int status6=0;
int status7=0;
int status8=0;

int totalStatus=0;

//answer key for each LED
int Correct1[3]= {OFF, OFF, ON}; //Blue
int Correct2[3]= {OFF, ON, OFF};//Green
int Correct3[3]= {ON, ON, OFF};//Yellow
int Correct4[3]= {ON, ON, ON};//White
int Correct5[3]= {ON, OFF, ON};//Purple
int Correct6[3]= {OFF, ON, OFF};//Green
int Correct7[3]= {ON, OFF, OFF};//Red
int Correct8[3]= {ON, ON, ON};//White


//set up LCD screen
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


//Set up ledArray class
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);
int lastPin = ledArray.lastPin();


void setup() {


lcd.begin(16,2);


 ledArray.reset();
 randomSeed(analogRead(A0)); //nothing connected to A0

//setup joystick
  pinMode(XPin, INPUT);
  pinMode(YPin, INPUT);

//start LEDs on white
Color(Colors1, LED1);
Color(Colors2, LED2);
Color(Colors3, LED3);
Color(Colors4, LED4);
Color(Colors5, LED5);
Color(Colors6, LED6);
Color(Colors7, LED7);
Color(Colors8, LED8);


}

void loop() {

//loop to determine if all LEDs are set to the correct color
while(totalStatus!=8){

//read in x-axis input and determine appropriate LED selection
JoyValX=analogRead(XPin);
selection= DeterminePosition(JoyValX, selection);

//switch case based on active selection
switch (selection){

case 1:

JoyValX=525;

  //while x-axis on joystick is not moved out of bounds
  while(JoyValX<HighBound && JoyValX>LowBound){
   JoyValX=analogRead(XPin);
     
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED1);
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Colors1, LED1);
    JoyValY=analogRead(YPin);

    //determine which color the LED is on
    Colors1Sel=NextColor(Colors1, LED1, Colors1Sel, JoyValY);

    //check answer key and update status
    status1=checkAnswer(Colors1, Correct1);

  }

  break;

case 2:

JoyValX=525;
  while(JoyValX<HighBound && JoyValX>LowBound){
    
    JoyValX=analogRead(XPin);
     
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED2);
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Colors2, LED2);
    JoyValY=analogRead(YPin);

    Colors2Sel=NextColor(Colors2, LED2, Colors2Sel, JoyValY);
    status2=checkAnswer(Colors2, Correct2);
  }

  break;


case 3:
 
JoyValX=525;
  while(JoyValX<HighBound && JoyValX>LowBound){
    JoyValX=analogRead(XPin);
    
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED3);
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Colors3, LED3);
    JoyValY=analogRead(YPin);

    Colors3Sel=NextColor(Colors3, LED3, Colors3Sel, JoyValY);
    status3=checkAnswer(Colors3, Correct3);
  
}
  break;


case 4:
 
JoyValX=525;
  while(JoyValX<HighBound && JoyValX>LowBound){
    JoyValX=analogRead(XPin);
     
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED4);
    delay(200);
    Color(Colors4, LED4);
    JoyValY=analogRead(YPin);

    Colors4Sel=NextColor(Colors4, LED4, Colors4Sel, JoyValY);
    status4=checkAnswer(Colors4, Correct4);
  
}
  break;


case 5:
 
JoyValX=525;
  while(JoyValX<HighBound && JoyValX>LowBound){
    JoyValX=analogRead(XPin);
     
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED5);
    delay(200);
    Color(Colors5, LED5);
    JoyValY=analogRead(YPin);

    Colors5Sel=NextColor(Colors5, LED5, Colors5Sel, JoyValY);
    status5=checkAnswer(Colors5, Correct5);
  
}
  break;


case 6:
 
JoyValX=525;
  while(JoyValX<HighBound && JoyValX>LowBound){
    JoyValX=analogRead(XPin);
     
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED6);
    delay(200);
    Color(Colors6, LED6);
    JoyValY=analogRead(YPin);

    Colors6Sel=NextColor(Colors6, LED6, Colors6Sel, JoyValY);
    status6=checkAnswer(Colors6, Correct6);
  
}
  break;


case 7:
 
JoyValX=525;
  while(JoyValX<HighBound && JoyValX>LowBound){
    JoyValX=analogRead(XPin);
     
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED7);
    delay(200);
    Color(Colors7, LED7);
    JoyValY=analogRead(YPin);

    Colors7Sel=NextColor(Colors7, LED7, Colors7Sel, JoyValY);
    status7=checkAnswer(Colors7, Correct7);
  
}
  break;


case 8:
 
JoyValX=525;
  while(JoyValX<HighBound && JoyValX>LowBound){
    JoyValX=analogRead(XPin);
     
    delay(200);
    JoyValX=analogRead(XPin);
    Color(Flash,LED8);
    delay(200);
    Color(Colors8, LED8);
    JoyValY=analogRead(YPin);

    Colors8Sel=NextColor(Colors8, LED8, Colors8Sel, JoyValY);
    status8=checkAnswer(Colors8, Correct8);
  
}
  break;
  
}

//determine total status based on each LEDs status
totalStatus=status1+status2+status3+status4+status5+status6+status7+status8;


}

//set all LEDs to Green
GREEN(Colors1, LED1);
GREEN(Colors2, LED2);
GREEN(Colors3, LED3);
GREEN(Colors4, LED4);
GREEN(Colors5, LED5);
GREEN(Colors6, LED6);
GREEN(Colors7, LED7);
GREEN(Colors8, LED8);

//print out code
lcd.print("Code:6739");

//infinite loop
while(true){

}


}//end loop()




//this function changes the color on of the LED
//it takes in both the Status array and the pin array and uses the ledArray class to set the pins
void Color(int Status[], int LED[]){
  for(int i =0;i<3;i++){
    ledArray.setPin(LED[i], Status[i]);  
  }
}

//these function turn on and off specific colors
void OffRed(int *Colors, int LED[]){
  Colors[0]=OFF;
  ledArray.setPin(LED[0], Colors[0]);
}

void OnRed(int *Colors, int LED[]){
  Colors[0]=ON;
  ledArray.setPin(LED[0], Colors[0]);
}

void OffGreen(int *Colors, int LED[]){
  Colors[1]=OFF;
  ledArray.setPin(LED[1], Colors[1]);
}

void OnGreen(int *Colors, int LED[]){
  Colors[1]=ON;
  ledArray.setPin(LED[1], Colors[1]);
}


void OffBlue(int *Colors, int LED[]){
  Colors[2]=OFF;
  ledArray.setPin(LED[2], Colors[2]);
}

void OnBlue(int *Colors, int LED[]){
  Colors[2]=ON;
  ledArray.setPin(LED[2], Colors[2]);
}



void RED(int *Colors, int LED[]){
  OffBlue(Colors, LED);
  OffGreen(Colors, LED);
  OnRed(Colors, LED);
  Color(Colors, LED);
}

void BLUE(int *Colors, int LED[]){
  OffRed(Colors, LED);
  OffGreen(Colors, LED);
  OnBlue(Colors, LED);
  Color(Colors, LED);
}

void GREEN(int *Colors, int LED[]){
  OffRed(Colors, LED);
  OffBlue(Colors, LED);
  OnGreen(Colors, LED);
  Color(Colors, LED);
}

void YELLOW(int *Colors, int LED[]){
  OnRed(Colors, LED);
  OnGreen(Colors, LED);
  OffBlue(Colors, LED);
  Color(Colors, LED);
}

void PURPLE(int *Colors, int LED[]){
  OnRed(Colors, LED);
  OnBlue(Colors, LED);
  OffGreen(Colors, LED);
  Color(Colors, LED);
}

void WHITE(int *Colors, int LED[]){
  OnRed(Colors, LED);
  OnBlue(Colors, LED);
  OnGreen(Colors, LED);
  Color(Colors, LED);
}

void CYAN(int *Colors, int LED[]){
  OffRed(Colors, LED);
  OnBlue(Colors, LED);
  OnGreen(Colors, LED);
  Color(Colors, LED);
}


//this function determines the LEDs next color based on the y-axis joystick input
int NextColor(int *Colors, int LED[], int Selection, int yVal){
  int HighBound=900;
  int LowBound=200;

if (JoyValY >HighBound){
    Selection++;
    if(Selection>7){
      Selection=1;
    }
  }

  if(JoyValY <LowBound){
    Selection--;
    if(Selection<1){
      Selection=7;
    }
  }
  
 ChangeColor(Colors, LED, Selection);

 return Selection;
  
}

//this function changes the Color of the led based on its color selection determined in NextColor
void ChangeColor(int *Colors, int LED[], int Selection){
switch (Selection) {
  
  case 1:
    RED(Colors, LED);
  break;
  
  case 2:
    BLUE(Colors, LED);
  break;
  
  case 3:
    GREEN(Colors, LED);
  break;
  
  case 4:
    YELLOW(Colors, LED);
  break;
  
  case 5:
    PURPLE(Colors, LED);
  break;
  
  case 6:
    WHITE(Colors, LED);
  break;
  
  case 7:
    CYAN(Colors, LED);
  break;
  }
}

//this function determines which LED is active based on systems current selection and joystick input
int DeterminePosition(int xVal, int selection){

if(JoyValX<200){
  selection--;
  if(selection<1){
    selection=8;
  }
}

if(JoyValX>800){
  selection++;
  

  if(selection>8){
    selection=1;
  }
}
  return selection;
}


//this function iterates through the LEDs current color array and its correct color array to see if they match
int checkAnswer(int Colors[],int Correct[]){
    int total=0;
    int output=0;
    
    for(int i =0; i<3;i++){
      if(Correct[i]==Colors[i]){
        total++;
      }
    }
    
    if(total==3){
      output=1;
    }
    return output;
}
