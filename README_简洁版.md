# Hi3861 OpenHarmony 嵌入式开发仓库

基于华为海思 Hi3861 开发板的 OpenHarmony 嵌入式开发实践项目，重点包含 Class 4-7 的核心学习内容。

## 🎯 Class 4-7 核心内容概览

### **Class 4: 智慧交通与智慧家居系统** 🚦🏠
**智慧交通系统**：
- `light.c` - 基础 LED 控制（GPIO_10/11/12）
- `traffic.c` - 交通灯控制系统（红黄绿三色，CMSIS-RTOS2 任务调度）
- `ability.c` - 多线程能力演示
- `button.c` - 按键识别与处理（GPIO 输入，消抖处理）
- `control.c` - 按钮控制交通灯（手动/自动模式切换）

**智慧家居系统**：
- `beep.c` - 蜂鸣器控制（PWM 输出，不同频率）
- `music.c` - 音乐播放系统（预定义旋律）
- `led.c` - **混合音乐 LED 系统**（当前激活，音乐可视化）

### **Class 5: 传感器与显示系统** 🌡️📺
**AHT20 温湿度传感器**：
- `aht20.c/.h` - I2C 通信，高精度测量（±0.3°C，±2%湿度）
- `aht20_demo.c` - 实时数据显示

**OLED 显示系统**：
- `oled_ssd1306.c/.h` - SSD1306 驱动（128x64，I2C/SPI）
- `oled_fonts.h` - 字体库（中英文，自定义图标）
- `oled_demo.c` - 温湿度图表显示

**环境传感器**：
- `mq2_demo.c` - MQ-2 气体检测（烟雾，可燃气体）
- `enrionment_demo.c` - 综合环境监测

### **Class 6: 环境感知系统** 👤☀️
**人体传感器**：
- `human_sensor.c` - 人体红外检测（ADC 通道3）
- `human_sensor_light.c` - 人体感应自动灯光

**光敏传感器**：
- `photosensitive.c` - 环境光检测，自动亮度调节

### **Class 7: AT 命令开发** 🧮
**计算器 AT 命令**：
- `cal.c` - 自定义 `AT+CALC=a,b` 命令
- 功能：四则运算（加、减、乘、除）
- 特性：参数验证，除零保护，实时计算

## 🛠️ 快速使用指南

### 编译配置
每个 class 目录有 `BUILD.gn` 文件，通过注释控制激活文件：

```gn
# Class 4 示例配置（当前激活 led.c）
sources = [
    #"light.c",    # 注释 = 不编译
    "led.c",      # 未注释 = 激活编译
]
```

### 开发流程
1. **选择模块**：进入对应 class 目录
2. **配置编译**：编辑 `BUILD.gn` 激活所需文件
3. **编译**：`hb build`
4. **烧录**：HiBurn 工具
5. **测试**：串口终端（115200 波特率）

## 📚 学习路径

### 基础 → 进阶
1. **Class 4**：GPIO 控制（LED、按键、蜂鸣器）
2. **Class 5**：传感器（I2C 通信，数据显示）
3. **Class 6**：环境感知（ADC 采集）
4. **Class 7**：AT 命令（系统交互）

### 项目实战
- **智慧交通灯**：Class 4 全部文件
- **环境监测站**：Class 5 + Class 6
- **计算器工具**：Class 7 AT 命令

## 🔧 技术要点

### 硬件接口
- **GPIO**：LED、按键、蜂鸣器
- **I2C**：AHT20、OLED 通信
- **ADC**：MQ-2、光敏、人体传感器
- **PWM**：蜂鸣器音调

### 软件框架
- **CMSIS-RTOS2**：多任务调度
- **HiAT Framework**：AT 命令处理
- **OpenHarmony Driver**：硬件驱动

## 🚀 开始开发

```bash
# 1. 进入学习模块
cd rayawa/class4

# 2. 配置编译文件
vi BUILD.gn  # 激活需要的文件

# 3. 编译
hb build

# 4. 烧录测试
# 使用 HiBurn 烧录，串口查看输出
```

---

**每个文件都有详细注释，适合 OpenHarmony Hi3861 嵌入式开发学习！**