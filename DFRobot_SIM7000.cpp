#include <DFRobot_SIM7000.h>

bool DFRobot_SIM7000::setBaudRate(long rate)
{
    SIMcore.baudrate = 115200;
    int  count = 0;
    while(count <3){
        if( rate  ==  1200){
            if(SIMcore.check_send_cmd("AT+IPR=1200\r\n","OK")){
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 2400){
            if(SIMcore.check_send_cmd("AT+IPR=2400\r\n","OK")){
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 4800){
            if(SIMcore.check_send_cmd("AT+IPR=4800\r\n","OK")){
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 9600){
            if(SIMcore.check_send_cmd("AT+IPR=9600\r\n","OK")){
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 19200){
            if(SIMcore.check_send_cmd("AT+IPR=19200\r\n","OK")){
                break;
            }else{
                count++;
                delay(200);
            }
        }else if(rate == 38400){
            if(SIMcore.check_send_cmd("AT+IPR=38400\r\n","OK")){
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
    if(count == 3){
        SIMcore.closeCommand();
        return false;
    }
    SIMcore.baudrate = rate;
    SIMcore.setCommandCounter(1);
    return true;
}

bool DFRobot_SIM7000::checkSIMStatus(void)
{
    if(SIMcore.getCommandCounter() == 1){
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
            SIMcore.closeCommand();
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
            SIMcore.closeCommand();
            return false;
        }
        SIMcore.setCommandCounter(2);
        return true;
    }else{
        SIMcore.closeCommand();
        return false;
    }
}

bool DFRobot_SIM7000::setNet(Net net)
{
    if(SIMcore.getCommandCounter() == 2){
        if(net == NB){
            if(SIMcore.check_send_cmd("AT+CNMP=38\r\n","OK")){
                delay(300);
                if(SIMcore.check_send_cmd("AT+CMNB=2\r\n","OK")){
					SIMcore.setCommandCounter(3);
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else if(net == GPRS){
            if(SIMcore.check_send_cmd("AT+CNVW=0,10,\"0D00\"\r\n","OK")){
				SIMcore.setCommandCounter(3);
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

bool DFRobot_SIM7000::attacthService(void)
{
    if(SIMcore.getCommandCounter() == 3){
		char i;
		char *s;
		char gprsBuffer[32];
		SIMcore.cleanBuffer(gprsBuffer,32);
		SIMcore.send_cmd("AT+CGATT=1\r\n");
		while(1){
			SIMcore.readBuffer(gprsBuffer, 32, DEFAULT_TIMEOUT);
			if(NULL != strstr(gprsBuffer, "OK")){
				delay(100);
				break;
			}
			if(NULL != strstr(gprsBuffer, "ERROR")){
				return false;
			}
		}
		SIMcore.cleanBuffer(gprsBuffer,32);
		if(SIMcore.check_send_cmd("AT+CSTT\r\n","OK")){
			delay(100);
		}else{
			return false;
		}
		SIMcore.send_cmd("AT+CIICR\r\n");
		while(1){
			SIMcore.readBuffer(gprsBuffer, 32);
			if(NULL != strstr(gprsBuffer, "OK")){
				delay(200);
				break;
			}else if(NULL != strstr(gprsBuffer,"ERROR")){
				return false;
			}
		}
		if(SIMcore.check_send_cmd("AT+CIFSR\r\n","ERROR")){
			return false;
		}
		SIMcore.setCommandCounter(4);
		return true;
	}else{
		return false;
	}
}

int    DFRobot_SIM7000::checkSignalQuality(void)
{
	if(SIMcore.getCommandCounter() > 1){
		char  signalBuffer[26];
		int i = 0,j = 0,k = 0;
		char *signalQuality;
		SIMcore.cleanBuffer(signalBuffer,26);
		SIMcore.send_cmd("AT+CSQ\r\n");
		SIMcore.readBuffer(signalBuffer,26);
		if (NULL != (signalQuality = strstr(signalBuffer, "+CSQ:"))){
			i = *(signalQuality + 6) - 48;
			j = *(signalQuality + 7) - 48;
			k = (i * 10) + j;
		}else{
			SIMcore.closeCommand();
			return 0;
		}
		if( k == 99){
			SIMcore.closeCommand();
			return 0;
		}else{
			return k;
		}
	}else{
		return 0;
	}
}

bool DFRobot_SIM7000::connect(Protocol ptl,const char *host, int port)
{
	if(SIMcore.getCommandCounter() > 3){
		char num[4];
		char resp[96];
		if(ptl == TCP){
			SIMcore.send_cmd("AT+CIPSTART=\"TCP\",\"");
			SIMcore.send_cmd(host);
			SIMcore.send_cmd("\",");
			itoa(port, num, 10);
			SIMcore.send_cmd(num);
			SIMcore.send_cmd("\r\n");
		}else if(ptl == UDP){
			SIMcore.send_cmd("AT+CIPSTART=\"UDP\",\"");
			SIMcore.send_cmd(host);
			SIMcore.send_cmd("\",");
			itoa(port, num, 10);
			SIMcore.send_cmd(num);
			SIMcore.send_cmd("\r\n");
		}else{
			Serial.println("No such mode!");
			return false;
		}
		while(1){
			while(SIMcore.checkReadable()){
				SIMcore.readBuffer(resp, 96);
				if(NULL != strstr(resp,"CONNECT OK")){
					SIMcore.setCommandCounter(9);
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

bool DFRobot_SIM7000::turnON(void)
{
    delay(300);
    char gprsBuffer[32];
    SIMcore.cleanBuffer(gprsBuffer,32);
    SIMcore.baudrate = 115200;
    SIMcore.setRate(SIMcore.baudrate);
    pinMode(12,OUTPUT);
    while(1){
        digitalWrite(12, HIGH);
        delay(2000);
        digitalWrite(12, LOW);
        while(SIMcore.checkReadable()){
            SIMcore.readBuffer(gprsBuffer,32,DEFAULT_TIMEOUT);
            if((NULL != strstr(gprsBuffer,"1"))){
                return true;
            }
            if((NULL != strstr(gprsBuffer,"+"))){
                return true;
            }
        }
    }
}

bool DFRobot_SIM7000::initPos(void)
{
    if(SIMcore.check_send_cmd("AT+CGNSPWR=1\r\n","OK")){
        delay(50);
        SIMcore.setCommandCounter(3);
        return true;
    }else{
        return false;
    }

}

bool   DFRobot_SIM7000::send(char *data){
    if(SIMcore.getCommandCounter() == 9){
        char num[4];
        char resp[20];
        int len = strlen(data);
        itoa(len, num, 10);
        SIMcore.send_cmd("AT+CIPSEND=");
        SIMcore.send_cmd(num);
        if(SIMcore.check_send_cmd("\r\n",">")){
            SIMcore.send_cmd(data);
            while(1){
                while(SIMcore.checkReadable()){
                    SIMcore.readBuffer(resp,20);
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

bool   DFRobot_SIM7000::send(void *buffer,size_t len)
{
    if(SIMcore.getCommandCounter() == 9){
        char num[4];
        itoa(len, num, 10);
        SIMcore.send_cmd("AT+CIPSEND=");
        SIMcore.send_cmd(num);
        if(SIMcore.check_send_cmd("\r\n",">")){
            if(SIMcore.check_send_cmd(buffer,"OK")){
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

int DFRobot_SIM7000::recv(char* buf,int maxlen,int timeout)
{
    char gprsBuffer[maxlen];
    SIMcore.cleanBuffer(gprsBuffer,maxlen);
    int i=SIMcore.readBuffer(gprsBuffer,maxlen, timeout);
    memcpy(buf,gprsBuffer,i);
    return i;
}

bool DFRobot_SIM7000::getPosition(void)
{
    char  posBuffer[50];
    char *pLongitude,*pLatitude;
    SIMcore.cleanBuffer(posBuffer,50);
    if(SIMcore.getCommandCounter() == 3){
        SIMcore.send_cmd("AT+CGNSINF\r\n");
        SIMcore.readBuffer(posBuffer,50);
        if(NULL != strstr(posBuffer,"+CGNSINF")){
            SIMcore.setCommandCounter(4);
        }else{
            return false;
        }
    }else{
        return false;
    }
    if(SIMcore.getCommandCounter() == 4){
        
        SIMcore.setCommandCounter(5);
        return true;
    }else{
        return false;
    }
}

char* DFRobot_SIM7000::getLatitude(void)
{
    if(SIMcore.getCommandCounter() == 5){
        
    }else{
        return "error";
    }
}

char* DFRobot_SIM7000::getLongitude(void)
{
    if(SIMcore.getCommandCounter() == 5){
        
    }else{
        return "error";
    }
}

bool   DFRobot_SIM7000::close(void)
{
    if(SIMcore.getCommandCounter() > 3){
        if(SIMcore.check_send_cmd("AT+CIPSHUT\r\n","OK")){
            SIMcore.setCommandCounter(4);
            return true;
        }else{
            SIMcore.setCommandCounter(4);
            return false;
        }
    }else{
        return false;
    }
}