#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include "main.h"

void bsp_key_init(void);

#define KEY_1      PDin(2)
#define KEY_2      PCin(10)
#define KEY_3      PCin(11)
#define KEY_4      PCin(12)
#define KEY_5      PBin(12)

#define SW_1      PCin(0)
#define SW_2      PCin(1)
#define SW_3      PCin(2)

#endif

