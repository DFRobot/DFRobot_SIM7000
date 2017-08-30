#ifndef __SIM7000_H__
#define __SIM7000_H__

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <Wire.h>

#define DEFAULT_TIMEOUT     		 5   //seconds
#define DEFAULT_INTERCHAR_TIMEOUT 1500   //miliseconds

static SoftwareSerial SIM7000Serial(8,7); // RX, TX

enum DataType {
    CMD     = 0,
    DATA    = 1,
};
int      SIM7000_check_readable();
void     SIM7000_flush_serial();
void     SIM7000_send_End_Mark();
void     SIM7000_send_cmd(const char* cmd);
void     SIM7000_send_byte(uint8_t data);
void     SIM7000_clean_buffer(char *buffer, int count);
void     SIM7000_read_buffer(char* buffer,int count,  unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);
boolean  SIM7000_check_with_cmd(const char* cmd, const char *resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT*5);
boolean  SIM7000_wait_for_resp(const char* resp, DataType type, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);

#endif