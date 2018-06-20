 /*
  * File  : DFRobot_SIM7000_UDP.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example verify UDP connection over a test server
  *         With initialization completed, we use connect(UDP,"112.74.93.163",5232) to set UDP connection
  *         Then enter data send to server and will receive the data same as entered
  *         Thus we finished the UDP send and receive verification
  * Note  : If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  *         The server in this example is provided by the chip supplier for UDP test
  *
  */

#include <Wire.h>
#include <DFRobot_SIM7000.h>

#define serverIP    "112.74.93.163"
#define serverPort   5232
#define PIN_TX       7
#define PIN_RX       8
SoftwareSerial       mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000      sim7000;
char                 sendData[100];
char                 buff[100];

void setup(){
    int signalStrength,dataNum;
    Serial.begin(115200);
    while(!Serial);
    sim7000.begin(mySerial);
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
        if(sim7000.setNetMode(NB)){                             //Set net mod NB-IOT
            Serial.println("Set NB-IOT mode");
            break;
        }else{
            Serial.println("Fail to set mode");
            delay(1000);
        }
    }

    Serial.println("Get signal quality......");
    delay(500);
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
    if(sim7000.openNetwork(UDP,serverIP,serverPort)){           //Start up UDP connection
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
        sim7000.recv(buff,350,0);
        Serial.println("Send data, recive :");
        Serial.println(buff);
    }else{
        Serial.println("Failed to send");
    }
    delay(500);

    Serial.println("Close connection......");
    if(sim7000.close()){                                        //End the connection
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