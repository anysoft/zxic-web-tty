#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atutils.h" // 引用 atutils.h

int exec_at(int a2)
{
    char *v5 = NULL; // 用于存储返回的信息
    char *s = NULL;  // 用于构建AT指令

    const char *command = *(const char **)(a2 + 4);

    // 判断AT指令是否以 "at" 或 "AT" 开头
    if (!strncmp(command, "at", 2) || !strncmp(command, "AT", 2))
    {
        v5 = (char *)malloc(0x400); // 分配1024字节内存
        s = (char *)malloc(0x40);   // 分配64字节内存

        if (!v5 || !s)
        {
            fprintf(stderr, "Memory allocation failed\n");
            free(v5);
            free(s);
            return -1;
        }

        // 构建AT命令
        sprintf(s, "%s\r\n", command);

        // 调用 get_modem_info
        if (get_modem_info(s, "%s", (void *)&v5) != 0)
        {
            fprintf(stderr, "get_modem_info failed\n");
        }
        else
        {
            printf("Response:%s\n", v5); // 输出返回结果
        }

        // 清理内存
        free(v5);
        free(s);
    }
    else
    {
        puts("command error");
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <AT Command>\n", argv[0]);
        return 1;
    }

    // 准备参数
    char *inputCommand = argv[1];         // 取输入的AT命令
    char *args[2] = {NULL, inputCommand}; // 模拟参数传递结构
    exec_at((int)&args);                  // 调用子函数
    return 0;
}
