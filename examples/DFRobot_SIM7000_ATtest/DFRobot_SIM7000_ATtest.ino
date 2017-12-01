 /*
  * File  : DFRobot_SIM7000_ATtest.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example use the serial port to send AT command to control the SIM7000
  *         With initialization completed, we can enter AT command to SIM7000 directly
  * AT command list:
  * https://github.com/DFRobot/binaryfiles/raw/master/DFR0505/doc/SIM7000%20Series_AT%20Command%20Manual_V1.01.pdf
  * Note  : If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  */
#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;

void setup() {
    Serial.begin(115200);
    sim7000.begin(mySerial);
    sim7000.turnOFF();
    delay(5000);
    Serial.println("Turn ON SIM7000......");
    if(sim7000.turnON()){                             //Turn ON SIM7000
        Serial.println("Turn ON !");
    }
    Serial.println("Set baud rate......");
    if(sim7000.setBaudRate(19200)){                   //Set baud rate from 115200 to 19200
        Serial.println("Set baud rate:19200");
    }else{
        Serial.println("Faile to set baud rate");
        while(1);
    }
    mySerial.begin(19200);
    Serial.println("Example :");
    mySerial.listen();
    mySerial.write("AT\r\n");                         //AT command end with Carriage Return and Line Feed
    while(mySerial.available()){
        Serial.write(mySerial.read());
    }
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
    delay(20);
}
