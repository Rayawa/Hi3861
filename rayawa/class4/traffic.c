#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"

#define LED_RED    WIFI_IOT_IO_NAME_GPIO_10
#define LED_GREEN  WIFI_IOT_IO_NAME_GPIO_11
#define LED_YELLOW WIFI_IOT_IO_NAME_GPIO_12

void init(void) {
    GpioInit();
    IoSetFunc(LED_RED, WIFI_IOT_IO_FUNC_GPIO_10_GPIO);
    GpioSetDir(LED_RED, WIFI_IOT_GPIO_DIR_OUT);
    IoSetFunc(LED_GREEN, WIFI_IOT_IO_FUNC_GPIO_11_GPIO);
    GpioSetDir(LED_GREEN, WIFI_IOT_GPIO_DIR_OUT);
    IoSetFunc(LED_YELLOW, WIFI_IOT_IO_FUNC_GPIO_12_GPIO);
    GpioSetDir(LED_YELLOW, WIFI_IOT_GPIO_DIR_OUT);
}

// 辅助函数：快速切换灯光状态
void set_leds(int red, int green, int yellow) {
    GpioSetOutputVal(LED_RED, red);
    GpioSetOutputVal(LED_GREEN, green);
    GpioSetOutputVal(LED_YELLOW, yellow);
}

static void traffic_task(void) {
    init();
    printf("\n--- Optimized Traffic Logic Started ---\n");

    while (1) {
        for (int i = 0; i < 3; i++) {
            set_leds(1, 0, 0); usleep(300000);
            set_leds(0, 0, 1); usleep(300000);
            set_leds(0, 1, 0); usleep(300000);
            set_leds(0, 0, 1); usleep(300000); 
        }

        for (int j = 0; j < 3; j++) {
            set_leds(1, 1, 1); usleep(200000);
            set_leds(0, 0, 0); usleep(200000);
        }

        usleep(500000);
    }
}

SYS_RUN(traffic_task);