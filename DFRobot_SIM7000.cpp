#include <DFRobot_SIM7000.h>

bool  DFRobot_SIM7000::setBaudRate(long rate)
{
    int  count = 0;
    while(count <3){
        if( rate  ==  1200){
            if(check_send_cmd("AT+IPR=1200\r\n","OK")){
                baudrate = 1200;
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 2400){
            if(check_send_cmd("AT+IPR=2400\r\n","OK")){
                baudrate = 2400;
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 4800){
            if(check_send_cmd("AT+IPR=4800\r\n","OK")){
                baudrate = 4800;
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 9600){
            if(check_send_cmd("AT+IPR=9600\r\n","OK")){
                baudrate = 9600;
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 19200){
            if(check_send_cmd("AT+IPR=19200\r\n","OK")){
                baudrate = 19200;
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 38400){
            if(check_send_cmd("AT+IPR=38400\r\n","OK")){
                baudrate = 38400;
                break;
            }else{
                count++;
                delay(200);
            }
        }else{
            Serial.println("No such rate");
            return false;
        }
    }
    setRate(baudrate);
    if(count == 3){
        closeCommand();
        return false;
    }
    setCommandCounter(1);
    return true;
}

bool  DFRobot_SIM7000::checkSIMStatus(void)
{
    if(getCommandCounter() == 1){
        int count = 0;
        while(count < 3){
            if(check_send_cmd("AT\r\n","OK")){
                break;
            }else{
                count++;
                delay(300);
            }
        }
        if(count == 3){
            closeCommand();
            return false;
        }
        count = 0;
        while(count < 3){
            if(check_send_cmd("AT+CPIN?\r\n","READY")){
                break;
            }else{
                count++;
                delay(300);
            }
        }
        if(count == 3){
            closeCommand();
            return false;
        }
        setCommandCounter(2);
        return true;
    }else{
        closeCommand();
        return false;
    }
}

bool  DFRobot_SIM7000::setNet(Net net)
{
    if(getCommandCounter() == 2){
        if(net == NB){
            if(check_send_cmd("AT+CNMP=38\r\n","OK")){
                delay(300);
                if(check_send_cmd("AT+CMNB=2\r\n","OK")){
                    setCommandCounter(3);
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else if(net == GPRS){
            if(check_send_cmd("AT+CNVW=0,10,\"0D00\"\r\n","OK")){
                setCommandCounter(3);
                return true;
            }else{
                return false;
            }
        }else{
            Serial.println("No such mode!");
            return false;
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::attacthService(void)
{
    if(getCommandCounter() == 3){
        char  i;
        char *s;
        char gprsBuffer[32];
        cleanBuffer(gprsBuffer,32);
        send_cmd("AT+CGATT=1\r\n");
        while(1){
            readBuffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
            if(NULL != strstr(gprsBuffer, "OK")){
                delay(100);
                break;
            }
            if(NULL != strstr(gprsBuffer, "ERROR")){
                return false;
            }
        }
        cleanBuffer(gprsBuffer,32);
        if(check_send_cmd("AT+CSTT\r\n","OK")){
            delay(100);
        }else{
            return false;
        }
        send_cmd("AT+CIICR\r\n");
        while(1){
            readBuffer(gprsBuffer, 32);
            if(NULL != strstr(gprsBuffer, "OK")){
                delay(200);
                break;
            }else if(NULL != strstr(gprsBuffer,"ERROR")){
                return false;
            }
        }
        if(check_send_cmd("AT+CIFSR\r\n","ERROR")){
            return false;
        }
        setCommandCounter(4);
        return true;
    }else{
        return false;
    }
}

int   DFRobot_SIM7000::checkSignalQuality(void)
{
    if(getCommandCounter() > 1){
        char  signalBuffer[26];
        int i = 0,j = 0,k = 0;
        char *signalQuality;
        cleanBuffer(signalBuffer,26);
        send_cmd("AT+CSQ\r\n");
        readBuffer(signalBuffer,26);
        if (NULL != (signalQuality = strstr(signalBuffer, "+CSQ:"))){
            i = *(signalQuality + 6) - 48;
            j = *(signalQuality + 7) - 48;
            k = (i * 10) + j;
        }else{
            closeCommand();
            return 0;
        }
        if( k == 99){
            closeCommand();
            return 0;
        }else{
            return k;
        }
    }else{
        return 0;
    }
}

bool  DFRobot_SIM7000::connect(Protocol ptl,const char *host, int port)
{
    if(getCommandCounter() > 3){
        char num[4];
        char resp[96];
        if(ptl == TCP){
            send_cmd("AT+CIPSTART=\"TCP\",\"");
            send_cmd(host);
            send_cmd("\",");
            itoa(port, num, 10);
            send_cmd(num);
            send_cmd("\r\n");
        }else if(ptl == UDP){
            send_cmd("AT+CIPSTART=\"UDP\",\"");
            send_cmd(host);
            send_cmd("\",");
            itoa(port, num, 10);
            send_cmd(num);
            send_cmd("\r\n");
        }else{
            Serial.println("No such mode!");
            return false;
        }
        while(1){
            while(checkReadable()){
                cleanBuffer(resp, 96);
                readBuffer(resp, 96,DEFAULT_TIMEOUT);
                if(NULL != strstr(resp,"CONNECT OK")){
                    setCommandCounter(9);
                    return true;
                }
                if(NULL != strstr(resp,"CONNECT FAIL")){
                    return false;
                }
            }
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::turnON(void)
{
    delay(300);
    char gprsBuffer[32];
    cleanBuffer(gprsBuffer,32);
    baudrate = 19200;
    setRate(baudrate);
    pinMode(12,OUTPUT);
    while(1){
        digitalWrite(12, HIGH);
        delay(2000);
        digitalWrite(12, LOW);
        while(checkReadable()){
            readBuffer(gprsBuffer,32,DEFAULT_TIMEOUT);
            if((NULL != strstr(gprsBuffer,"1"))){
                return true;
            }
            if((NULL != strstr(gprsBuffer,"+"))){
                return true;
            }
        }
        delay(5000);
        delay(5000);
        if(check_send_cmd("AT\r\n","OK")){
            return true;
        }
    }
}

bool  DFRobot_SIM7000::initPos(void)
{
    if(check_send_cmd("AT+CGNSPWR=1\r\n","OK")){
        delay(50);
        setCommandCounter(3);
        return true;
    }else{
        return false;
    }

}

bool  DFRobot_SIM7000::send(char *data)
{
    if(getCommandCounter() == 9){
        char num[4];
        char resp[20];
        int len = strlen(data);
        itoa(len, num, 10);
        send_cmd("AT+CIPSEND=");
        send_cmd(num);
        if(check_send_cmd("\r\n",">")){
            send_cmd(data);
            while(1){
                while(checkReadable()){
                    readBuffer(resp,20);
                    if(NULL != strstr(resp,"OK")){
                        return true;
                    }
                    if(NULL != strstr(resp,"ERROR")){
                        return false;
                    }
                }
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::send(void *buffer,size_t len)
{
    if(getCommandCounter() == 9){
        char num[4];
        itoa(len, num, 10);
        send_cmd("AT+CIPSEND=");
        send_cmd(num);
        if(check_send_cmd("\r\n",">")){
            if(check_send_cmd(buffer,"OK")){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::MQTTconnect(char* iot_client, char* iot_username, char* iot_key)
{
    if(getCommandCounter() == 9){
        if(check_send_cmd("AT+CIPSEND\r\n",">")){
            char     MQTThead[10]={0x00,0x04,0x4d,0x51,0x54,0x54,0x04,0xc2,0x0b,0xb8};
            
            char MQTTbuff[50]={0};
            MQTTbuff[0] = 0x10;
            send_buff(MQTTbuff,1);
            int leng = 10;
            leng += strlen(iot_client)+2;
            leng += strlen(iot_username)+2;
            leng += strlen(iot_key)+2;
            MQTTbuff[0] = leng ;
            send_buff(MQTTbuff,1);
            send_buff(MQTThead,10);
            send_buff(MQTThead,1);
            MQTTbuff[0]=strlen(iot_client);
            send_buff(MQTTbuff,1);
            send_cmd(iot_client);
            send_buff(MQTThead,1);
            MQTTbuff[0]=strlen(iot_username);
            send_buff(MQTTbuff,1);
            send_cmd(iot_username);
            send_buff(MQTThead,1);
            MQTTbuff[0]=strlen(iot_key);
            send_buff(MQTTbuff,1);
            send_cmd(iot_key);
            if(check_send_cmd("","CLOSED")){
                return false;
            }else{
                setCommandCounter(10);
                return true;
            }
        }
        return false;
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::MQTTsend(char* iot_topic, char* iot_data)
{
    if(getCommandCounter() == 10){
        if(check_send_cmd("AT+CIPSEND\r\n",">")){
            char     MQTTdata[2]={0x00,0x04};
            char     MQTTbuff[50]={0};
            MQTTbuff[0] = 0x32;
            send_buff(MQTTbuff,1);
            MQTTbuff[0] = strlen(iot_topic)+strlen(iot_data)+4;
            send_buff(MQTTbuff,2);
            MQTTbuff[0] = strlen(iot_topic);
            send_buff(MQTTbuff,1);
            send_cmd(iot_topic);
            send_buff(MQTTdata,2);
            send_cmd(iot_data);
            if(check_send_cmd("","CLOSED")){
                return false;
            }else{
                return true;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::MQTTsubscribe(char* iot_topic)
{
    if(getCommandCounter() == 10){
        if(check_send_cmd("AT+CIPSEND\r\n",">")){
            char     MQTTbuff[10]={0};
            MQTTbuff[0] = 0x82;
            MQTTbuff[1] = strlen(iot_topic)+5;
            MQTTbuff[3] = 0x0a;
            MQTTbuff[5] = strlen(iot_topic);
            send_buff(MQTTbuff,6);
            send_cmd(iot_topic);
            MQTTbuff[0] = 0x01;
            send_buff(MQTTbuff,1);
            if(check_send_cmd("","CLOSED")){
                return false;
            }else{
                setCommandCounter(11);
                return true;
            }
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::MQTTunsubscribe(char* iot_topic)
{
    if(getCommandCounter() == 11){
        if(check_send_cmd("AT+CIPSEND\r\n",">")){
            char     MQTTbuff[10]={0};
            MQTTbuff[0] = 0xa2;
            MQTTbuff[1] = strlen(iot_topic)+4;
            MQTTbuff[3] = 0x0a;
            MQTTbuff[5] = strlen(iot_topic);
            send_buff(MQTTbuff,6);
            send_cmd(iot_topic);
            if(check_send_cmd("","CLOSED")){
                return false;
            }else{
                return true;
                setCommandCounter(10);
            }
        }else{
            return false;
        }
    }
}

bool  DFRobot_SIM7000::MQTTrecv(char* iot_topic, char* buf, int maxlen)
{
    if(getCommandCounter() == 11){
        char   MQTTbuff[maxlen+30];
        char  *p; 
        cleanBuffer(MQTTbuff,maxlen+30);
        int i = readBuffer(MQTTbuff,maxlen+30);
        for(int j=0;j<i;j++){
            if(NULL != (p = strstr(MQTTbuff+j,iot_topic))){
                memcpy(buf,p+strlen(iot_topic),maxlen+30);
                return true;
            }
        }
        return false;
    }else{
        return false;
    }
}

bool  DFRobot_SIM7000::MQTTdisconnect(void)
{
    if(check_send_cmd("AT+CIPSEND\r\n",">")){
        char     MQTTdata[2]={0xe0,0x00};
        send_buff(MQTTdata,2);
        if(check_send_cmd("","CLOSED")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

int   DFRobot_SIM7000::recv(char* buf, int maxlen, int timeout)
{
    char gprsBuffer[maxlen];
    cleanBuffer(gprsBuffer,maxlen);
    int i=readBuffer(gprsBuffer,maxlen, timeout);
    memcpy(buf,gprsBuffer,i);
    return i;
}

bool  DFRobot_SIM7000::getPosition(void)
{
    char  posBuffer[150];
    char *position;
    cleanBuffer(posBuffer,150);
    if(getCommandCounter() == 3 || getCommandCounter() == 6){
        send_cmd("AT+CGNSINF\r\n");
        readBuffer(posBuffer,150);
        if(NULL != strstr(posBuffer,"+CGNSINF: 1,1")){
            setCommandCounter(4);
        }else{
            return false;
        }
    }else{
        return false;
    }
    if(getCommandCounter() == 4){
        position  = strstr(posBuffer,".000");
        memcpy(latitude , position+5 , 7);
        memcpy(longitude, position+15, 7);
        setCommandCounter(5);
        return true;
    }else{
        return false;
    }
}

char* DFRobot_SIM7000::getLatitude(void)
{
    if(getCommandCounter() >= 5){
        setCommandCounter(6);
        return latitude;
    }else{
        return "error";
    }
}

char* DFRobot_SIM7000::getLongitude(void)
{
    if(getCommandCounter() >= 5){
        setCommandCounter(6);
        return longitude;
    }else{
        return "error";
    }
}

bool  DFRobot_SIM7000::close(void)
{
    if(getCommandCounter() > 3){
        if(check_send_cmd("AT+CIPSHUT\r\n","OK")){
            setCommandCounter(4);
            return true;
        }else{
            setCommandCounter(4);
            return false;
        }
    }else{
        return false;
    }
}

int   DFRobot_SIM7000::batteryPower(void)
{
    char  batteryBuff[26];
    char *pBattery;
    int i=0,j=0,k=0;
    cleanBuffer(batteryBuff,26);
    send_cmd("AT+CBC\r\n");
    readBuffer(batteryBuff,26);
    pBattery = strstr(batteryBuff,"+CBC:");
    i = *(pBattery + 8) - 48;
    j = *(pBattery + 9) - 48;
    k = (i * 10) + j;
    return  k;
}