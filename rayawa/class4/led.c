#include <stdio.h>
#include <unistd.h>
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "wifiiot_gpio.h"
#include "wifiiot_gpio_ex.h"
#include "wifiiot_watchdog.h"
#include "wifiiot_pwm.h"
#include "hi_pwm.h"

#define BEEPER_PWM_PORT WIFI_IOT_PWM_PORT_PWM0
#define LED_RED_PWM     WIFI_IOT_PWM_PORT_PWM1
#define LED_GREEN_PWM   WIFI_IOT_PWM_PORT_PWM2
#define LED_YELLOW_PWM  WIFI_IOT_PWM_PORT_PWM3

#define PWM_CYCLE       8000 
#define GLOW_BRIGHTNESS 100

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
    0, 36364, 32389, 30593, 27257, 24279, 21622, 20408, 40816, 18182
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
    2, 2, 2, 2, 6, 2,
    3, 1, 2, 2, 8,
    2, 2, 2, 2, 6, 2,
    2, 2, 2, 2, 8,
    2, 2, 2, 2, 6, 2,
    2, 2, 2, 2, 4, 4,
    2, 2, 2, 2, 6, 2,
    3, 1, 2, 2, 8
};

static void SetLedBrightness(WifiIotPwmPort port, uint16_t duty) {
    if (duty == 0) {
        PwmStop(port);
    } else {
        PwmStart(port, duty, PWM_CYCLE);
    }
}

static void AllOff(void) {
    PwmStop(BEEPER_PWM_PORT);
    PwmStop(LED_RED_PWM);
    PwmStop(LED_GREEN_PWM);
    PwmStop(LED_YELLOW_PWM);
}

static void BreathingFadingEffect(WifiIotPwmPort mainLedPort, uint8_t durationTicks) {
    uint32_t totalTimeUs = durationTicks * 125000;
    const uint32_t stepUs = 10000;
    uint32_t steps = totalTimeUs / stepUs;
    
    SetLedBrightness(LED_RED_PWM, GLOW_BRIGHTNESS);
    SetLedBrightness(LED_GREEN_PWM, GLOW_BRIGHTNESS);
    SetLedBrightness(LED_YELLOW_PWM, GLOW_BRIGHTNESS);

    for (uint32_t i = 0; i < steps; i++) {
        uint32_t duty;
        uint32_t midStep = steps / 2;

        if (i < midStep) {
            duty = GLOW_BRIGHTNESS + ((PWM_CYCLE - GLOW_BRIGHTNESS - 1000) * i) / midStep;
        } else {
            duty = (PWM_CYCLE - 1000) - ((PWM_CYCLE - GLOW_BRIGHTNESS - 1000) * (i - midStep)) / (steps - midStep);
        }

        if (durationTicks > 4 && i == midStep) {
            SetLedBrightness(LED_RED_PWM, PWM_CYCLE-1000);
            SetLedBrightness(LED_GREEN_PWM, PWM_CYCLE-1000);
            SetLedBrightness(LED_YELLOW_PWM, PWM_CYCLE-1000);
            usleep(20000);
        }

        SetLedBrightness(mainLedPort, duty);
        usleep(stepUs);
    }
}

static void *MusicLightSyncTask(const char *arg) {
    (void)arg;
    hi_pwm_set_clock(PWM_CLK_XTAL); 

    while (1) {
        for (size_t i = 0; i < sizeof(g_scoreNotes); i++) {
            uint8_t note = g_scoreNotes[i];
            uint16_t freqDivisor = g_tuneFreqs[note];
            uint8_t duration = g_scoreDurations[i];

            if (note == NOTE_STOP || freqDivisor == 0) {
                AllOff();
                usleep(duration * 125000);
            } else {
                WifiIotPwmPort mainLed = LED_GREEN_PWM; 
                switch (note) {
                    case NOTE_L5: case NOTE_6: case NOTE_7:
                        mainLed = LED_GREEN_PWM;
                        break;
                    case NOTE_1: case NOTE_2: case NOTE_3:
                        mainLed = LED_YELLOW_PWM;
                        break;
                    case NOTE_S4: case NOTE_5: case NOTE_H6:
                        mainLed = LED_RED_PWM;
                        break;
                    default:
                        mainLed = LED_GREEN_PWM;
                        break;
                }

                PwmStart(BEEPER_PWM_PORT, freqDivisor / 2, freqDivisor);
                BreathingFadingEffect(mainLed, duration);
            }
            AllOff();
            usleep(20000); 
        }
        sleep(2);
    }
    return NULL;
}

static void StartMusicLightApp(void) {
    WatchDogDisable();
    GpioInit();
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_9, WIFI_IOT_IO_FUNC_GPIO_9_PWM0_OUT);
    PwmInit(BEEPER_PWM_PORT);
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_10, WIFI_IOT_IO_FUNC_GPIO_10_PWM1_OUT);
    PwmInit(LED_RED_PWM);
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_11, WIFI_IOT_IO_FUNC_GPIO_11_PWM2_OUT);
    PwmInit(LED_GREEN_PWM);
    IoSetFunc(WIFI_IOT_IO_NAME_GPIO_12, WIFI_IOT_IO_FUNC_GPIO_12_PWM3_OUT);
    PwmInit(LED_YELLOW_PWM);

    osThreadAttr_t attr = {
        .name = "MusLightTsk",
        .stack_size = 2048,
        .priority = osPriorityAboveNormal
    };
    osThreadNew((osThreadFunc_t)MusicLightSyncTask, NULL, &attr);
}

SYS_RUN(StartMusicLightApp);