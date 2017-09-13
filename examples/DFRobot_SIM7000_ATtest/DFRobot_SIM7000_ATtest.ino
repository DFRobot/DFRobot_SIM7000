 /*
  * file DFRobot_SIM7000_ATtest.ino
  * brief DFRobot's SIM7000 module
  * This example use the serial port to send AT commands to control the SIM7000
  */
#include <DFRobot_SIM7000.h>

SoftwareSerial mySerial(8,7);                                  // RX, TX

DFRobot_SIM7000 sim7000;

void setup() {
    Serial.begin(115200);
    sim7000.turnOFF();
    delay(500);
    if(sim7000.turnON()){                                      //Turn ON SIM7000
        Serial.println("Turn NO SIM7000");
    }
    if(sim7000.setBaudRate(38400)){                            //Set baud rate from 115200 to 38400
        Serial.println("Set baud rate:38400");
    }else{
        Serial.println("faile to set baud rate");
    }
    mySerial.begin(38400);
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
