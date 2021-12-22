/*!
 * @file     DFRobot_SIM7000_ATtest.ino
 * @n        SIM7000 needs 7-12V DC power supply
 * @brief    This example use the serial port to send AT command to control the SIM7000
 * @n        With initialization completed, we can enter AT command to SIM7000 directly
 * @n        Common AT commands : 
 * @n        AT+CPIN? : Check SIM card
 * @n        AT+CSQ   : Check signal quality
 * @n        AT+CGATT?: Check net attached state
 * @n        AT+CSTT  : Start net connect task
 * @n        AT+CIFSR : Get local IP
 * 
 * @n        Get the AT command table in Resource folder :SIM7000 Series_AT Command Manual_V1.01.pdf
 * @n        If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
 * @n        The AT command must end with CRLF
 * 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [TangJie](jie.tang@dfrobot.com)
 * @version     V1.0.1
 * @date        2021-09-16
 * @url         https://github.com/DFRobot/DFRobot_SIM7000
 */

#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000(&mySerial);

void setup() {
  Serial.begin(9600);
  mySerial.begin(19200);
  Serial.println("Turn ON SIM7000......");
  if(sim7000.turnON()){                             //Turn ON SIM7000
    Serial.println("Turn ON !");
  }

  Serial.println("Set baud rate......");
  while(1){
    if(sim7000.setBaudRate(19200)){               //Set SIM7000 baud rate from 115200 to 19200 reduce the baud rate to avoid distortion
      Serial.println("Set baud rate:19200");
        break;
      }else{
        Serial.println("Faile to set baud rate");
        delay(1000);
      }
  }
  mySerial.begin(19200);
  Serial.println("For example, if you type AT\\r\\n, OK\\r\\n will be responsed!");
  Serial.println("Enter your AT command :");
}

void loop() {
  mySerial.listen();
  while(mySerial.available()){
    Serial.write(mySerial.read());
  }
  mySerial.flush();
  while(Serial.available()){
    mySerial.write(Serial.read());
  }
}