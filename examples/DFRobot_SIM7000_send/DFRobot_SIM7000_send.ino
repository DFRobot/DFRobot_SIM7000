 /*
  * file DFRobot_SIM7000_send.ino
  * brief DFRobot's SIM7000 module
  * This example Send GPRS data(UDP)
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

DFRobot_SIM7000 DS;

void setup() {
  Serial.begin(115200);
  DS.setBaudRate(38400);                          //Set baud rate from 115200 to 38400
  DS.init();                                      //Init SIM7000
  DS.checkSIMStatus();                            //Check SIM card
  delay(100);
  DS.setNet(GPRS);                                //Set net mod GPRS or NB-IOT
  delay(100);
  DS.checkSignalQuality();                        //Check signal quality
  DS.attacthService();                            //Open the connection
  DS.connect(UDP,"116.247.119.165",7016);         //Start Up TCP or UDP Connection
  DS.send("1234",4);                              //Send Data Through TCP or UDP Connection 
  DS.close();                                     //End the connection
}

void loop() {
  delay(1000);
}