 /*
  * File  : DFRobot_SIM7000_ATtest.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example use the serial port to send AT command to control the SIM7000
  *         With initialization completed, we can enter AT command to SIM7000 directly
  *         Common AT commands : 
  *         AT+CPIN? : Check SIM card
  *         AT+CSQ   : Check signal quality
  *         AT+CGATT?: Check net attached state
  *         AT+CSTT  : Start net connect task
  *         AT+CIFSR : Get local IP
  *         Get the AT command table in Resource folder :SIM7000 Series_AT Command Manual_V1.01.pdf
  * Note  : If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  *         The AT command must end with CRLF
  */
#include <DFRobot_SIM7000.h>

#define PIN_TX     7
#define PIN_RX     8
SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000    sim7000;

void setup() {
    Serial.begin(115200);
    sim7000.begin(mySerial);
    delay(5000);
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