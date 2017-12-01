 /*
  * file  : DFRobot_SIM7000_getPosition.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example use for get longitude and latitude
  *         With initialization completed, we use getPosition() to positioning current position
            Use getLongitude() to get longitude(-180,180), negative is west positive is east
            Use getLatitude() to get latitude(-90,90), negative is south positive is north
  * Note  : If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  *       : The positioning function only available in outdoor
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    sim7000.begin(mySerial);
    sim7000.turnOFF();
    delay(5000);

    Serial.println("Turn ON SIM7000......");
    if(sim7000.turnON()){                                          //Turn ON SIM7000
        Serial.println("Turn ON !");
    }

    Serial.println("Set baud rate......");
    if(sim7000.setBaudRate(19200)){                                //Set baud rate from 115200 to 19200
        Serial.println("Set baud rate:19200");
    }else{
        Serial.println("Faile to set baud rate");
        while(1);
    }

    Serial.println("Check SIM card......");
    if(sim7000.checkSIMStatus()){                                  //Check SIM card
        Serial.println("SIM card READY");
    }else{
        Serial.println("SIM card ERROR");
        while(1);
    }

    Serial.println("Init positioning function......");
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