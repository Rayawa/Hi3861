#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_adc.h"
#include "wifiiot_errno.h"
#define HUMAN_SENSOR_CHAN_NAME WIFI_IOT_ADC_CHANNEL_3

unsigned short data = 0;

static void HummanSensorTask(void *arg)
{
    (void)arg;
    printf("[Debug] Enter HummanSensorTask Loop\n");

    while (1)
    {
        unsigned int ret = AdcRead(HUMAN_SENSOR_CHAN_NAME, &data, WIFI_IOT_ADC_EQU_MODEL_4, WIFI_IOT_ADC_CUR_BAIS_DEFAULT, 0);
    
        if (ret == WIFI_IOT_SUCCESS) {
            printf("adc value: %d\n", data);
        } else {
            printf("[Error] AdcRead Failed! Error Code: 0x%x\n", ret);
        }
 
        osDelay(100); 
    }
}

static void HummanSensorDemo(void)
{
    printf("[Debug] HummanSensorDemo Initializing...\n");

    osThreadAttr_t attr;
    attr.name = "HummanSensorTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 4096;
    attr.priority = osPriorityNormal;

    if (osThreadNew(HummanSensorTask, NULL, &attr) == NULL)
    {
        printf("[Error] Failed to create HummanSensorTask!\n");
    } else {
        printf("[Debug] HummanSensorTask Created Successfully!\n");
    }
}

APP_FEATURE_INIT(HummanSensorDemo);