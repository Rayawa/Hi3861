#include <stdio.h>
#include "ohos_init.h"


void DrawArt(void) {
    // 打印一个简单的心形
    printf("\r\n");
    printf("  ******           ****** \r\n");
    printf("**********       **********\r\n");
    printf("************* *************\r\n");
    printf(" ************************* \r\n");
    printf("   ********************* \r\n");
    printf("     ***************** \r\n");
    printf("       ************* \r\n");
    printf("         ********* \r\n");
    printf("           ***** \r\n");
    printf("             * \r\n");
    printf("\r\n       Hello HarmonyOS!   \r\n");
}
SYS_RUN(DrawArt);