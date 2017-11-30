 /*
  * file DFRobot_SIM7000_test.ino
  * brief DFRobot's SIM7000 module
  * This example use for get longitude and latitude
  * The positioning function only available in outdoor
  * If you use Mega please connect PIN8 PIN10 and set mySerial(10,7);
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

DFRobot_SIM7000 sim7000;
SoftwareSerial  mySerial(8,7);                                     //Set serial

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    sim7000.begin(mySerial);
    sim7000.turnOFF();
    delay(5000);
    if(sim7000.turnON()){                                          //Turn ON SIM7000
        Serial.println("Turn NO SIM7000");
    }
    if(sim7000.setBaudRate(19200)){                                //Set baud rate from 115200 to 19200
        Serial.println("Set baud rate:19200");
    }else{
        Serial.println("faile to set baud rate");
    }
    while(1){
        if(sim7000.init()){                                        //Init SIM7000
            Serial.println("AT command READY");
            break;
        }else{
            Serial.println("AT command ERROR");
            delay(500);
        }
    }
    while(1){
        if(sim7000.initPos()){
            Serial.println("Positioning function initialized");
            break;
        }else{
            Serial.println("Fail to init positioning function");
            delay(500);
        }
    }
}

void loop(){
    Serial.println("Enter anything to get positioning ");
    char loge[10];
    readSerial(loge);
    Serial.println("Getting position......");
    if(sim7000.getPosition()){                                     //Get the current position
        Serial.print("Longtude :");
        Serial.println(sim7000.getLongitude());                    //Get longitude
        Serial.print("Latitude :");
        Serial.println(sim7000.getLatitude());                     //Get latitude
    }else{
        Serial.println("Wrong data try again");
    }
}

int readSerial(char result[]){
    int i = 0;
    while(1){
        while(Serial.available() > 0){
            char inChar = Serial.read();
            if(inChar == '\n'){
                result[i] = '\0';
                Serial.flush();
                return 0;
            }
            if(inChar != '\r'){
                result[i] = inChar;
                i++;
            }
        }
    }
}