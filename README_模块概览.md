# Hi3861 OpenHarmony 四大开发模块

## 🎯 模块概览

### **模块一：红绿灯板开发** 🚦
**硬件**：三色LED（GPIO_10/11/12） + S3按钮（GPIO_8）
**项目**：
1. `light.c` - 基础灯控制
2. `traffic.c` - 交通灯系统（自动时序）
3. `ability.c` - 多线程并发
4. `button.c` - S3按钮开发
5. `control.c` - **按钮控制红绿灯**（综合项目）

### **模块二：炫彩灯板开发** 🎨
**硬件**：三色LED（PWM1/2/3） + 蜂鸣器（PWM0） + 人体传感器 + 光敏电阻
**项目**：
1. `beep.c` - 蜂鸣器控制
2. `music.c` - 音乐播放
3. `led.c` - **音乐可视化**（核心项目）
4. `human_sensor.c` - 人体红外传感器
5. `photosensitive.c` - 光敏电阻
6. `human_sensor_light.c` - **夜晚人体感应灯**（综合项目）

### **模块三：环境监测板开发** 🌡️
**硬件**：MQ-2燃气传感器 + AHT20温湿度 + OLED显示屏 + 蜂鸣器
**项目**：
1. `mq2_demo.c` - 燃气浓度检测
2. `aht20.c/.h` - 温湿度传感器驱动
3. `oled_ssd1306.c/.h` - OLED显示驱动
4. `oled_demo.c` - OLED显示演示
5. `enrionment_demo.c` - **综合环境监测系统**（核心项目）

### **模块四：AT指令开发** 📡
**项目**：
- `cal.c` - **自定义AT+CALC指令**（四则运算计算器）

## 🛠️ 快速使用

### 编译配置
```gn
# rayawa/BUILD.gn - 激活模块
features = [
    "traffic_light:traffic_light",    # 激活红绿灯模块
    # 注释其他模块
]

# traffic_light/BUILD.gn - 激活文件
sources = [
    "control.c",  # 激活综合项目
    # 注释其他文件
]
```

### 开发流程
1. **选择模块** → 编辑 `rayawa/BUILD.gn`
2. **选择文件** → 编辑模块 `BUILD.gn`
3. **编译** → `hb build`
4. **烧录** → HiBurn工具
5. **测试** → 串口终端（115200）

## 📚 学习路径

### 基础入门
1. **hello模块** → 程序结构
2. **traffic_light/light.c** → GPIO控制
3. **colorful_light/beep.c** → PWM控制

### 进阶开发
1. **traffic_light/control.c** → 综合控制系统
2. **colorful_light/led.c** → 音乐可视化
3. **environment/enrionment_demo.c** → 多传感器融合

### 高级应用
1. **at_command/cal.c** → AT指令开发
2. 自定义传感器驱动
3. 复杂系统设计

## 🔧 技术要点

### 硬件接口
- **GPIO**：LED、按钮
- **PWM**：蜂鸣器、LED调光
- **I2C**：AHT20、OLED
- **ADC**：MQ-2、人体传感器、光敏电阻

### 软件框架
- **CMSIS-RTOS2**：多任务调度
- **HiAT Framework**：AT指令处理
- **OpenHarmony Driver**：硬件驱动

## 🚀 开始开发

```bash
# 1. 激活模块和文件
# 2. 编译：hb build
# 3. 烧录：HiBurn
# 4. 测试：串口终端
```

**每个模块都有详细注释，适合嵌入式开发学习！**