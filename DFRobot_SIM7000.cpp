#include <DFrobot_SIM7000.h>

bool DFRobot_SIM7000::setBaudRate(long rate)
{
    char gprsBuffer[32];
    SIM7000_clean_buffer(gprsBuffer,32);
    delay(500);
    if( rate  ==  1200)
        SIM7000_send_cmd("AT+IPR=1200\r\n");
    else if(rate == 2400)
        SIM7000_send_cmd("AT+IPR=2400\r\n");
    else if(rate == 4800)
        SIM7000_send_cmd("AT+IPR=4800\r\n");
    else if(rate == 9600)
        SIM7000_send_cmd("AT+IPR=9600\r\n");
    else if(rate == 19200)
        SIM7000_send_cmd("AT+IPR=19200\r\n");
    else if(rate == 38400)
        SIM7000_send_cmd("AT+IPR=38400\r\n");
    else{
        Serial.println("No such rate");
        return false;
    }
    baudrate=rate;
    return true;
}

bool DFRobot_SIM7000::init(void)
{
    char gprsBuffer[32];
    int  count = 0;
    SIM7000_clean_buffer(gprsBuffer,32);
    while( count < 3){
        SIM7000_send_cmd("AT\r\n");
        SIM7000_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
        if((NULL != strstr(gprsBuffer,"OK"))){
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
        SIM7000_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
        if((NULL != strstr(gprsBuffer,"+CPIN: READY"))){
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
    if(net == NB){
        SIM7000_send_cmd("AT+CNVW=0,10,\"1E00\"\r\n");
        SIM7000_read_buffer(gprsBuffer, 40, DEFAULT_TIMEOUT);
        if(NULL != strstr(gprsBuffer, "OK"))
            return true;
        else
            return false;
    }else if(net == GPRS){
        SIM7000_send_cmd("AT+CNVW=0,10,\"0D00\"\r\n");
        SIM7000_read_buffer(gprsBuffer, 40, DEFAULT_TIMEOUT);
        if(NULL != strstr(gprsBuffer, "OK")){
            return true;
        }else
            return false;
    }else{
    Serial.println("No such mode!");
        return false;
    }
}

int DFRobot_SIM7000::checkSignalQuality(void)
{
    int i = 0,j = 0,k = 0;
    char gprsBuffer[26];
    char *p,*s;
    char buffers;
    SIM7000_flush_serial();
    SIM7000_clean_buffer(gprsBuffer, 26);
    SIM7000_send_cmd("AT+CSQ\r");
    SIM7000_read_buffer(gprsBuffer, 26, DEFAULT_TIMEOUT);
    if (NULL != (s = strstr(gprsBuffer, "+CSQ:"))){
        i = *(s + 6) - 48;
        j = *(s + 7) - 48;
        k = (i * 10) + j;
        return k;
    }
    return 0;
}

bool DFRobot_SIM7000::attacthService(void)
{
    char i;
    char *s;
    char gprsBuffer[32];
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CGATT?\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if(NULL != strstr(gprsBuffer, "+CGATT:")){
        delay(100);
    }else{
        Serial.println("Fail to attach service");
        return false;
    }
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CSTT\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if(NULL != strstr(gprsBuffer, "OK")){
        delay(100);
    }else{
        Serial.println("Fail to start task");
        return false;
    }
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CIICR\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT*100);
    if(NULL != strstr(gprsBuffer, "OK")){
        delay(500);
    }else{
        Serial.println("Fail to bring up wireless connection");
        return false;
    }
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CIFSR\r\n");
    SIM7000_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
    if (NULL != strstr(gprsBuffer,"ERROR")){
        Serial.println("Can not get local IP address");
        return false;
    }
    return true;
}

bool DFRobot_SIM7000::connect(Protocol ptl,const char *host, int port, int timeout, int chartimeout)
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
    SIM7000_read_buffer(resp, 96, DEFAULT_TIMEOUT*100, chartimeout*50);
    if(NULL != strstr(resp,"CONNECT OK")){
        return true;
    }
    return false;
}

void DFRobot_SIM7000::send(const char *str)
{
    char num[4];
    int len=strlen(str);
    if(len > 0){
        SIM7000_send_cmd("AT+CIPSEND=");
        itoa(len,num,10);
        SIM7000_send_cmd(num);
        SIM7000_send_cmd("\r\n");
        delay(500);
        SIM7000_send_cmd(str);
        delay(500);
        SIM7000_send_End_Mark();
    }
}

void DFRobot_SIM7000::send(const char *str,int len)
{
    char num[4];
    SIM7000_send_cmd("AT+CIPSEND=");
    itoa(len,num,10);
    SIM7000_send_cmd(num);
    SIM7000_send_cmd("\r\n");
    delay(500);
    SIM7000_send_cmd(str);
    delay(500);
    SIM7000_send_End_Mark();

}
int DFRobot_SIM7000::recv(char* buf,int maxlen,int timeout)
{
    char gprsBuffer[maxlen];
    SIM7000_clean_buffer(gprsBuffer,maxlen);
    int i=SIM7000_read_buffer(gprsBuffer,maxlen, timeout);
    memcpy(buf,gprsBuffer,i);
    return i;
}

bool DFRobot_SIM7000::close(void)
{
    char gprsBuffer[32];
    while(SIM7000Serial.available()){
        delay(100);
    }
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CIPCLOSE\r\n");
    SIM7000_read_buffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
    if(NULL != strstr(gprsBuffer, "OK")){
        delay(500);
    }else{
        Serial.println("Fail to close connect");
        return false;
    }
    SIM7000_send_cmd("AT+CIPSHUT\r\n");
    return true;
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

int DFRobot_SIM7000::SIM7000_read_buffer(char *buffer, int count, unsigned int timeout, unsigned int chartimeout)
{
    int i = 0;
    unsigned long timerStart, prevChar;
    timerStart = millis();
    prevChar = 0;
    while(1){
        while(SIM7000_check_readable()){
            buffer[i++] = SIM7000Serial.read();
            prevChar = millis();
            if(i >= count)
                return i;
        }
        if(timeout){
            if((unsigned long) (millis() - timerStart) > timeout * 1000){
                Serial.println("Get head timeout");
                break;
            }
        }
        if(((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)){
            break;
        }
    }
    return i;
}

boolean DFRobot_SIM7000::SIM7000_wait_for_resp(const char* resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
    int len = strlen(resp);
    int sum = 0;
    char c[50];
    unsigned long timerStart;
    timerStart = millis();
    while(1){
        if(SIM7000Serial.available()){
            while(SIM7000Serial.available()){
            Serial.write(SIM7000Serial.read());
            }
        }
        if((unsigned long)(millis() - timerStart) > timeout*3000){
            return false;
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

bool DFRobot_SIM7000::turnON(void)
{
    delay(300);
    char gprsBuffer[32];
    SIM7000_clean_buffer(gprsBuffer,32);
    baudrate = 115200;
    SIM7000Serial.begin(baudrate);
    pinMode(12,OUTPUT);
    while(1){
        digitalWrite(12, HIGH);
        delay(2000);
        digitalWrite(12, LOW);
        while(1){
            if(SIM7000Serial.available()){
                while(SIM7000Serial.available()){
                SIM7000_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
                }
                if((NULL != strstr(gprsBuffer,"1"))){
                return true;
                }
                if((NULL != strstr(gprsBuffer,"+"))){
                return true;
                }
            }
        }
    }
}

bool DFRobot_SIM7000::turnOFF(void){
    char gprsBuffer[32];
    SIM7000_clean_buffer(gprsBuffer,32);
    SIM7000_send_cmd("AT+CPOWD=1\r\n");
    SIM7000_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
    if((NULL != strstr(gprsBuffer,"DOWN"))){
            return true;
    }

}