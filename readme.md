## 嵌入式课设功能介绍
> 山东科技大学电子信息科学与技术2021级ARM原理与设计课程设计
#### 1. 项目简介
本项目是一个基于**STM32F103ZET6**嵌入式控制系统。STM32使用**FreeRTOS**嵌入式实时操作系统开发，**RK3268 Linux嵌入式开发板**用于**Web服务器**的部署。主要功能是模拟一个智能家居的控制系统。具有***灯光控制、风扇控制、门禁系统、报警系统、防火防盗系统、空气质量检测系统、语音控制、网络远程控制***等功能。

#### 2. 家内设施
1. **灯光系统**使用PCB上焊接的3个**LED灯**模拟，可调节灯光亮度
2. **风扇系统**使用**TB6612电机驱动**模块驱动扇叶转动，可调节风扇转速
3. **门禁系统**通过驱动舵机模拟门的开关，**OpenMV**模拟门禁摄像头，用于**识别人脸**开锁，**矩阵键盘**和**OLED显示屏**模拟**门禁密码**输入和显示
4. **报警系统**使用**蜂鸣器**及**蓝牙模块**传送报警信息
5. 传感器组：
    - **红外对射传感器**用于检测家中人数
    - **光敏电阻**用于检测光照强度
    - **空气质量传感器**用于检测空气质量（温湿度、二氧化碳、PM2.5、PM10、甲醛、TVOC共**七**个指标）
    - 一氧化碳传感器和动作传感器用于**防火防盗**系统

6. LVDS接口 **TFT LCD**显示屏用于显示家中传感器及设施状态。
显示内容包括：**空气质量**、**家中人数**、**灯光亮度**、**风扇转速**、**防火防盗警报状态**、**门禁系统状态**、RTC实时时钟显示**当前时间**。此外，可通过**触摸控制**屏幕上的按钮实现对家中设施的控制。

#### 3. 控制方式
1. **语音控制**：使用天问五幺语音**离线语音识别芯片**实现**语音播报**和**语音识别**，通过**串口**与**STM32**通信以实现对家中设施的控制。
2. **网络远程控制**：网页部署在RK3568，STM32使用串口与RK3568通信，传输控制指令及家中传感器及设施状态，通过**网页**实现对家中设施的控制，同时显示家中传感器及设施状态。
    - 网页前端技术栈：**Bootstrap**、**jQuery**、**Vue**
    - 网页后端技术栈：**Flask**
    - Web服务器：**Nginx**

