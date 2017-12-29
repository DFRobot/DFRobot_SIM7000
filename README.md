
# DFROBOT_SIM7000 Library for Arduino
-  Provides an Arduino library for NB-IOT SIM7000 Shield
-  SIM7000 is the first LTE CAT-M1 / NB-IoT module, it supports multiple frequency bands of LTE-TDD / LTE-FDD / GSM / GPRS / EDGE
The upstream and downstream data flow peak 375kbps, it a stable low-power communications module.NB-IoT has 20dB + coverage gain, so
it has wireless communication capabilities even in a similar basement and the like.

# NB-IOT SIM7000 Shield

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0505/DFR0505svg1.png)

## Table of Contents

* [Summary](#summary)
* [Methods](#methods)
* [Compatibility](#Compatibility)
* [Depends](#depends)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary
### The library provide some application rely on SIM7000:
####   Use GPRS mode or NB-IOT mod to send and receive data by UDP or TCP
####   Positioning current position by GNSS, this function works better on outdoor
####   We also provide a way to send AT command directly to SIM7000

## Methods

```C++
/*
 * @brief Set SIM7000 software serial
 *
 * @Param &s_ SoftwareSerial
 */
void begin(Stream &s_);

/*
 * @brief Turn ON SIM7000
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
 bool turnON(void);

/*
 * @brief Turn OFF SIM7000
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool turnOFF(void);

/*
 * @brief Set baud rate to avoid garbled
 *
 * @param rate Baud rate value
 *     Possible values:1200 2400 4800 9600 19200 38400
 *
 * @note 
 *     SIM7000 default baud rate is 115200 reduce the baud rate to avoid distortion
 *
 * @return
 *     ture   Success
 *     false  Faile
 */
bool setBaudRate(long rate);

/*
 * @brief Init SIM7000
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool init(void);

/*
 * @brief Check SIM card
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool checkSIMStatus(void);

/*
 * @brief Set net mode
 *
 * @param net The net mode
 *     GPRS: GPRS mode
 *     NB:   NB-IOT mode
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool setNet(Net net);

/*
 * @brief Check signal quality
 *
 * @return
 *     0-99:Signal quality
 */
int checkSignalQuality(void);

/*
 * @brief Get battery power
 *
 * @return
 *     0-99:Battery power
 */
int batteryPower(void);

/*
 * @brief Open the connection
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool attacthService(void);

/*
 * @brief Start up connection
 *
 * @param ptl  Choose connection protocol
 *     TCP  Choose TCP
 *     UDP  Choose UDP
 *
 * @param *host Host domain name
 *
 * @param port  Contented port
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool connect(Protocol ptl,const char *host, int port);

/*
 * @brief Receive data
 *
 * @param buf The buffer to store data
 *
 * @param maxlen The max length of data 
 *    The maximum value:300
 *
 * @param timeout Maximum waiting time
 *    Default time = 0 keep receiving state
 *
 * @return
 *    The byte of received data
 */
int recv(char* buf,int maxlen,int timeout);

/*
 * @brief Send data
 *
 * @param *str The data to send
 */
void send(const char *str);

/*
 * @brief Send data with specify the length
 *
 * @param buf The buffer stored data to be send
 *
 * @param len The length of data to be send
 */
void send(void* buf,size_t len);

/*
 * @brief End the connection
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool close(void);

/*
 * @brief Init SIM7000 positioning module
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool initPos(void);

/*
 * @brief Get the current position
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool getPosition(void);

/*
 * @brief Get longitude
 *
 * @return
 *     Longitude value
 */
char* getLongitude(void);

/*
 * @brief Get latitude
 *
 * @return
 *     Latitude value
 */
char* getLatitude(void);

/*
 * @brief MQTT connect request
 *
 * @param iot_client Client name user-defined
 *
 * @param iot_username The user name identifies the name of the user who is connecting
 *
 * @param iot_key The password for user
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool MQTTconnect(char* iot_client, char* iot_username, char* iot_key);

/*
 * @brief MQTT send command
 *
 * @param iot_topic Target topic
 *
 * @param iot_data  The data you want to send
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool MQTTsend(char* iot_topic, char* iot_data);

/*
 * @brief MQTT subscribe request
 *
 * @param iot_topic The topic you want to subscribe
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool MQTTsubscribe(char* iot_topic);

/*
 * @brief Receive data from subscribed topic
 *
 * @param iot_topic The subscribed topic
 *
 * @param buff      The buffer to store data
 *
 * @param maxlen    The maximum length of the buffer
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool     MQTTrecv(char* iot_topic, char* buff,int maxlen);

/*
 * @brief MQTT unsubscribe request
 *
 * @param iot_topic The topic you want to unsubscribe
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool MQTTunsubscribe(char* iot_topic);

```

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno  |      √       |             |            | 
Leonardo  |      √       |             |            | 
Meag2560 |      √       |             |            | 

If you use Mega please connect PIN8 PIN10

## Depends

Projects           |                     URL                       | Remarks
------------------ | :-------------------------------------------: | -----------
DFRobot_SIM        |  https://github.com/DFRobot/DFRobot_SIM       | must

## History

- data 2017-8-30
- version V1.0

## Credits

- author [Zhangjiawei  <jiawei.zhang@dfrobot.com>]
