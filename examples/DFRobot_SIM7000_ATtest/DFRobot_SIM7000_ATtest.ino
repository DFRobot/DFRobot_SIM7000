 /*
  * file DFRobot_SIM7000_ATtest.ino
  * brief DFRobot's SIM7000 module
  * This example use the serial port to send AT commands to control the SIM7000
  */
#include <DFRobot_SIM7000.h>

// Set software serial(RX=8,TX=7) if you use Mega please set RX=10 and connect PIN8 PIN10 and set mySerial(10,7)
SoftwareSerial mySerial(8,7);

DFRobot_SIM7000 sim7000;

void setup() {
    Serial.begin(115200);
    sim7000.begin(mySerial);
    sim7000.turnOFF();
    delay(5000);
    if(sim7000.turnON()){                                      //Turn ON SIM7000
        Serial.println("Turn NO SIM7000");
    }
    if(sim7000.setBaudRate(19200)){                            //Set baud rate from 115200 to 19200
        Serial.println("Set baud rate:19200");
        Serial.println("Enter your AT commands : ");
    }else{
        Serial.println("faile to set baud rate");
    }
    mySerial.begin(19200);
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
