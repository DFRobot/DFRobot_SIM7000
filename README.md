
# DFRobot_SIM7000
* [中文版](./README_CN.md)
  
SIM7000 is the first LTE CAT-M1 / NB-IoT module, it supports multiple frequency bands of LTE-TDD / LTE-FDD / GSM / GPRS / EDGE.
The upstream and downstream data flow peaks at 375kbps. It is a stable low-power communications module. NB-IoT has 20dB + coverage gain, so
it has wireless communication capabilities even in environment like basement.

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0505/DFR0505svg1.png)

## Product Link(https://www.dfrobot.com/product-1701.html)

    SKU:DFR0505

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

The library provide some application rely on SIM7000:
Use GPRS mode or NB-IOT mod to send and receive data by UDP or TCP
Positioning current position by GNSS, this function works better on outdoor
We also provide a way to send AT command directly to SIM7000

## Installation

Download the associated library before running the demo of the library:  https://github.com/DFRobot/DFRobot_SIM
To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  /**
   * @fn DFRobot_SIM7000
   * @brief DFRobot_SIMcore constructor of abstract class. Construct serial ports
   * @param s The pointer to abstract class, where you can fill in the pointer to serial object.
   * @return None
   */
  DFRobot_SIM7000(Stream *s);
  ~DFRobot_SIM7000(){};

  /**
   * @fn recv
   * @brief Receive
   * @param buf Receive data content
   * @param maxlen Receive data length
   * @return Get data length
   */
  int recv(char* buf, int maxlen);
 
  /**
   * @fn checkSignalQuality
   * @brief Check signal quality
   * @return 0-30:Signal quality
   */
  int checkSignalQuality(void);

  /**
   * @fn batteryPower
   * @brief Battery power
   * @return Battery power
   */
  int batteryPower(void);
 
  /**
   * @fn setNetMode
   * @brief Set net mode
   * @param net The net mode
   * @n    GPRS: GPRS mode
   * @n    NB:   NB-IOT mode
   * @return bool type, indicating the status of setting
   * @retval ture Success 
   * @retval false Failed
   */
  bool setNetMode(eNet net);

  /**
   * @fn attacthService
   * @brief Open the connection
   * @return bool type, indicating the status of opening the connection
   * @retval true Success 
   * @retval false Failed
   */
  bool attacthService(void);

  /**
   * @fn setBaudRate
   * @brief Set baud rate to avoid garbled
   * @param rate Baud rate value
   * @n    Possible values:1200 2400 4800 9600 19200 38400
   * @note SIM7000 default baud rate is 115200, reduce the baud rate to avoid distortion
   * @return bool type, indicating the status of setting
   * @retval true Success 
   * @retval false Failed
   */
  bool setBaudRate(long rate);

  /**
   * @fn checkSIMStatus
   * @brief Check SIM card
   * @return bool type, indicating the status of checking SIM card
   * @retval true Success 
   * @retval false Failed
   */
  bool checkSIMStatus(void);

  /**
   * @fn openNetwork
   * @brief Start up connection
   * @param ptl  Choose connection protocol
   * @n    TCP  Choose TCP
   * @n    UDP  Choose UDP
   * @param host Host domain name
   * @param port  Contented port
   * @return bool type, indicating the status of opening Network
   * @retval true Success 
   * @retval false Failed
   */
  bool openNetwork(eProtocol ptl, const char *host, int port);

  /**
   * @fn closeNetwork
   * @brief End the connection
   * @return bool type, indicating the status of closing Network
   * @retval true Success 
   * @retval false Failed
   */
  bool closeNetwork(void);

  /**
   * @fn turnON
   * @brief Turn ON SIM7000
   * @return bool type, indicating the status of turning on
   * @retval true Success 
   * @retval false Failed
   */
  bool turnON(void);

  /**
   * @fn initPos
   * @brief Init SIM7000 positioning module
   * @return bool type, indicating the initialization status
   * @retval true Success 
   * @retval false Failed
   */
  bool initPos(void);

  /**
   * @fn mqttConnect
   * @brief MQTT connect request
   * @param iot_client Client name user-defined
   * @param iot_username The user name identifies the name of the user who is connecting
   * @param iot_key The password for user
   * @return bool type, indicating the connection status
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttConnect(const char* iot_client, const char* iot_username, const char* iot_key);

  /**
   * @fn mqttPublish
   * @brief MQTT send command
   * @param iot_topic Target topic
   * @param iot_data  The data you want to send
   * @return bool type, indicating status of sending
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttPublish(const char* iot_topic, String iot_data);

  /**
   * @fn mqttSubscribe
   * @brief Subscribe MQTT channel
   * @param iot_topic The subscribed MQTT key 
   * @return bool type, indicating subscription status
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttSubscribe(const char* iot_topic);

  /**
   * @fn mqttUnsubscribe
   * @brief Unsubscribe MQTT channel
   * @param iot_topic The unsubscribed MQTT key
   * @return bool type, indicating unsubscribe status
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttUnsubscribe(const char* iot_topic);

  /**
   * @fn mqttRecv
   * @brief MQTT send data
   * @param iot_topic Subscribe channel key
   * @param buf Send data
   * @param maxlen Send data length
   * @return bool type, indicating subscription status
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttRecv(char* iot_topic, char* buf,int maxlen);

  /**
   * @fn mqttDisconnect
   * @brief MQTT disconnection
   * @return bool type, indicating disconnection status
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttDisconnect(void);

  /**
   * @fn httpInit
   * @brief Initialize HTTP service
   * @param net The net mode
   * @n    eGPRS: GPRS mode
   * @n    eNB:   NB-IOT mode
   * @return bool type, indicating initialization status
   * @retval true Success 
   * @retval false Failed
   */
  bool httpInit(eNet net);

  /**
   * @fn httpConnect
   * @brief Connect to server
   * @param host Server IP
   * @return bool type, indicating connection status
   * @retval true Success 
   * @retval false Failed
   */
  bool httpConnect(const char *host);

  /**
   * @fn httpPost
   * @brief HTTP POST
   * @param host URL
   * @param data POST data
   * @return bool type, indicating request status
   * @retval true Success 
   * @retval false Failed
   */
  bool httpPost(const char *host , String data);

  /**
   * @fn httpGet
   * @brief HTTP GET This function print the get data
   * @param host URL
   */
  void httpGet(const char *host);

  /**
   * @fn httpDisconnect
   * @brief Disconnect from server and cancel initialization
   */
  void httpDisconnect(void);

  /**
   * @fn send
   * @brief Send data with specify the length
   * @param buf The buffer for data to be sent
   * @param len The length of data to be sent
   * @return bool type, indicating status of sending
   * @retval true Success 
   * @retval false Failed
   */
  bool send(char *buf,size_t len);

  /**
   * @fn send
   * @brief Send data
   * @param data The data to send
   * @return bool type, indicating status of sending
   * @retval true Success 
   * @retval false Failed
   */
  bool send(char *data);

  /**
   * @fn getPosition
   * @brief Get the current position
   * @return bool type, indicating the status of getting position
   * @retval true Success 
   * @retval false Failed
   */
  bool getPosition(void);

  /**
   * @fn getLatitude
   * @brief Get latitude
   * @return Latitude value
   */
  const char* getLatitude(void);

  /**
   * @fn getLongitude
   * @brief Get longitude
   * @return Longitude value
   */
  const char* getLongitude(void);
```

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno  |      √       |             |            | 
Leonardo  |      √       |             |            | 
Meag2560 |         √    |              |            | 

If you use Mega please connect PIN8 PIN10

## History

- 2017/8/30 - 1.0.0 version
- 2021/09/16 - 1.0.1 version
- 2021/12/28 - 1.0.2 version

## Credits

- Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
