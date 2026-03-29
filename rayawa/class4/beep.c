#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_pwm.h"
#include "hi_pwm.h"

void init(void)
{
    GpioInit();

    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_9, WIFI_IOT_IO_FUNC_GPIO_9_PWM0_OUT);
    PwmInit(WIFI_IOT_PWM_PORT_PWM0);
}
void beep(void)
{
    init();

    uint32_t dot = 200000;
    uint32_t dash = 600000;
    uint32_t interval = 200000;
    uint32_t letterGap = 600000;
    uint32_t loopGap = 2000000;

    uint16_t freqDivisor = 34052;

    while (1)
    {
        for (int i = 0; i < 3; i++) {
            PwmStart(WIFI_IOT_PWM_PORT_PWM0, freqDivisor / 2, freqDivisor);
            usleep(dot);
            PwmStop(WIFI_IOT_PWM_PORT_PWM0);
            usleep(interval);
        }

        usleep(letterGap);

        for (int i = 0; i < 3; i++) {
            PwmStart(WIFI_IOT_PWM_PORT_PWM0, freqDivisor / 2, freqDivisor);
            usleep(dash);
            PwmStop(WIFI_IOT_PWM_PORT_PWM0);
            usleep(interval);
        }

        usleep(letterGap);

        for (int i = 0; i < 3; i++) {
            PwmStart(WIFI_IOT_PWM_PORT_PWM0, freqDivisor / 2, freqDivisor);
            usleep(dot);
            PwmStop(WIFI_IOT_PWM_PORT_PWM0);
            usleep(interval);
        }

        usleep(loopGap);
    }
}

SYS_RUN(beep);
