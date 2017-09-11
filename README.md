# DFROBOT_SIM7000 Library for Arduino
Provides an Arduino library for NB-IOT SIM7000 Shield
## Table of Contents

* [Summary](#summary)
* [Methods](#methods)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary
The library is used to Send and receive GPRS or NB-IOT data (TCP,UDP)

## Methods

```C++

#include <DFrobot_SIM7000.h>
//Turn ON SIM7000
bool turnON(void);

//Turn OFF SIM7000
bool turnOFF(void);
//Set baud rate to avoid garbled, rate:1200 2400 4800 9600 19200 38400
bool setBaudRate(long rate);

//Init SIM7000
bool init(void);

//Check SIM card
bool checkSIMStatus(void);
    
//Set net mod GPRS or NB-IOT, net:GPRS NB
bool setNet(Net net);

//Check signal quality,return signal quality(0-99)
int checkSignalQuality(void);
   
//Open the connection
bool attacthService(void);

//Start up TCP or UDP connection,ptl:UDP TCP
bool connect(Protocol ptl,const char *host, int port, int timeout= DEFAULT_TIMEOUT, int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);

//Receive data,maxlen from 1 to 300,when timeout=0(default) keep receiving state,return the actual number of received
int recv(char* buf,int maxlen,int timeout);

//Send data through TCP or UDP connection
void send(const char *str);

//Send data with specify the length
void send(const char *str,int len);

//End the connection
bool close(void);

```

## History

- data 2017-8-30
- version V1.0

## Credits

- author [Zhangjiawei  <jiawei.zhang@dfrobot.com>]
