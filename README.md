# DFROBOT_SIM7000 Library for Arduino
Provides an Arduino library for SIM7000
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

### Set baud rate from 115200 to 38400 to avoid garbled
 
    bool setBaudRate(void);
    
### Init SIM7000
   
    bool init(void);

### Check SIM card

    bool checkSIMStatus(void);
    
### Set net mod GPRS or NB-IOT

    bool setNet(Net net);
    net:GPRS NB

### Check signal quality
   
    bool checkSignalQuality(void);
   
### Open the connection
    
    bool attacthService(void);

### Start Up TCP or UDP Connection

    bool connect(Protocol ptl,const char *host, int port, int timeout= DEFAULT_TIMEOUT, int chartimeoutchartimeout = DEFAULT_INTERCHAR_TIMEOUT);
    ptl:UDP TCP
    
### Send Data Through TCP or UDP Connection

    int  send(const char *str, int len);

### End the connection

    bool close(void);

## History

- data 2017-8-30
- version V1.0

## Credits

- author [Zhangjiawei<jiawei.zhang@dfrobot.com>]
