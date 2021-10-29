
/**
 * This code will be used on the on-board arduino on the Buckeye Formula car. 
 * Its purpose is to receive CAN data and package it via the Google Protocol Buffers format.
 * The packages will be sent with COBS encoding
 * 
 * **THIS CODE IS NOT COMPLETE**
 * **IT WORKS, IT IS NOT YET OPTIMIZED OR EFFICIENT**
 * 
 * Author: Toby Williams, Buckeye Formula Electronics Team
 */


#include <PacketSerial.h>
#include <CAN.h>
#include <pb_encode.h>
#include <pb_common.h>
#include "carProto.pb.h"


//packet serial object
PacketSerial_<COBS> ps;

//initialize function pointer array
void (*extractData[])(char[], int*) = {engineCAN, temperaturesCAN, errorsCAN};

size_t (*packageData[])(int[],pb_ostream_t) = {engineData, temperaturesData, errorsData};
      
int output;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //start the CAN bus at 500 kbps
  CAN.begin(500E3);

  //begin communication with our PacketSerial Object
  ps.begin(&Serial);
  

}

void loop() {

  //check if packet has been received and try to parse packet
  int packetSize = CAN.parsePacket();

  //if packet has been recieved
  if(packetSize!=0){

    //get packet Id
    long id = CAN.packetId();
    
    //Get value of the Data Length Code field of the packet
    int DLC = CAN.packetDlc();
    
    //read Bytes from CAN message into character array
    unsigned char canStreamBuf[8];
    CAN.readBytes(canStreamBuf, DLC);

    //get index for function array
    int canIndex = getIndex(id);
    
    //filter messages (test values for now)
    if(canIndex < 3){
  
      int data[3] = {};
      //get data from can message
      (*extractData[canIndex])(canStreamBuf, data);
      
      //initialize buffer, size, and status
      uint8_t messageBuffer[64]; 

      //create stream that will write to buffer
      pb_ostream_t stream = pb_ostream_from_buffer(messageBuffer, sizeof(messageBuffer));

      //package appropriate data
      size_t message_length = (*packageData[canIndex])(data, stream);
      
      //send packet to PacketSerial object
      ps.send(messageBuffer, message_length);
      Serial.println();
      
      for(int i =0; i<message_length; i++){
        Serial.print(messageBuffer[i]);
      }
      Serial.println();
              
    }
  }
}




int getIndex(int canID){
  int output = 3;

  if(canID == 0xF1){
    output = 0;
  }
  else if(canID == 0xB1){
    output = 1;
  }
  else if(canID == 0xA1){
    output = 2;
  }

  return output;
}

void engineCAN(char canBuffer[], int *data){
  
  int car_speed = canBuffer[0];
  int engine_rpm = canBuffer[1];
  int enginer_gear = canBuffer[2];
  data[0] = car_speed;
  data[1] = engine_rpm;
  data[2] = enginer_gear; 
  
}

void temperaturesCAN(char canBuffer[], int *data){
  
  int engine_temp = canBuffer[0];
  int wheel_temp = canBuffer[1];
  int brake_temp = canBuffer[2];
  data[0] = engine_temp;
  data[1] = wheel_temp;
  data[2] = brake_temp;
  
}

 void errorsCAN(char canBuffer[], int *data){
  
  int error1 = canBuffer[0];
  int error2 = canBuffer[1];
  int error3 = canBuffer[2];
  int error4 = canBuffer[3];
  data[0] = error1;
  data[1] = error2;
  data[2] = error3;
  
}

size_t engineData(int data[], pb_ostream_t stream){

  EngineMessage engine = EngineMessage_init_zero;
  engine.car_speed = data[0];
  engine.rpm = data[1];
  engine.gear = data[2];
  
  //encode message, get status
  bool messageStatus = pb_encode(&stream, EngineMessage_fields, &engine);
  if(!messageStatus){
        Serial.println("Encoding failed");
      }
  size_t message_length = stream.bytes_written;
  return message_length;
}

size_t temperaturesData(int data[], pb_ostream_t stream){

  TempsMessage temps = TempsMessage_init_zero;
  temps.engine_temp = data[0];
  temps.wheel_temp = data[1];
  temps.brake_temp = data[2];
  
  //encode message, get status
  bool messageStatus = pb_encode(&stream, TempsMessage_fields, &temps);
  if(!messageStatus){
        Serial.println("Encoding failed");
      }
  size_t message_length = stream.bytes_written;
  return message_length;
}

size_t errorsData(int data[],pb_ostream_t stream){

  ErrorMessage errors = TempsMessage_init_zero;
  errors.error1 = data[0];
  errors.error2 = data[1];
  errors.error3 = data[2];
  errors.error4 = data[3];
  
  //encode message, get status
  bool messageStatus = pb_encode(&stream, ErrorMessage_fields, &errors);
  if(!messageStatus){
        Serial.println("Encoding failed");
      }
  size_t message_length = stream.bytes_written;
  return message_length;
}
