#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hi_at.h"
#include "ohos_init.h"

// 1. 定义回调函数：处理 AT+CALC=num1,num2
hi_u32 at_setup_calc_cmd(hi_s32 argc, const hi_char *argv[])
{
    // 参数校验：必须输入2个参数
    if (argc != 2) {
        hi_at_printf("Usage: AT+CALC=a,b\r\n");
        return HI_ERR_SUCCESS; 
    }

    // 将字符串参数转为整数
    int a = atoi(argv[0]);
    int b = atoi(argv[1]);

    // 计算并输出结果
    hi_at_printf("\r\n+CALC:Sum=%d", a + b);
    hi_at_printf("\r\n+CALC:Diff=%d", a - b);
    hi_at_printf("\r\n+CALC:Prod=%d", a * b);

    if (b != 0) {
        hi_at_printf("\r\n+CALC:Quot=%d\r\n", a / b);
    } else {
        hi_at_printf("\r\n+CALC:Quot=Error(Div0)\r\n");
    }

    return HI_ERR_SUCCESS;
}

// 2. 创建指令列表数组
static const at_cmd_func g_my_at_table[] = {
    // 指令名称, 名称长度, 测试, 查询, 设置(回调), 执行
    {"+CALC", 5, HI_NULL, HI_NULL, (at_call_back_func)at_setup_calc_cmd, HI_NULL},
};

// 3. 动态注册函数
void my_at_cmd_register(void)
{
    // 调用 hi_at_register_cmd 进行注册
    hi_at_register_cmd(g_my_at_table, sizeof(g_my_at_table) / sizeof(g_my_at_table[0]));
}

// 4. 使用系统的初始化宏，使程序启动时自动注册
SYS_RUN(my_at_cmd_register);