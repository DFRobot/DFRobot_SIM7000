DFROBOT_SIM7000 Library for Arduino
---------------------------------------------------------

The library is used to Send and receive GPRS or NB-IOT data (TCP,UDP)

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

    bool SIM7000Connect(Protocol ptl,const char *host, int port, int timeout= DEFAULT_TIMEOUT, int chartimeoutchartimeout = DEFAULT_INTERCHAR_TIMEOUT);
    ptl:UDP TCP
	
### Send Data Through TCP or UDP Connection

    int  SIM7000Send(const char *str, int len);

### End the connection

    bool SIM7000Close(void);

 * @file DFROBOT_SIM7000_send.ino
 * @brief DFRobot's SIM7000 module
 * @n This example Send GPRS data(UDP)
 *
 * @n [Get the module here](等上架后添加商品购买链接)
 * @n [Connection and Diagram](等上架后添加wiki链接)
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2017
 * @copyright	GNU Lesser General Public License
 *
 * @author [Zhangjiawei <jiawei.zhang@dfrobot.com>]
 * @version  V1.0
 * @date  2017-8-30
 * @https://github.com/DFRobot/DFRobot_SIM7000
 
