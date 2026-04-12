#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_adc.h"
#define PHOTO_SENSOR_CHAN_NAME WIFI_IOT_ADC_CHANNEL_4
unsigned short data = 0;
static void PhotoSensorTask(void *arg)
{
    (void)arg;

    while (1)
    {
        AdcRead(PHOTO_SENSOR_CHAN_NAME, &data, WIFI_IOT_ADC_EQU_MODEL_4, WIFI_IOT_ADC_CUR_BAIS_DEFAULT, 0);
        printf("adc:%d\n", data);
        sleep(1);
    }
}
static void PhotoSensorDemo(void)
{
    osThreadAttr_t attr;
    attr.name = "PhotoSensorTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 4096;
    attr.priority = osPriorityNormal;

    if (osThreadNew(PhotoSensorTask, NULL, &attr) == NULL)
    {
        printf("[PhotoSensorDemo] Falied to create PhotoSensorTask!\n");
    }
}

APP_FEATURE_INIT(PhotoSensorDemo);
