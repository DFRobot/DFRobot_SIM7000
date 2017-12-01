#ifndef __DFROBOT_SIM7000_H__
#define __DFROBOT_SIM7000_H__

#include "DFRobot_SIMcore.h"

#define ON  0
#define OFF 1

enum Protocol {
    CLOSED = 0,
    TCP    = 1,
    UDP    = 2,
};

enum Net{
    GPRS,
    NB,
};

enum DataType {
    CMD     = 0,
    DATA    = 1,
};

class DFRobot_SIM7000 : public DFRobot_SIMcore
{
public:
    int      recv(char* buf,int maxlen,int timeout);
    int      checkSignalQuality(void);
    bool     setNet(Net net);
    bool     attacthService(void);
    bool     setBaudRate(long rate);
    bool     checkSIMStatus(void);
    bool     connect(Protocol ptl,const char *host, int port);
    bool     close(void);
    bool     turnON(void);
    bool     initPos(void);
    bool     send(void *buffer,size_t len);
    bool     send(char *data);
    bool     getPosition(void);
    char*    getLatitude(void);
    char*    getLongitude(void);
private:
    char     latitude[8];
    char     longitude[8];
    long     SIM7000baudrate;
};

#endif