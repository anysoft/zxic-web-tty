#ifndef NVRAM_H
#define NVRAM_H

int cfg_get_item(char *key, char *value, int len);
int cfg_set(char *key, char *value);
int cfg_unset(char *key);
void cfg_reset(void);
void cfg_save(void);

#endif // NVRAM_H

