#ifndef __DFROBOT_SIM7000_H__
#define __DFROBOT_SIM7000_H__

#include "SIM7000.h"


enum Protocol {
    CLOSED = 0,
    TCP    = 1,
    UDP    = 2,
};

enum Net{
	GPRS,
	NB,
};

extern Stream *serialSIM7000;
class DFRobot_SIM7000
{
public:
  bool setBaudRate(void);
  bool init(void);
  bool checkSignalQuality(void);
  bool checkSIMStatus(void);
  bool getRevision(void);
  bool setNet(Net net);
  bool attacthService(void);
  bool bringupConnection(void);
  bool SIM7000Connect(Protocol ptl,const char *host, int port, int timeout= DEFAULT_TIMEOUT, int chartimeoutchartimeout = DEFAULT_INTERCHAR_TIMEOUT);
  int  SIM7000Send(const char *str, int len);
  bool SIM7000Close(void);
private:
  uint32_t str_to_ip(const char* str);
  uint32_t _ip;
  char ip_string[16];
};


#endif  