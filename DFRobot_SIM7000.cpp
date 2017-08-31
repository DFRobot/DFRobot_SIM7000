#include "DFrobot_SIM7000.h"

bool DFRobot_SIM7000::setBaudRate(long rate)
{
    Serial.println("Ready to set baud rate");
    baudrate=115200;
    SIM7000Serial.begin(baudrate);
    while(1){
        if(SIM7000Serial.available()){
            while(SIM7000Serial.available()){
            Serial.write(SIM7000Serial.read());
            }
            break;
        }
    }
    delay(2000);
    if(rate==1200)
        SIM7000_send_cmd("AT+IPR=1200\r\n");
    else if(rate==2400)
        SIM7000_send_cmd("AT+IPR=2400\r\n");
    else if(rate==4800)
        SIM7000_send_cmd("AT+IPR=4800\r\n");
    else if(rate==9600)
        SIM7000_send_cmd("AT+IPR=9600\r\n");
    else if(rate==19200)
        SIM7000_send_cmd("AT+IPR=19200\r\n");
    else if(rate==38400)
        SIM7000_send_cmd("AT+IPR=38400\r\n");
    else{
        Serial.println("No such rate");
        return false;
    }
    Serial.print("Set baud rate:");
    Serial.println(rate);
    baudrate=rate;
}

bool DFRobot_SIM7000::init(void)
{
    char gprsBuffer[32];
    int  count = 0;
    SIM7000_clean_buffer(gprsBuffer,32);
    while(count < 3){
        SIM7000_send_cmd("AT\r\n");
        SIM7000_read_buffer(gprsBuffer,32);
        if((NULL != strstr(gprsBuffer,"OK"))){ 
            Serial.println("AT command READY");        
            break;
        }
        count++;
        delay(300);
    }
    if(count == 3){
        return false;
    }
    return true;
}

bool DFRobot_SIM7000::checkSIMStatus(void)
{
    char gprsBuffer[32];
    int  count = 0;
    SIM7000_clean_buffer(gprsBuffer,32);
    while(count < 3){
        SIM7000_send_cmd("AT+CPIN?\r\n");
        SIM7000_read_buffer(gprsBuffer,32);
        if((NULL != strstr(gprsBuffer,"+CPIN: READY"))){ 
            Serial.println("SIM card READY");        
            break;
        }
        count++;
        delay(300);
    }
    if(count == 3){
        return false;
    }
    return true;
}

bool DFRobot_SIM7000::getRevision(void)
{
    char gprsBuffer[90];
    int  count = 0;
    SIM7000_clean_buffer(gprsBuffer,90);
    while(count < 3){
        SIM7000_send_cmd("AT+CGMR\r\n");
        SIM7000_read_buffer(gprsBuffer,90);    
        if((NULL != strstr(gprsBuffer,"Revision"))){
            break;
        }
        count++;
        delay(300);
    }
    if(count == 3){
        return false;
    }
    return true;
}

bool DFRobot_SIM7000::setNet(Net net)
{
    char gprsBuffer[40];
    if(net==NB){
        SIM7000_send_cmd("AT+CNVW=0,10,\"1E00\"\r\n");
        SIM7000_read_buffer(gprsBuffer, 40, DEFAULT_TIMEOUT);
        if(NULL != strstr(gprsBuffer, "OK")){
            Serial.println("Set NB-IOT mode");
            return true;
        }else{
            Serial.println("Fail to set NB-IOT mode");
            while(1){
                delay(100);
            }
            return false;
        }
    }else if(net==GPRS){
        SIM7000_send_cmd("AT+CNVW=0,10,\"0D00\"\r\n");
        SIM7000_read_buffer(gprsBuffer, 40, DEFAULT_TIMEOUT);
        if(NULL != strstr(gprsBuffer, "OK")){
            Serial.println("Set GPRS mode");
            return true;
        }else{
            Serial.println("Fail to set GPRS mode");
            while(1){
                delay(100);
            }
            return false;
        }
    }else{
    Serial.println("No such mode!");
        return false;
    }
}

bool DFRobot_SIM7000::checkSignalQuality(void)
{
    char i = 0;
    char gprsBuffer[26];
    char *p,*s;
    char buffers;
    SIM7000_flush_serial();
    SIM7000_clean_buffer(gprsBuffer, 26);
    SIM7000_send_cmd("AT+CSQ\r");
    SIM7000_read_buffer(gprsBuffer, 26, DEFAULT_TIMEOUT);
    if (NULL != (s = strstr(gprsBuffer, "+CSQ:"))){
        Serial.print("signal strength:");
        Serial.print(*(s+6));
        Serial.println(*(s+7));
        return true;
    }
    return false;
}

bool DFRobot_SIM7000::attacthService(void)
{
    char i;
    char *s;
    char gprsBuffer[32];
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CGATT?\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if(NULL != strstr(gprsBuffer, "+CGATT: 1")){
        Serial.println("Attach service");    
    }else{
        Serial.println("Fail to attach service");
        return false;
    }
    delay(100);
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CSTT\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if(NULL != strstr(gprsBuffer, "OK")){
        Serial.println("Start task");    
    }else{
        Serial.println("Fail to start task");
        return false;
    }
    delay(100);
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CIICR\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if(NULL != strstr(gprsBuffer, "OK")){
        Serial.println("Bring up wireless connection");    
    }else{
        Serial.println("Fail to bring up wireless connection");
        return false;
    }
    delay(1000);
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CIFSR\r\n");
    SIM7000_read_buffer(gprsBuffer,32);
    if (NULL != strstr(gprsBuffer,"ERROR")){
        Serial.println("Can not get local IP address");
        return false;
    }
    s=strstr(gprsBuffer,"\n");
    Serial.print("Local IP address:");
    Serial.println(s);
    return false;
}

bool DFRobot_SIM7000::SIM7000Connect(Protocol ptl,const char *host, int port, int timeout, int chartimeout)
{
    char num[4];
    char resp[96];
    if(ptl == TCP){
        SIM7000_send_cmd("AT+CIPSTART=\"TCP\",\"");
        SIM7000_send_cmd(host);
        SIM7000_send_cmd("\",");
        itoa(port, num, 10);
        SIM7000_send_cmd(num);
        SIM7000_send_cmd("\r\n");
    }else if(ptl == UDP){
        SIM7000_send_cmd("AT+CIPSTART=\"UDP\",\"");
        SIM7000_send_cmd(host);
        SIM7000_send_cmd("\",");
        itoa(port, num, 10);
        SIM7000_send_cmd(num);
        SIM7000_send_cmd("\r\n");
    }else{
        Serial.println("No such mode!");
        return false;
    }
    SIM7000_read_buffer(resp, 96, timeout, chartimeout);  
    if(NULL != strstr(resp,"CONNECT OK")){
        Serial.println("Connect OK!");
        return true;
    }
    Serial.println("Fail to connect");
    return false;
}

int DFRobot_SIM7000::SIM7000Send(const char *str, int len)
{
    char num[4],gprsBuffer[32];
    SIM7000_clean_buffer(gprsBuffer,32);
    if(len > 0){
        SIM7000_send_cmd("AT+CIPSEND=");
        itoa(len,num,10);
        SIM7000_send_cmd(num);
        SIM7000_send_cmd("\r\n");
        delay(500);
        SIM7000_send_cmd(str);
        delay(500);
        SIM7000_send_End_Mark();
        SIM7000_read_buffer(gprsBuffer,32+len, DEFAULT_TIMEOUT);
        if(NULL!=strstr(gprsBuffer,"OK")){
            Serial.println("Send OK");
            return len;
        }else{
            Serial.println("Fail to send");
            return 0;
        }
    }
}

bool DFRobot_SIM7000::SIM7000Close(void)
{
    char gprsBuffer[32];
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CIPCLOSE\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if(NULL != strstr(gprsBuffer, "OK")){
        Serial.println("Close connect");    
    }else{
        Serial.println("Fail to close connect");
        return false;
    }
    delay(500);
    SIM7000_send_cmd("AT+CIPSHUT\r\n");
    delay(500);
}

int DFRobot_SIM7000::SIM7000_check_readable(void)
{
    return SIM7000Serial.available();
}

void DFRobot_SIM7000::SIM7000_send_cmd(const char* cmd)
{
    SIM7000Serial.begin(baudrate);
    SIM7000Serial.write(cmd);
}

boolean DFRobot_SIM7000::SIM7000_check_with_cmd(const char* cmd, const char *resp, DataType type,unsigned int timeout, unsigned int chartimeout)
{
    SIM7000_send_cmd(cmd);
    if(SIM7000_wait_for_resp(resp,type,timeout,chartimeout))
        return true;
    else
        return false;
}

boolean DFRobot_SIM7000::SIM7000_wait_for_resp(const char* resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
    int len = strlen(resp);
    int sum = 0;
    char c[50];
    unsigned long timerStart;//prevChar;  //prevChar is the time when the previous Char has been read.
    timerStart = millis();
    while(1){
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

void DFRobot_SIM7000::SIM7000_read_buffer(char *buffer, int count, unsigned int timeout, unsigned int chartimeout)
{
    int i = 0;
    unsigned long timerStart, prevChar;
    timerStart = millis();
    prevChar = 0;
    char c;
    while(1){
        while (SIM7000_check_readable()){
            c = SIM7000Serial.read();
            prevChar = millis();
            buffer[i++] = c;
            if(i >= count)
                break;
        }
        if((unsigned long) (millis() - timerStart) > timeout * 1000){
            //Serial.println("timeout");
            break;
        }       
        if(((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)){
            //Serial.println("timeout");
            break;
        }
    }
}

void DFRobot_SIM7000::SIM7000_clean_buffer(char *buffer, int count)
{
    for(int i=0; i < count; i++){
        buffer[i] = '\0';
    }
}

void DFRobot_SIM7000::SIM7000_flush_serial(void)
{
    while(SIM7000Serial.available()){
        SIM7000Serial.read();
    }
}

void DFRobot_SIM7000::SIM7000_send_byte(uint8_t data)
{
    SIM7000Serial.write(data);
}

void DFRobot_SIM7000::SIM7000_send_End_Mark(void)
{
    SIM7000_send_byte((char)26);
}
