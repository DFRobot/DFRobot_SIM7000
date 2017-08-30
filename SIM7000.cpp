#include "SIM7000.h"

long baudrate=115200;

int SIM7000_check_readable()
{
    return SIM7000Serial.available();
}

void SIM7000_send_cmd(const char* cmd)
{
    SIM7000Serial.begin(baudrate);
    SIM7000Serial.write(cmd);
}

boolean SIM7000_check_with_cmd(const char* cmd, const char *resp, DataType type,unsigned int timeout, unsigned int chartimeout)
{
    SIM7000_send_cmd(cmd);
    if(SIM7000_wait_for_resp(resp,type,timeout,chartimeout))
        return true;
    else
        return false;
}

boolean SIM7000_wait_for_resp(const char* resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
    int len = strlen(resp);
    int sum = 0;
    char c[50];
    unsigned long timerStart;//prevChar;  //prevChar is the time when the previous Char has been read.
    timerStart = millis();
    while(1) {
		if(SIM7000Serial.available()){
			while(SIM7000Serial.available()){
            Serial.write(SIM7000Serial.read());
            }
            return true;
        }
        /*
		if(SIM7000Serial.available()){
        
		    while(SIM7000Serial.available()){
            c[sum++]=SIM7000Serial.read();
            }
			
        for(sum=0;sum<=len;sum++)
        {
            if(c[sum]!=resp[sum])
                return false;
        }
	
            return true;
        }
		*/
        if((unsigned long)(millis() - timerStart) > timeout*1000){
            Serial.println("timeout");
            return false;
        }
    }
}


void SIM7000_read_buffer(char *buffer, int count, unsigned int timeout, unsigned int chartimeout)
{
    int i = 0;
    unsigned long timerStart, prevChar;
    timerStart = millis();
    prevChar = 0;
    char c;
    while(1) {
        while (SIM7000_check_readable()){
            c = SIM7000Serial.read();
            Serial.write(c);
            prevChar = millis();
            buffer[i++] = c;
            if(i >= count)
                break;
        }
        if ((unsigned long) (millis() - timerStart) > timeout * 1000){
            //Serial.println("read buffer timeout");
            break;
        }       
        if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)){
            //Serial.println("read bite timeout");
            break;
        }
    }
}

void SIM7000_clean_buffer(char *buffer, int count)
{
    for(int i=0; i < count; i++) {
        buffer[i] = '\0';
    }
}

void SIM7000_flush_serial()
{
    while(SIM7000Serial.available()){
        SIM7000Serial.read();
    }
}

void SIM7000_send_byte(uint8_t data)
{
    SIM7000Serial.write(data);
}

void SIM7000_send_End_Mark(void)
{
    SIM7000_send_byte((char)26);
}