 /*
  * file DFRobot_SIM7000_test.ino
  * brief DFRobot's SIM7000 module
  * This example Send an HTTP request to www.baidu.com and receive the return data
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

DFRobot_SIM7000 DS;

void setup() {
  char buff[100];
  Serial.begin(115200);
  if(DS.setBaudRate(38400))                                                           //Set baud rate from 115200 to 38400
      Serial.println("Set baud rate:38400");
  else
      Serial.println("faile to set baud rate");
  if(DS.init())                                                                       //Init SIM7000
      Serial.println("AT command READY");
  else
      Serial.println("AT command ERROR");
  if(DS.checkSIMStatus())                                                             //Check SIM card
       Serial.println("SIM card READY");
  else  
       Serial.println("SIM card ERROR");  
  delay(100);
  if(DS.setNet(GPRS))                                                                 //Set net mod GPRS or NB-IOT
      Serial.println("Set GPRS mode");
  else 
      Serial.println("Fail to set mode");  
  delay(100);
  DS.checkSignalQuality();                                                            //Check signal quality
  delay(500);
  DS.attacthService();                                                                //Open the connection
  delay(200);
  DS.connect(TCP,"www.baidu.com",80);                                                 //Start Up TCP or UDP Connection
  DS.send("GET / HTTP/1.1\r\nHost:www.baidu.com\r\nConnection:keep-alive\r\n\r\n");   //Send Data Through TCP or UDP Connection 
  DS.recv(buff,100);                                                                  //Receive data 
  Serial.println(buff); 
  DS.close();                                                                         //End the connection
}

void loop() {
  delay(1000);
}