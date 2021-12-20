
# DFRobot_SIM7000 
* [English Version](./README.md)

SIM7000是首个LTE CAT-M1 / NB-IoT模块，支持LTE- tdd / LTE- fdd / GSM / GPRS / EDGE多频段
这个上传和下载数据流量峰值375kbps，它是一个稳定的低功耗通信模块。NB-IoT的覆盖增益为20dB +，所以
即使在类似的地下室，它也有无线通信能力。

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0505/DFR0505svg1.png)

## 产品链接(https://www.dfrobot.com.cn/goods-1645.html)

    SKU:DFR0505-CN

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概述

这个库提供SIM7000的一些应用依赖:
用GPRS模式或NB-IOT模式通过UDP或TCP发送和接收数据
通过GNSS定位当前位置, 这个功能需要在户外使用
我们还提供了一种直接向SIM7000发送AT命令的方法

## 库安装

在运行此库的demo之前，你需要下载关联库:  https://github.com/DFRobot/DFRobot_SIM
使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```C++
  /**
   * @fn DFRobot_SIM7000
   * @brief DFRobot_SIMcore 抽象类的构造函数。构建串行端口。
   * @param s 抽象类的类指针对象，这里可以填入串口对象的指针。
   * @return None
   */
  DFRobot_SIM7000(Stream *s);
  ~DFRobot_SIM7000(){};

  /**
   * @fn recv
   * @brief 接收数据
   * @param buf 接收数据内容
   * @param maxlen 接收数据长度
   * @return int 获取数据长度
   */
  int recv(char* buf, int maxlen);

  /**
   * @fn checkSignalQuality
   * @brief 检查信号质量
   * @return 0-30:信号质量
   */
  int checkSignalQuality(void);

  /**
   * @fn batteryPower
   * @brief 充电等级
   * @return int 充电等级
   */
  int batteryPower(void);

  /**
   * @fn setNetMode
   * @brief 设置网络模式
   * @param net 网络模式
   * @n    GPRS: GPRS 模式
   * @n    NB:   NB-IOT 模式
   * @return bool类型，表示设置状态
   * @retval ture Success 
   * @retval false Failed
   */
  bool setNetMode(eNet net);

  /**
   * @fn attacthService
   * @brief 打开连接
   * @return bool类型，表示打开连接状态
   * @retval true Success 
   * @retval false Failed
   */
  bool attacthService(void);

  /**
   * @fn setBaudRate
   * @brief 修改波特率避免出错
   * @param rate 波特率值
   * @n    可选值:1200 2400 4800 9600 19200 38400
   * @note SIM7000默认波特率为115200，请降低波特率，避免失真
   * @return bool类型，表示设置状态
   * @retval true Success 
   * @retval false Failed
   */
  bool setBaudRate(long rate);

  /**
   * @fn checkSIMStatus
   * @brief 检测SIM卡
   * @return bool类型，表示检测卡状态
   * @retval true 有卡 
   * @retval false 无卡
   */
  bool checkSIMStatus(void);

  /**
   * @fn openNetwork
   * @brief 开始连接
   * @param ptl  选择连接协议
   * @n    TCP  选择 TCP
   * @n    UDP  选择 UDP
   * @param host 主机域名
   * @param port  端口号
   * @return bool类型，表示打开状态
   * @retval true Success 
   * @retval false Failed
   */
  bool openNetwork(eProtocol ptl, const char *host, int port);

  /**
   * @fn closeNetwork
   * @brief 结束连接
   * @return bool类型，表示关闭状态
   * @retval true Success 
   * @retval false Failed
   */
  bool closeNetwork(void);

  /**
   * @fn turnON
   * @brief 打开SIM7000
   * @return bool类型，表示开机状态
   * @retval true Success 
   * @retval false Failed
   */
  bool turnON(void);
  
  /**
   * @fn initPos
   * @brief 初始化 SIM7000 定位模式
   * @return bool类型，表示初始化状态
   * @retval true Success 
   * @retval false Failed
   */
  bool initPos(void);

  /** 
   * @fn mqttConnect
   * @brief MQTT 连接请求
   * @param iot_client 用户定义客户端名称
   * @param iot_username 用户名标识正在连接的用户的名称
   * @param iot_key 用户密码
   * @return bool类型，表示连接状态
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttConnect(char* iot_client, char* iot_username, char* iot_key);

  /**
   * @fn mqttPublish
   * @brief MQTT 发送命令
   * @param iot_topic 目标标题
   * @param iot_data  你想要发送的数据
   * @return bool类型，表示发送状态
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttPublish(char* iot_topic, String iot_data);

  /**
   * @fn mqttSubscribe
   * @brief 订阅MQTT频道
   * @param iot_topic 订阅的MQTT密钥 
   * @return bool类型，表示订阅状态
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttSubscribe(char* iot_topic);

  /**
   * @fn mqttUnsubscribe
   * @brief 取消订阅MQTT频道
   * @param iot_topic 取消订阅的MQTT密钥
   * @return bool类型，表示取消订阅状态
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttUnsubscribe(char* iot_topic);

  /**
   * @fn mqttRecv
   * @brief MQTT发送数据
   * @param iot_topic 订阅频道密钥
   * @param buf 发送数据
   * @param maxlen 发送数据长度
   * @return bool类型，表示订阅状态
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttRecv(char* iot_topic, char* buf,int maxlen);

  /**
   * @fn mqttDisconnect
   * @brief MQTT断开连接
   * @return bool类型，表示断开连接状态
   * @retval true Success 
   * @retval false Failed
   */
  bool mqttDisconnect(void);

  /**
   * @fn httpInit
   * @brief 初始化 HTTP 服务
   * @param net 网络模式
   * @n    eGPRS: GPRS 模式
   * @n    eNB:   NB-IOT 模式
   * @return bool类型，表示初始化状态
   * @retval true Success 
   * @retval false Failed
   */
  bool httpInit(eNet net);

  /**
   * @fn httpConnect
   * @brief 配置服务
   * @param Host 服务器IP
   * @return bool类型，表示连接状态
   * @retval true Success 
   * @retval false Failed
   */
  bool httpConnect(const char *Host);

  /**
   * @fn httpPost
   * @brief HTTP POST
   * @param Host 网址
   * @param data POST 数据
   * @return bool类型，表示请求状态
   * @retval true Success 
   * @retval false Failed
   */
  bool httpPost(const char *Host , String data);

  /**
   * @fn httpGet
   * @brief HTTP GET 这个函数用来打印get数据
   * @param Host URL
   */
  void httpGet(const char *Host);

  /**
   * @fn httpDisconnect
   * @brief 断开与服务器的连接并取消初始化
   */
  void httpDisconnect(void);

  /**
   * @fn send
   * @brief 发送指定长度的数据
   * @param buf 存储数据的buffer
   * @param len 发送数据的长度
   * @return bool类型，表示发送状态
   * @retval true Success 
   * @retval false Failed
   */
  bool send(void *buffer,size_t len);

  /**
   * @fn send
   * @brief 发送数据
   * @param data 发送的数据
   * @return bool类型，表示发送状态
   * @retval true Success 
   * @retval false Failed
   */
  bool send(char *data);

  /**
   * @fn getPosition
   * @brief 获取当前位置
   * @return bool类型，表示发送状态
   * @retval true Success 
   * @retval false Failed
   */
  bool getPosition(void);

  /**
   * @fn getLatitude
   * @brief 获取纬度
   * @return 纬度数据
   */
  char* getLatitude(void);

  /**
   * @fn getLongitude
   * @brief 获取经度
   * @return 经度数据
   */
  char* getLongitude(void);
```

## 兼容性

主板               | 通过  | 未通过   | 未测试   | 备注
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno  |      √       |             |            | 
Leonardo  |      √       |             |            | 
Meag2560 |         √    |              |            | 

如果你使用Mega请配置PIN8 PIN9
## 历史

- 2017/8/30 - 1.0.0 版本
- 2021/09/16 - 1.0.1 版本

## 创作者

- Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
