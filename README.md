# Hi3861 开源鸿蒙嵌入式开发仓库

基于华为海思 Hi3861 开发板的 OpenHarmony 嵌入式开发实践项目。本仓库包含了从基础 GPIO 控制到高级传感器应用、AT 命令开发的完整学习路径。

## 📁 仓库结构

```
Hi3861/
├── demolink/              # 基础示例
│   └── helloworld.c      # Hello World 示例
├── iothardware/          # IoT 硬件示例
│   └── led_example.c     # LED 控制示例
├── rayawa/               # 核心学习项目（重点）
│   ├── class3/           # 第3课：基础入门
│   │   └── hello.c       # 基础程序
│   ├── class4/           # 第4课：智慧交通与家居（重点）
│   ├── class5/           # 第5课：传感器与显示
│   ├── class6/           #第6课：环境感知
│   └── class7/           # 第7课：AT命令开发
├── samgr/                # 系统服务管理示例
└── startup/              # 启动配置
```

## 🎯 Class 4-7 详细内容（重点）

### **Class 4: 智慧交通与智慧家居系统**

本课程实现了两个完整的嵌入式系统：智慧交通灯控制系统和智慧家居控制系统。

#### **智慧交通系统** 🚦
- **`light.c`** - 基础 LED 控制
  - 控制 GPIO_10、GPIO_11、GPIO_12 三个 LED
  - 实现 LED 的单独控制和组合控制
  - 包含延时控制和状态切换

- **`traffic.c`** - 交通灯控制系统
  - 模拟真实交通灯：红、黄、绿三色灯
  - 实现标准交通灯时序控制
  - 使用 CMSIS-RTOS2 进行任务调度
  - 支持手动模式和自动模式切换

- **`ability.c`** - 多线程能力演示
  - 展示 OpenHarmony 多任务处理能力
  - 实现并行任务执行
  - 任务间通信和同步

- **`button.c`** - 按键识别与处理
  - GPIO 输入检测
  - 按键消抖处理
  - 中断和轮询两种模式
  - 多按键同时检测

- **`control.c`** - 按钮控制交通灯
  - 将按键与交通灯控制结合
  - 实现手动控制交通灯状态
  - 模式切换功能

#### **智慧家居系统** 🏠
- **`beep.c`** - 蜂鸣器控制
  - PWM 输出控制蜂鸣器
  - 实现不同频率的声音
  - 警报音效生成

- **`music.c`** - 音乐播放系统
  - 基于蜂鸣器的简单音乐播放
  - 支持播放预定义旋律
  - 节奏和音调控制

- **`led.c`** - 混合音乐 LED 系统（当前激活）
  - **综合项目**：将音乐播放与 LED 控制结合
  - 实现音乐可视化效果
  - LED 随音乐节奏变化
  - 多模式灯光效果

### **Class 5: 传感器与显示系统**

本课程专注于环境感知和数据显示。

#### **AHT20 温湿度传感器** 🌡️
- **`aht20.c/.h`** - AHT20 传感器驱动
  - I2C 通信协议实现
  - 温湿度数据采集
  - 数据校准和补偿算法
  - 高精度测量（温度 ±0.3°C，湿度 ±2%）

- **`aht20_demo.c`** - 传感器演示程序
  - 实时温湿度显示
  - 数据刷新控制
  - 异常处理

#### **OLED 显示系统** 📺
- **`oled_ssd1306.c/.h`** - SSD1306 OLED 驱动
  - I2C/SPI 双模式支持
  - 128x64 像素显示控制
  - 字体渲染和图形绘制
  - 帧缓冲管理

- **`oled_fonts.h`** - 字体库
  - 多种中英文字体
  - 自定义图标支持
  - 字体缩放功能

- **`oled_demo.c`** - OLED 演示程序
  - 温湿度数据显示
  - 实时图表绘制
  - 多页面切换

#### **环境传感器** 🌫️
- **`mq2_demo.c`** - MQ-2 气体传感器
  - 烟雾和可燃气体检测
  - 浓度阈值报警
  - ADC 数据采集

- **`enrionment_demo.c`** - 综合环境监测
  - 多传感器数据融合
  - 环境质量评估
  - 数据日志记录

### **Class 6: 环境感知系统**

本课程实现人体感知和环境光检测。

#### **人体传感器** 👤
- **`human_sensor.c`** - 人体红外传感器
  - ADC 通道读取（WIFI_IOT_ADC_CHANNEL_3）
  - 运动检测算法
  - 灵敏度调节
  - 连续监测模式

- **`human_sensor_light.c`** - 人体感应灯光控制
  - 检测到人体时自动开灯
  - 延时关闭功能
  - 节能模式

#### **光敏传感器** ☀️
- **`photosensitive.c`** - 光敏电阻应用
  - 环境光强度检测
  - 自动亮度调节
  - 日夜模式切换
  - 阈值自适应

### **Class 7: AT 命令开发**

本课程实现自定义 AT 命令系统。

#### **计算器 AT 命令** 🧮
- **`cal.c`** - 自定义 AT+CALC 命令
  - 命令格式：`AT+CALC=a,b`
  - 支持四则运算：加、减、乘、除
  - 参数验证和错误处理
  - 除零保护机制

#### **功能特性**：
- **实时计算**：输入两个数字，立即返回计算结果
- **完整输出**：同时显示和、差、积、商
- **错误处理**：除零错误提示
- **AT 框架集成**：完全集成到 OpenHarmony AT 框架

## 🛠️ 开发环境配置

### 1. 环境要求
- OpenHarmony 3.0+ 开发环境
- Hi3861 开发板
- HiBurn 烧录工具
- Serial Terminal（如 Putty、MobaXterm）

### 2. 编译说明
每个 class 目录下都有 `BUILD.gn` 文件，配置了编译选项。当前激活的文件在注释中标注。

例如 Class 4 的配置：
```gn
static_library("class4") {
    sources = [
        # 当前激活：混合音乐LED系统
        "led.c",      # 混合音乐led
    ]
    # ... 包含目录配置
}
```

### 3. 烧录步骤
1. 编译项目：`hb build`
2. 连接 Hi3861 开发板
3. 使用 HiBurn 烧录固件
4. 通过串口查看输出

## 📚 学习路径建议

### 初学者路线
1. **Class 3** → 基础 Hello World
2. **Class 4** → GPIO 控制（light.c → traffic.c → control.c）
3. **Class 4** → 智慧家居（beep.c → music.c → led.c）

### 进阶路线
1. **Class 5** → 传感器应用（aht20 → oled）
2. **Class 6** → 环境感知（human_sensor → photosensitive）
3. **Class 7** → AT 命令开发

### 项目实战
1. 智慧交通灯系统（Class 4 全部）
2. 环境监测站（Class 5 + Class 6）
3. 自定义 AT 命令工具（Class 7）

## 🔧 技术栈

### 硬件接口
- **GPIO**：LED、按键、蜂鸣器控制
- **I2C**：AHT20、OLED 通信
- **ADC**：MQ-2、光敏电阻、人体传感器
- **PWM**：蜂鸣器音调控制

### 软件框架
- **OpenHarmony**：基础操作系统
- **CMSIS-RTOS2**：实时任务调度
- **HiAT Framework**：AT 命令处理
- **Driver Framework**：硬件驱动抽象

### 开发工具
- **编译系统**：GN + Ninja
- **调试工具**：串口调试、日志系统
- **烧录工具**：HiBurn
- **测试工具**：AT 命令测试

## 🚀 快速开始

### 1. 克隆仓库
```bash
git clone <repository-url>
cd Hi3861
```

### 2. 选择学习模块
```bash
# 进入 Class 4（智慧交通与家居）
cd rayawa/class4

# 修改 BUILD.gn 激活需要的文件
# 取消注释要编译的文件，注释其他文件
```

### 3. 编译和烧录
```bash
# 在 OpenHarmony 根目录执行
hb build

# 使用 HiBurn 烧录生成的固件
```

### 4. 运行和测试
1. 连接串口终端（波特率 115200）
2. 重启开发板
3. 查看程序输出
4. 交互测试（如按键、AT命令）

## 📖 文档资源

### 官方文档
- [OpenHarmony 官方文档](https://gitee.com/openharmony/docs)
- [Hi3861 数据手册](https://www.hisilicon.com/)
- [CMSIS-RTOS2 参考](https://arm-software.github.io/CMSIS_5/RTOS2/html/index.html)

### 学习资源
- 每个 `.c` 文件都有详细注释
- `BUILD.gn` 文件说明编译配置
- 串口输出包含调试信息

## 🤝 贡献指南

1. Fork 本仓库
2. 创建功能分支：`git checkout -b feature/新功能`
3. 提交更改：`git commit -m '添加新功能'`
4. 推送到分支：`git push origin feature/新功能`
5. 提交 Pull Request

## 📄 许可证

本项目基于 Apache License 2.0 开源协议。

## 📞 联系与支持

- **问题反馈**：在 Issues 中提交问题
- **功能建议**：使用 Feature Request 模板
- **技术讨论**：欢迎提交 Pull Request

---

**开始你的 OpenHarmony Hi3861 嵌入式开发之旅吧！** 🚀

*最后更新：2026年4月12日*