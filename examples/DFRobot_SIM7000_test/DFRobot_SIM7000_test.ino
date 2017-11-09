 /*
  * file DFRobot_SIM7000_test.ino
  * brief DFRobot's SIM7000 module
  * This example Send an HTTP request to www.dfrobot.com and receive the return data
  * If you use Mega please connect PIN8 PIN10 and set mySerial(10,7);
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

DFRobot_SIM7000 sim7000;
static char buff[300];
SoftwareSerial mySerial(8,7);                                                                  //Set serial please dont use PIN12

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    sim7000.begin(mySerial);
    sim7000.turnOFF();
    delay(500);
    if(sim7000.turnON()){                                                                      //Turn ON SIM7000
        Serial.println("Turn NO SIM7000");
    }
    if(sim7000.setBaudRate(38400)){                                                            //Set baud rate from 115200 to 38400
        Serial.println("Set baud rate:38400");
    }else{
        Serial.println("faile to set baud rate");
    }
    if(sim7000.init()){                                                                        //Init SIM7000
        Serial.println("AT command READY");
    }else{
        Serial.println("AT command ERROR");
    }
    if(sim7000.checkSIMStatus()){                                                              //Check SIM card
        Serial.println("SIM card READY");
    }else{
        Serial.println("SIM card ERROR");
    }
    delay(500);
    if(sim7000.setNet(GPRS)){                                                                  //Set net mod GPRS or NB-IOT
        Serial.println("Set GPRS mode");
    }else{
        Serial.println("Fail to set mode");
    }
    delay(500);
    signalStrength=sim7000.checkSignalQuality();                                               //Check signal quality
    Serial.print("signalStrength =");
    Serial.println(signalStrength);
    delay(500);
    if(sim7000.attacthService()){                                                              //Open the connection
        Serial.println("Attach service");
    }else{
        Serial.println("Fail to Attach service");
    }
    delay(200);
    if(sim7000.connect(TCP,"www.dfrobot.com",80)){                                             //Start Up TCP or UDP Connection
        Serial.println("Connect OK");
    }else{
        Serial.println("Fail to connect");
    }
    sim7000.send("HEAD / HTTP/1.1\r\nHost:www.dfrobot.com\r\nConnection:keep-alive\r\n\r\n");  //Send Data Through TCP or UDP Connection 
    dataNum=sim7000.recv(buff,300,0);                                                          //Receive data 
    Serial.print("dataNum=");
    Serial.println(dataNum);
    Serial.println(buff);
    uint8_t buf[]={1,2,0,1,2,0};
    sim7000.send(buf,sizeof(buf));                                                             //Send Data with specify the length
    delay(2000);
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