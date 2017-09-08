 /*
  * file DFRobot_SIM7000_test.ino
  * brief DFRobot's SIM7000 module
  * This example Send an HTTP request to www.baidu.com and receive the return data
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

DFRobot_SIM7000 DS;
static char buff[300];

void setup() {
    int sig,dataNum;
    Serial.begin(115200);
    if(DS.setBaudRate(38400)){                                                            //Set baud rate from 115200 to 38400
        Serial.println("Set baud rate:38400");
    }else{
        Serial.println("faile to set baud rate");
    }
    if(DS.init()){                                                                        //Init SIM7000
        Serial.println("AT command READY");
    }else{
        Serial.println("AT command ERROR");
    }
    if(DS.checkSIMStatus()){                                                              //Check SIM card
        Serial.println("SIM card READY");
    }else{
        Serial.println("SIM card ERROR");
    }
    delay(500);
    if(DS.setNet(GPRS)){                                                                  //Set net mod GPRS or NB-IOT
        Serial.println("Set GPRS mode");
    }else{
        Serial.println("Fail to set mode");
    }
    delay(500);
    sig=DS.checkSignalQuality();                                                          //Check signal quality
    Serial.print("sig =");
    Serial.println(sig);
    delay(500);
    if(DS.attacthService()){                                                              //Open the connection
    Serial.println("Attach service");
    }else{
    Serial.println("Fail to Attach service");
    }
    delay(200);
    if(DS.connect(TCP,"www.baidu.com",80)){                                               //Start Up TCP or UDP Connection
    Serial.println("Connect OK");
    }else{
    Serial.println("Fail to connect");
    }
    DS.send("HEAD / HTTP/1.1\r\nHost:www.baidu.com\r\nConnection:keep-alive\r\n\r\n");    //Send Data Through TCP or UDP Connection 
    dataNum=DS.recv(buff,300,0);                                                          //Receive data 
    Serial.print("dataNum=");
    Serial.println(dataNum);
    Serial.println(buff);
    if(DS.close()){                                                                       //End the connection
        Serial.println("Close connection");
    }else{
        Serial.println("Fail to close connection");
    }
}

void loop() {
    delay(1000);
}