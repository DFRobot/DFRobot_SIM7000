/*!
 * @file   DFRobot_SIM7000_HTTP.ino
 * @n      SIM7000 needs 7-12V DC power supply
 * @brief  This example will verify HTTP connection over a HTTP request
 * @n      With initialization completed, we connect to server POST data and GET data
 * @n      Thus we finished the HTTP POST and GET verification
 * @n      If you use NB-IOT please confirm that the IOT is in the whitelist of your NB card
 * @n      If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
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

//Login website (https://www.tlink.io/) to register an account ,fill the following information based on your account
#define deviceNo  "DEVICE NO" //Device serial number
#define sensorsId "SENSOR ID" //sensor ID
#define value     "VALUE"

//This URL is use for post data to tlink
#define POSTURL   "api.tlink.io/tlink_interface/api/device/createDataPonit.htm"
//This URL is use for get data from tlink, please change the SENSORID to your sensorsId
#define GETURL    "api.tlink.io/tlink_interface/api/device//getDataPoint_SENEORID.htm"

SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7000         sim7000(&mySerial);

void setup(){
  int signalStrength;
  Serial.begin(9600);
  mySerial.begin(19200);
  Serial.println("Turn ON SIM7000......");
  if(sim7000.turnON()){                                    //Turn ON SIM7000
    Serial.println("Turn ON !");
  }

  Serial.println("Set baud rate......");
  while(1){
    if(sim7000.setBaudRate(19200)){                      //Set SIM7000 baud rate from 115200 to 19200, reduce the baud rate to avoid distortion
      Serial.println("Set baud rate:19200");
      break;
    }else{
      Serial.println("Faile to set baud rate");
      delay(1000);
    }
  }

  Serial.println("Check SIM card......");
  if(sim7000.checkSIMStatus()){                            //Check SIM card
    Serial.println("SIM card READY");
  }else{
    Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7000");
    while(1);
  }

  Serial.println("Set net mode......");
  while(1){
    if(sim7000.setNetMode(sim7000.eGPRS)){                        //Set net mod GPRS
      Serial.println("Set GPRS mode");
      break;
    }else{
      Serial.println("Fail to set mode");
      delay(1000);
    }
  }

  Serial.println("Get signal quality......");
  delay(1500);
  signalStrength=sim7000.checkSignalQuality();             //Check signal quality from (0-30)
  Serial.print("signalStrength =");
  Serial.println(signalStrength);
  delay(500);

  Serial.println("Attaching service......");
  while(1){
    if(sim7000.attacthService()){                        //Open the connection
      Serial.println("Attach service");
      break;
    }else{
      Serial.println("Fail to Attach service");
      delay(1000);
    }
  }

  Serial.println("Init http......");
  while(1){
    if(sim7000.httpInit(sim7000.eGPRS)){                          //Init http service
      Serial.println("HTTP init !");
      break;
    }else{
      Serial.println("Fail to init http");
    }
  }

  Serial.print("POST to ");
  Serial.println(POSTURL);
  String httpbuff;
  httpbuff += "{\"deviceNo\":\"";                          //{
  httpbuff += deviceNo;                                    //   "deviceNo" : "DEVICE NO",
  httpbuff += "\",\"sensorDatas\":[{\"sensorsId\":";       //      "sensorDatas":[{
  httpbuff += sensorsId;                                   //          "sensorsId" :  SENSOR ID,
  httpbuff += ",\"value\":\"";                             //          "value"     : "  VALUE  "
  httpbuff += value;                                       //       }]
  httpbuff += "\"}]}";                                     //}
  while(1){
    if(sim7000.httpPost(POSTURL,httpbuff)){              //HTTP POST
      Serial.println("Post successed");
      break;
    }else{
      Serial.println("Fail to post");
    }
  }

  Serial.print("GET from ");
  Serial.println(GETURL);
  sim7000.httpGet(GETURL);                                 //HTTP GET
  Serial.println("Disconnect");
  sim7000.httpDisconnect();                                //Disconnect
  Serial.println("Close net work");
  sim7000.closeNetwork();                                  //Close network
  Serial.println("Turn off SIM7000");
  sim7000.turnOFF();                                       //Turn OFF SIM7000
}

void loop() {
  delay(1000);
}
