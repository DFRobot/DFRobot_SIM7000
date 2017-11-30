 /*
  * file  : DFRobot_SIM7000_TCP.ino
  * brief : DFRobot's SIM7000 module
  * Power : SIM7000 needs 7-12V DC power supply
  * This example Send an HTTP request to www.dfrobot.com and receive the return data
  * If you use Mega please connect PIN8 PIN10 and set mySerial(10,7);
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;
static char        buff[350];

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    sim7000.begin(mySerial);
    sim7000.turnOFF();
    delay(5000);
    Serial.println("Turn ON SIM7000......");
    if(sim7000.turnON()){                                                                      //Turn ON SIM7000
        Serial.println("Turn ON !");
    }
    Serial.println("Set baud rate......");
    if(sim7000.setBaudRate(19200)){                                                            //Set baud rate from 115200 to 19200
        Serial.println("Set baud rate:19200");
    }else{
        Serial.println("Faile to set baud rate");
        while(1);
    }
    Serial.println("Check SIM card......");
    if(sim7000.checkSIMStatus()){                                                              //Check SIM card
        Serial.println("SIM card READY");
    }else{
        Serial.println("SIM card ERROR");
        while(1);
    }
    delay(500);
    Serial.println("Set net mod......");
    if(sim7000.setNet(NB)){                                                                    //Set net mod NB-IOT
        Serial.println("Set NB-IOT mode");
    }else{
        Serial.println("Fail to set mode");
    }
    Serial.println("Get signal quality......");
    delay(500);
    signalStrength=sim7000.checkSignalQuality();                                               //Check signal quality from (0-30)
    Serial.print("signalStrength =");
    Serial.println(signalStrength);
    delay(500);
    Serial.println("Attaching service......");
    if(sim7000.attacthService()){                                                              //Open the connection
        Serial.println("Attach service");
    }else{
        Serial.println("Fail to Attach service");
        while(1);
    }
    delay(200);
    Serial.println("Connecting......");
    if(sim7000.connect(TCP,"www.taobao.com",80)){                                              //Start Up TCP or UDP Connection
        Serial.println("Connect OK");
    }else{
        Serial.println("Fail to connect");
        while(1);
    }
    sim7000.send("HEAD/HTTP/1.1\r\nHost:www.taobao.com\r\nConnection:keep-alive\r\n\r\n");     //Send Data Through TCP or UDP Connection 
    dataNum=sim7000.recv(buff,350,0);                                                          //Receive data 
    Serial.print("dataNum=");
    Serial.println(dataNum);
    Serial.println(buff);
    delay(500);
    if(sim7000.close()){                                                                       //End the connection
        Serial.println("Close connection");
    }else{
        Serial.println("Fail to close connection");
    }
    delay(2000);
    sim7000.turnOFF();                                                                         //Turn OFF SIM7000
}

void loop() {
    delay(1000);
}