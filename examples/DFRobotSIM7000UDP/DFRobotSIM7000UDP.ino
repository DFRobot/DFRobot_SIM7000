/*!
 * @file   DFRobot_SIM7000_UDP.ino
 * @n      SIM7000 needs 7-12V DC power supply
 * @brief  This example verify UDP connection over a test server
 * @n      With initialization completed, we use connect(UDP,"112.74.93.163",5232) to set UDP connection
 * @n      Then enter data send to server and will receive the data same as entered
 * @n      Thus we finished the UDP send and receive verification
 * @n      If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
 * @n     The server in this example is provided by the chip supplier for UDP test
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [TangJie](jie.tang@dfrobot.com)
 * @version     V1.0.1
 * @date        2021-09-16
 * @url         https://github.com/DFRobot/DFRobot_SIM7000
 */

#include <DFRobot_SIM7000.h>

#define serverIP    "112.74.93.163"
#define serverPort   5232
#define PIN_TX       7
#define PIN_RX       8
SoftwareSerial       mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000         sim7000(&mySerial);
char                 sendData[100];
char                 buff[100];

void setup(){
  int signalStrength;
  Serial.begin(9600);
  mySerial.begin(19200);
  Serial.println("Turn ON SIM7000......");
  if(sim7000.turnON()){                                       //Turn ON SIM7000
    Serial.println("Turn ON !");
  }

  Serial.println("Set baud rate......");
  while(1){
    if(sim7000.setBaudRate(19200)){                         //Set SIM7000 baud rate from 115200 to 19200 reduce the baud rate to avoid distortion
      Serial.println("Set baud rate:19200");
      break;
    }else{
      Serial.println("Faile to set baud rate");
      delay(1000);
    }
  }

  Serial.println("Check SIM card......");
  if(sim7000.checkSIMStatus()){                               //Check SIM card
    Serial.println("SIM card READY");
  }else{
    Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7000");
    while(1);
  }

  Serial.println("Set net mode......");
  while(1){
    if(sim7000.setNetMode(sim7000.eGPRS)){                             //Set GPRS mode
      Serial.println("Set GPRS mode");
      break;
    }else{
      Serial.println("Fail to set mode");
      delay(1000);
    }
  }

  Serial.println("Get signal quality......");
  delay(1500);
  signalStrength=sim7000.checkSignalQuality();                //Check signal quality from (0-30)
  Serial.print("signalStrength =");
  Serial.println(signalStrength);
  delay(500);

  Serial.println("Attaching service......");
  while(1){
    if(sim7000.attacthService()){                           //Open the connection
      Serial.println("Attach service");
      break;
    }else{
      Serial.println("Fail to Attach service");
      delay(1000);
    }
  }
}

void loop(){
  delay(2000);
  Serial.println("Connecting......");
  if(sim7000.openNetwork(sim7000.eUDP,serverIP,serverPort)){           //Start up UDP connection
    Serial.println("Connect OK");
  }else{
    Serial.println("Fail to connect");
    return;
  }

  Serial.println("Input data :");
  readSerial(sendData);
  Serial.println("Send data :");
  Serial.println(sendData);
  if(sim7000.send(sendData)){                                 //Send data to server
    sim7000.recv(buff,350);
    Serial.println("Send data, recive :");
    Serial.println(buff);
  }else{
    Serial.println("Failed to send");
  }
  delay(500);

  Serial.println("Close connection......");
  if(sim7000.closeNetwork()){                                 //End the connection
    Serial.println("Closed !");
  }else{
    Serial.println("Fail to close connection");
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