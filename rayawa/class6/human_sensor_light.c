#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"

#define LED_R WIFI_IOT_IO_NAME_GPIO_10
#define LED_G WIFI_IOT_IO_NAME_GPIO_11
#define LED_B WIFI_IOT_IO_NAME_GPIO_12
#define SENSOR_GPIO WIFI_IOT_IO_NAME_GPIO_7

void init(void)
{
    GpioInit();
    IoSetFunc(LED_R, WIFI_IOT_IO_FUNC_GPIO_10_GPIO);
    GpioSetDir(LED_R, WIFI_IOT_GPIO_DIR_OUT);
    IoSetFunc(LED_G, WIFI_IOT_IO_FUNC_GPIO_11_GPIO);
    GpioSetDir(LED_G, WIFI_IOT_GPIO_DIR_OUT);
    IoSetFunc(LED_B, WIFI_IOT_IO_FUNC_GPIO_12_GPIO);
    GpioSetDir(LED_B, WIFI_IOT_GPIO_DIR_OUT);

    IoSetFunc(SENSOR_GPIO, WIFI_IOT_IO_FUNC_GPIO_7_GPIO);
    GpioSetDir(SENSOR_GPIO, WIFI_IOT_GPIO_DIR_IN);
    IoSetPull(SENSOR_GPIO, WIFI_IOT_IO_PULL_UP);
}

void RainbowSoftPwm(int r_duty, int g_duty, int b_duty)
{
    int total_us = 5000;
    GpioSetOutputVal(LED_R, 1);
    GpioSetOutputVal(LED_G, 1);
    GpioSetOutputVal(LED_B, 1);
    usleep(r_duty * 50);
    GpioSetOutputVal(LED_R, 0);
    usleep(g_duty * 1);
    GpioSetOutputVal(LED_G, 0);
    usleep(b_duty * 1);
    GpioSetOutputVal(LED_B, 0);
    usleep(total_us); 
}

static void HummanSensorLightTask(void *arg)
{
    (void)arg;
    init();

    int phase = 0; 
    WifiIotGpioValue rel = 0;

    while (1) {
        GpioGetInputVal(SENSOR_GPIO, &rel);

        if (rel == WIFI_IOT_GPIO_VALUE1) {
            int r = (phase < 100) ? phase : (phase < 200 ? 200 - phase : 0);
            int g = (phase > 66 && phase < 166) ? (phase - 66) : (phase >= 166 && phase < 266 ? 266 - phase : 0);
            int b = (phase > 133) ? (phase - 133) : 0;

            RainbowSoftPwm(r, g, b);

            phase = (phase + 1) % 300;
            usleep(5000); 
        } else {
            GpioSetOutputVal(LED_R, 0);
            GpioSetOutputVal(LED_G, 0);
            GpioSetOutputVal(LED_B, 0);
            phase = 0;
            osDelay(20);
        }
    }
}

static void HummanSensorLightDemo(void)
{
    osThreadAttr_t attr = {0};
    attr.name = "HummanSensorLightTask";
    attr.stack_size = 4096;
    attr.priority = osPriorityNormal;

    if (osThreadNew(HummanSensorLightTask, NULL, &attr) == NULL) {
        printf("Failed to create task\n");
    }
}

APP_FEATURE_INIT(HummanSensorLightDemo);