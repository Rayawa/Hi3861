#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"

#define LED_RED    WIFI_IOT_IO_NAME_GPIO_10
#define LED_GREEN  WIFI_IOT_IO_NAME_GPIO_11
#define LED_YELLOW WIFI_IOT_IO_NAME_GPIO_12
#define BUTTON_S3  WIFI_IOT_IO_NAME_GPIO_8

static volatile int g_state = 0; 

static void AllOff(void) {
    GpioSetOutputVal(LED_RED, 0);
    GpioSetOutputVal(LED_GREEN, 0);
    GpioSetOutputVal(LED_YELLOW, 0);
}

static void OnButtonPressed(char *arg) {
    (void)arg;
    if (g_state == 0) g_state = 1;
    else if (g_state == 1) g_state = 2;
}

static void TrafficControlTask(void) {
    GpioInit();
    IoSetFunc(LED_RED, WIFI_IOT_IO_FUNC_GPIO_10_GPIO);
    GpioSetDir(LED_RED, WIFI_IOT_GPIO_DIR_OUT);
    IoSetFunc(LED_GREEN, WIFI_IOT_IO_FUNC_GPIO_11_GPIO);
    GpioSetDir(LED_GREEN, WIFI_IOT_GPIO_DIR_OUT);
    IoSetFunc(LED_YELLOW, WIFI_IOT_IO_FUNC_GPIO_12_GPIO);
    GpioSetDir(LED_YELLOW, WIFI_IOT_GPIO_DIR_OUT);

    IoSetFunc(BUTTON_S3, WIFI_IOT_IO_FUNC_GPIO_8_GPIO);
    GpioSetDir(BUTTON_S3, WIFI_IOT_GPIO_DIR_IN);
    IoSetPull(BUTTON_S3, WIFI_IOT_IO_PULL_UP);
    GpioRegisterIsrFunc(BUTTON_S3, WIFI_IOT_INT_TYPE_EDGE, WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW, OnButtonPressed, NULL);

    while (1) {
        if (g_state == 0) {
            AllOff();
            GpioSetOutputVal(LED_RED, 1);
            usleep(100000);
        } 
        else if (g_state == 1) {
            AllOff();
            GpioSetOutputVal(LED_GREEN, 1);
            usleep(100000);
        } 
        else if (g_state == 2) {
            AllOff();
            for (int i = 0; i < 2; i++) {
                GpioSetOutputVal(LED_YELLOW, 1); usleep(200000);
                GpioSetOutputVal(LED_YELLOW, 0); usleep(200000);
            }
            GpioSetOutputVal(LED_YELLOW, 1);
            sleep(2);
            g_state = 0;
        }
    }
}

static void StartDemo(void) {
    osThreadAttr_t attr = {.name = "TrfTsk", .stack_size = 2048, .priority = osPriorityNormal};
    osThreadNew((osThreadFunc_t)TrafficControlTask, NULL, &attr);
}

SYS_RUN(StartDemo);