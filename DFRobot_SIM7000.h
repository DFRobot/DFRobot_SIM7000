/*!
 * @file DFRobot_SIM7000.h
 * @brief Define the basic structure of DFRobot_SIM7000 class
 * @details This is a stable low-power communication module, and it supports multiple frequency bands of LTE- tdd / LTE- fdd / GSM / GPRS / EDGE. The upload and download data flow peak at 375kbps.
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.1
 * @date  2021-09-16
 * @url https://github.com/DFRobot/DFRobot_SIM7000
 */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
#ifndef __DFROBOT_SIM7000_H__
#define __DFROBOT_SIM7000_H__

#include "DFRobot_SIMcore.h"

#include "Arduino.h"
#include "String.h"

#define ON  0
#define OFF 1


#if 0
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

class DFRobot_SIM7000 : public DFRobot_SIMcore{
public:
  /**
   * @enum eProtocol
   * @brief Select Network communication protocol
   */
  typedef enum  {
    eCLOSED = 0,
    eTCP    = 1,
    eUDP    = 2,
  }eProtocol;

  /**
   * @enum eNet
   * @brief Select data communication mode
   */
  typedef enum {
    eGPRS,
    eNB,
  }eNet;

public:
  /**
   * @fn DFRobot_SIM7000
   * @brief DFRobot_SIMcore constructor of abstract class. Construct serial ports.
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
   * @param buf The buffer for data to be send
   * @param len The length of data to be send
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
  
private:
  char  _latitude[8];
  char  _longitude[8];
  int   _mode_t=0;
	long	_baudrate = 19200;
	Stream *_s;
 };

#endif
