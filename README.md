# NB-IOT SIM7000 Shield

Communicate Shield via GPRS and NB-IOT

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0505/DFR0505svg1.png)

# DFROBOT_SIM7000 Library for Arduino
Provides an Arduino library for NB-IOT SIM7000 Shield
## Table of Contents

* [Summary](#summary)
* [Methods](#methods)
* [Compatibility](#Compatibility)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary
The library is used to Send and receive GPRS or NB-IOT data (TCP,UDP)

## Methods

```C++

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

```

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno  |      √       |             |            | 
Leonardo  |      √       |             |            | 
Meag2560 |      √       |             |            | 

## History

- data 2017-8-30
- version V1.0

## Credits

- author [Zhangjiawei  <jiawei.zhang@dfrobot.com>]
