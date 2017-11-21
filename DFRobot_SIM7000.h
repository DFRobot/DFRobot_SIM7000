#ifndef __DFROBOT_SIM7000_H__
#define __DFROBOT_SIM7000_H__

#include <Arduino.h>
#include <stdint.h>
#include "stdio.h"
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <Wire.h>

#define DEFAULT_TIMEOUT                 5    //seconds
#define DEFAULT_INTERCHAR_TIMEOUT    1500    //miliseconds

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

class DFRobot_SIM7000
{
public:
    int      checkSignalQuality(void);
    int      SIM7000_check_readable(void);
    int      recv(char* buf,int maxlen,int timeout);
    int      SIM7000_read_buffer(char* buffer,int count,  unsigned int timeout = 0, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);
    bool     init(void);
    bool     setNet(Net net);
    bool     checkSIMStatus(void);
    bool     attacthService(void);
    bool     setBaudRate(long rate);
    bool     bringupConnection(void);
    bool     connect(Protocol ptl,const char *host, int port, int timeout= DEFAULT_TIMEOUT, int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);
    bool     close(void);
    bool     turnON(void);
    bool     turnOFF(void);
    void     begin(Stream &s_);
    void     send(const char *str);
    void     send(void *buffer,size_t len);
    void     SIM7000_flush_serial(void);
    void     SIM7000_send_End_Mark(void);
    void     SIM7000_send_cmd(const char* cmd);
    void     SIM7000_send_byte(uint8_t data);
    void     SIM7000_clean_buffer(char *buffer, int count);
    boolean  SIM7000_check_with_cmd(const char* cmd, const char *resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT*5);
    boolean  SIM7000_wait_for_resp(const char* resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);
private:
    long     baudrate=38400;
};

#endif