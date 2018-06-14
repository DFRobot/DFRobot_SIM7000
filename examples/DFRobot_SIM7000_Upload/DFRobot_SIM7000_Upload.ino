 /*
  * File  : DFRobot_SIM7000_Upload.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example use SIM7000 to get position then upload the data to iot with MQTT
  * Note  : This example needs SIM card
  *         The tracker function only available in outdoor
  *         If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  */

#include <DFRobot_SIM7000.h>

//Login website (http://iot.dfrobot.com.cn) to register an account ,fill the following information based on your account
#define serverIP        "iot.dfrobot.com.cn"
#define IOT_CLIENT      " CLIENT NAME "
#define IOT_USERNAME    " USER   NAME "
#define IOT_KEY         " PASSWORD    "
#define IOT_TOPIC       " TOPIC       "

#define PIN_TX          7
#define PIN_RX          8

SoftwareSerial          mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000         sim7000;

void setup() {
    Serial.begin(115200);
    sim7000.begin(mySerial);
    delay(5000);
    Serial.println("Turn ON SIM7000......");
    if(sim7000.turnON()){                                        //Turn ON SIM7000
        Serial.println("Turn ON !");
    }

    Serial.println("Set baud rate......");
    while(1){
        if(sim7000.setBaudRate(19200)){                          //Set SIM7000 baud rate from 115200 to 19200 reduce the baud rate to avoid distortion
            Serial.println("Set baud rate:19200");
            break;
        }else{
            Serial.println("Faile to set baud rate");
            delay(1000);
        }
    }

    Serial.println("Check SIM card......");
    if(sim7000.checkSIMStatus()){                                //Check SIM card
        Serial.println("SIM card READY");
    }else{
        Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7000");
        while(1);
    }

    Serial.println("Set net mode......");
    while(1){
        if(sim7000.setNetMode(NB)){                              //Set net mod NB-IOT
            Serial.println("Set NB-IOT mode");
            break;
        }else{
            Serial.println("Fail to set mode");
            delay(1000);
        }
    }

    Serial.println("Get signal quality......");
    int  signalStrength=sim7000.checkSignalQuality();            //Check signal quality from (0-30)
    Serial.print("signalStrength =");
    Serial.println(signalStrength);
    delay(500);

    Serial.println("Attaching service......");
    while(1){
        if(sim7000.attacthService()){                            //Open the connection
            Serial.println("Attach service");
            break;
        }else{
            Serial.println("Fail to Attach service");
            delay(1000);
        }
    }
}

void loop()
{
    delay(2000);
    if(sim7000.getPosition()){                                   //Get the current position
        Serial.print("Longtude :");
        Serial.println(sim7000.getLongitude());                  //Get longitude
        Serial.print("Latitude :");
        Serial.println(sim7000.getLatitude());                   //Get latitude
    }else{
        Serial.println("Wrong data try again");
        return;
    }

    String  sim7000Buffer;
    sim7000Buffer  = String(); 
    sim7000Buffer += " Longitude : ";
    sim7000Buffer +=  sim7000.getLongitude();
    sim7000Buffer += " Latitude  : ";
    sim7000Buffer +=  sim7000.getLatitude();

    Serial.print("Connect to :");
    Serial.println(serverIP);
    if(sim7000.openNetwork(TCP,serverIP,1883)){                  //Connect to server
        Serial.println("Connected !");
    }else{
        Serial.println("Failed to connect");
        return;
    }
    delay(200);

    Serial.print("Connect to : ");
    Serial.println(IOT_USERNAME);
    if(sim7000.MQTTconnect(IOT_CLIENT,IOT_USERNAME,IOT_KEY)){    //MQTT connect request
        Serial.println("Connected !");
    }else{
        Serial.println("Failed to connect");
        return;
    }
    delay(200);

    if(sim7000.MQTTpublish(IOT_TOPIC,sim7000Buffer)){            //Send data to topic
        Serial.println("Send OK");
    }else{
        Serial.println("Failed to send");
        return;
    }
    delay(200);

    Serial.println("Close connection......");
    if(sim7000.close()){                                         //Close connection
        Serial.println("Close connection !");
    }else{
        Serial.println("Fail to close connection !");
        return;
    }
}