#ifndef __DFROBOT_SIM7000_H__
#define __DFROBOT_SIM7000_H__

#include <Arduino.h>
#include <stdint.h>
#include "stdio.h"
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <Wire.h>

#define DEFAULT_TIMEOUT              5    //seconds
#define DEFAULT_INTERCHAR_TIMEOUT 1500    //miliseconds

static SoftwareSerial SIM7000Serial(8,7); // RX, TX
extern Stream *serialSIM7000;

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
  int      SIM7000Send(const char *str, int len);
  int      SIM7000_check_readable(void);
  bool     setBaudRate(long rate);
  bool     init(void);
  bool     checkSignalQuality(void);
  bool     checkSIMStatus(void);
  bool     getRevision(void);
  bool     setNet(Net net);
  bool     attacthService(void);
  bool     bringupConnection(void);
  bool     SIM7000Connect(Protocol ptl,const char *host, int port, int timeout= DEFAULT_TIMEOUT, int chartimeoutchartimeout = DEFAULT_INTERCHAR_TIMEOUT);
  bool     SIM7000Close(void);
  void     SIM7000_send_cmd(const char* cmd);
  void     SIM7000_flush_serial(void);
  void     SIM7000_send_End_Mark(void);
  void     SIM7000_send_byte(uint8_t data);
  void     SIM7000_clean_buffer(char *buffer, int count);
  void     SIM7000_read_buffer(char* buffer,int count,  unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);
  boolean  SIM7000_check_with_cmd(const char* cmd, const char *resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT*5);
  boolean  SIM7000_wait_for_resp(const char* resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);
private:
  long     baudrate;
};

#endif  