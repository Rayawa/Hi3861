#include <stdio.h>
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"

static void *example_task1_entry(void *data)
{
    (void)data;
    for (int i = 0; i < 10; i++) {
        sleep(1);
        printf("example_task1_entry: %d!\r\n", i);
    }
    return NULL;
}

static void *example_task2_entry(void *data)
{
    (void)data;
    for (int i = 0; i < 10; i++) {
        usleep(800000);
        printf("example_task2_entry: %d!\r\n", i);
    }
    return NULL;
}

void example_task_init(void)
{
    osThreadAttr_t attr1 = {0};
    osThreadAttr_t attr2 = {0};

    attr1.name = "example_task1";
    attr1.stack_size = 2048;
    attr1.priority = osPriorityNormal;

    attr2.name = "example_task2";
    attr2.stack_size = 2048;
    attr2.priority = osPriorityNormal;

    if (osThreadNew((osThreadFunc_t)example_task1_entry, NULL, &attr1) == NULL) {
        printf("Example_task1 create failed!\r\n");
    }

    if (osThreadNew((osThreadFunc_t)example_task2_entry, NULL, &attr2) == NULL) {
        printf("Example_task2 create failed!\r\n");
    }
}

SYS_RUN(example_task_init);