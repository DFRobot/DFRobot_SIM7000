#include <stdint.h>
#include "stdio.h"
#include "DFrobot_SIM7000.h"

extern long baudrate;

bool DFRobot_SIM7000::setBaudRate(void)
{
    Serial.println("setBaudRate");
    SIM7000Serial.begin(baudrate);
    while(1){
	    if(SIM7000Serial.available()){
            while(SIM7000Serial.available()){
            Serial.write(SIM7000Serial.read());
            }
            break;
        }
    }
    Serial.println("begin to set BaudRate");
    delay(2000);
    unsigned long timerStart;
    timerStart = millis();
    SIM7000_send_cmd("AT+IPR=38400\r\n");
    while(1) {
        if(SIM7000Serial.available()){
            while(SIM7000Serial.available()){
                Serial.write(SIM7000Serial.read());
            }
            Serial.println("set BaudRate to 38400");
            return true;
        }
        if ((unsigned long)(millis() - timerStart) > 5000){
            Serial.println("fail to set baud rate");
            return false;
        }
    }
    baudrate=38400;
}

bool DFRobot_SIM7000::init(void)
{
    if(!SIM7000_check_with_cmd("AT\r\n","OK\r\n",CMD)){   
	    Serial.println("AT command is invalid");
        return false;
    }
    else
        Serial.println("AT command is valid");
    delay(1000);
    if(!SIM7000_check_with_cmd("AT+CPIN?r\n","+CPIN: READY\r\n",CMD)) {
        Serial.println("SIM card is invalid");
        return false;
    }
    else
    Serial.println("SIM card is valid");
    return true;
}

bool DFRobot_SIM7000::checkSIMStatus(void)
{
    char gprsBuffer[32];
    int  count = 0;
    SIM7000_clean_buffer(gprsBuffer,32);
    while(count < 3) {
        SIM7000_send_cmd("AT+CPIN?\r\n");
        SIM7000_read_buffer(gprsBuffer,32);
        if((NULL != strstr(gprsBuffer,"+CPIN: READY"))) { 
        Serial.println("SIM card READY");		
        break;
        }
        count++;
        delay(300);
    }
    if(count == 3) {
        return false;
    }
    return true;
}

bool DFRobot_SIM7000::getRevision(void)
{
    char gprsBuffer[90];
    int  count = 0;
    SIM7000_clean_buffer(gprsBuffer,90);
    while(count < 3) {
        SIM7000_send_cmd("AT+CGMR\r\n");
        SIM7000_read_buffer(gprsBuffer,90);	
        if((NULL != strstr(gprsBuffer,"Revision"))) {         	
        break;
        }
        count++;
        delay(300);
    }
    if(count == 3) {
        return false;
    }
    return true;
}

bool DFRobot_SIM7000::setNet(Net net)
{
    if(net==NB){
    SIM7000_check_with_cmd("AT+CNVW=0,10,\"1E00\"\r\n","OK\r\n",CMD);
    return true;
    }
    else if(net==GPRS){
    SIM7000_check_with_cmd("AT+CNVW=0,10,\"0D00\"\r\n","OK\r\n",CMD);
    return true;
    }
    else{
    Serial.println("No such mode!");		
    return false;   
    }
}

bool DFRobot_SIM7000::checkSignalQuality(void)
{
    char i = 0;
    char gprsBuffer[26];
    char *p, *s;
    char buffers;
    SIM7000_flush_serial();
    SIM7000_clean_buffer(gprsBuffer, 26);
    SIM7000_send_cmd("AT+CSQ\r");
    SIM7000_read_buffer(gprsBuffer, 26, DEFAULT_TIMEOUT);
    if (NULL != (s = strstr(gprsBuffer, "+CSQ:"))) {
        s = strstr((char *)(s), " ");
        s = s + 1;  
        p = strstr((char *)(s), ","); 
        if (NULL != s) {
            i = 0;
            buffers=*(s)*10+*(s+1);
            Serial.println(buffers);
        }
        return true;
    }
    return false;
}

bool DFRobot_SIM7000::attacthService(void)
{
    char i;
    char *p, *s;
    char ipAddr[32];
    SIM7000_clean_buffer(ipAddr,32);
    SIM7000_check_with_cmd("AT+CGATT?\r\n","OK\r\n", CMD);
    delay(100);
    SIM7000_check_with_cmd("AT+CSTT\r\n", "OK\r\n", CMD);
    delay(100);
    SIM7000_check_with_cmd("AT+CIICR\r\n","OK\r\n", CMD);
    delay(1000);
    SIM7000_check_with_cmd("AT+CIFSR\r\n","OK\r\n", CMD);
    SIM7000_read_buffer(ipAddr,32);
    if (NULL != strstr(ipAddr,"ERROR")) {
        return false;
    }
    s = ipAddr + 11;
    p = strstr((char *)(s),"\r\n"); //p is last character \r\n
    if (NULL != s) {
        i = 0;
        while (s < p) {
            ip_string[i++] = *(s++);
        }
        ip_string[i] = '\0';            
    }
    _ip = str_to_ip(ip_string);
    if(_ip != 0) {
        return true;
    }
    return false;
}

bool DFRobot_SIM7000::SIM7000Connect(Protocol ptl,const char *host, int port, int timeout, int chartimeout)
{
    char num[4];
    char resp[96];
    if(ptl == TCP) {
        SIM7000_send_cmd("AT+CIPSTART=\"TCP\",\"");
        SIM7000_send_cmd(host);
        SIM7000_send_cmd("\",");
        itoa(port, num, 10);
        SIM7000_send_cmd(num);
        SIM7000_send_cmd("\r\n");
    } 
    else if(ptl == UDP) {
        SIM7000_send_cmd("AT+CIPSTART=\"UDP\",\"");
        SIM7000_send_cmd(host);
        SIM7000_send_cmd("\",");
        itoa(port, num, 10);
        SIM7000_send_cmd(num);
        SIM7000_send_cmd("\r\n");
    } else {
        return false;
    }
    SIM7000_read_buffer(resp, 96, timeout, chartimeout);  
    if(NULL != strstr(resp,"CONNECT OK")) {
        return true;
    }
    return false;
}

int DFRobot_SIM7000::SIM7000Send(const char *str, int len)
{
    char num[4];
    if(len > 0){
        SIM7000_send_cmd("AT+CIPSEND=");
        itoa(len, num, 10);
        SIM7000_send_cmd(num);
        if(!SIM7000_check_with_cmd("\r\n",">",CMD)) {
            return 0;
        }
        delay(500);
        SIM7000_send_cmd(str);
        delay(500);
        SIM7000_send_End_Mark();
        if(!SIM7000_wait_for_resp("SEND OK\r\n", DATA, DEFAULT_TIMEOUT * 10, DEFAULT_INTERCHAR_TIMEOUT * 10)) {
            return 0;
        }        
    }
    return len;
}

bool DFRobot_SIM7000::SIM7000Close(void)
{
    SIM7000_check_with_cmd("AT+CIPCLOSE\r\n","OK\r\n", CMD);
    delay(500);
    SIM7000_check_with_cmd("AT+CIPSHUT\r\n","OK\r\n",CMD);
    delay(500);
}

uint32_t DFRobot_SIM7000::str_to_ip(const char* str)
{
    uint32_t ip = 0;
    char* p = (char*)str;
    for(int i = 0; i < 4; i++) {
        ip |= atoi(p);
        p = strchr(p, '.');
        if (p == NULL) {
            break;
        }
        ip <<= 8;
        p++;
    }
    return ip;
}
