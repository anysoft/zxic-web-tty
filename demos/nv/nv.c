#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <nvram.h>

// 

int cfg_get_item(char *key,char *value,int len);
int cfg_set(char *key,char *value);
int cfg_unset(char *key);
void cfg_reset();
void cfg_save();

#define CFGLEN 256
#define cfg_get(key, value) cfg_get_item(key, value, CFGLEN)

int main(int argc,char *argv[]){
    char buf[CFGLEN];
    char imei[32] = {0};
    cfg_get("imei",buf);
    strcpy(imei,buf);
    printf("IMEI=");
    printf(imei);

    // 设置键值对
    char key[] = "test_anysoft";
    char value[] = "anysoft";

    if (cfg_set(key, value) == 0) {
        printf("Successfully set %s to %s.\n", key, value);
    } else {
        fprintf(stderr, "Failed to set %s.\n", key);
        return EXIT_FAILURE;
    }

    // 保存配置
    cfg_save();
    printf("Configuration saved successfully.\n");

    return EXIT_SUCCESS;

}
