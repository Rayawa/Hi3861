#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_watchdog.h"
#include "wifiiot_pwm.h"
#include "hi_pwm.h"


#define NOTE_6 1
#define NOTE_7 2
#define NOTE_1 3
#define NOTE_2 4
#define NOTE_3 5
#define NOTE_S4 6
#define NOTE_5 7
#define NOTE_L5 8
#define NOTE_H6 9
#define NOTE_STOP 0

static const uint16_t g_tuneFreqs[] = {
    0,      // 0: 停顿
    36364,  // 1: 中音 6 (A4)
    32389,  // 2: 中音 7 (B4)
    30593,  // 3: 中音 1 (C5)
    27257,  // 4: 中音 2 (D5)
    24279,  // 5: 中音 3 (E5)
    21622,  // 6: 中音 #4 (F#5)
    20408,  // 7: 中音 5 (G5)
    40816,  // 8: 低音 5 (G4)
    18182   // 9: 高音 6 (A5) -> 36364 / 2 得到
};


static const uint8_t g_scoreNotes[] = {
    NOTE_6, NOTE_3, NOTE_3, NOTE_3, NOTE_3, NOTE_2,
    NOTE_1, NOTE_2, NOTE_1, NOTE_7, NOTE_6,
    
    NOTE_H6, NOTE_H6, NOTE_H6, NOTE_H6, NOTE_H6, NOTE_5,
    NOTE_3, NOTE_5, NOTE_5, NOTE_S4, NOTE_3,
    
    NOTE_3, NOTE_H6, NOTE_H6, NOTE_5, NOTE_3, NOTE_2,
    NOTE_1, NOTE_2, NOTE_1, NOTE_7, NOTE_6, NOTE_3,

    NOTE_3, NOTE_1, NOTE_1, NOTE_7, NOTE_6, NOTE_3,
    NOTE_2, NOTE_1, NOTE_7, NOTE_L5, NOTE_6
};

static const uint8_t g_scoreDurations[] = {
    2, 2, 2, 2, 6, 2,       // 我从南极来
    3, 1, 2, 2, 8,          // 最喜欢赤石
    2, 2, 2, 2, 6, 2,       // 灵感菇刮擦
    2, 2, 2, 2, 8,          // 咕咕又嘎嘎
    2, 2, 2, 2, 6, 2,       // 组了个乐队
    2, 2, 2, 2, 4, 4,       // 拳都不诗人
    2, 2, 2, 2, 6, 2,       // 想成为人类
    3, 1, 2, 2, 8           // 神人把我黑
};

static void *BeeperMusicTask(const char *arg)
{
    (void)arg;
    hi_pwm_set_clock(PWM_CLK_XTAL); 

    while (1) {
        for (size_t i = 0; i < sizeof(g_scoreNotes); i++) {
            uint16_t freqDivisor = g_tuneFreqs[g_scoreNotes[i]];
            uint32_t tuneInterval = g_scoreDurations[i] * 125000; 

            if (freqDivisor > 0) {
                PwmStart(WIFI_IOT_PWM_PORT_PWM0, freqDivisor / 2, freqDivisor);
            }
            
            usleep(tuneInterval);
            PwmStop(WIFI_IOT_PWM_PORT_PWM0);
            usleep(30000);
        }
        sleep(2);
    }
    return NULL;
}

static void StartBeepMusicTask(void)
{
    printf("\n\n#######################\n");
    printf("MUSIC TASK STARTING!!!\n");
    printf("#######################\n\n");
    osThreadAttr_t attr;
    GpioInit();
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_9, WIFI_IOT_IO_FUNC_GPIO_9_PWM0_OUT);
    PwmInit(WIFI_IOT_PWM_PORT_PWM0);
    WatchDogDisable();

    attr.name = "BeeperMusicTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 1024;
    attr.priority = osPriorityNormal;
    if (osThreadNew((osThreadFunc_t)BeeperMusicTask, NULL, &attr) == NULL)
    {
        printf("[LedExample] Falied to create BeeperMusicTask!\n");
    }
        printf("\n\n#######################\n");
    printf("MUSIC TASK END!!!\n");
    printf("#######################\n\n");
}
SYS_RUN(StartBeepMusicTask);
