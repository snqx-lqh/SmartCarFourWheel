#include "keyscan.h"

#include "bsp_led.h"
#include "bsp_key.h"


/**
 * @brief 按键扫描函数
 *
 * @param mode 模式为1就是连续扫描，为0就是单次
 */
void key_scan(u8 mode)
{
    static int keyCount = 0;
    static int keyState = 0;
    if(mode == 1) keyState=0;
    if (keyState == 0 && (KEY_1 == 0))
    {
        keyCount++;
        if(keyCount>2)
        {
            keyState = 1;
            keyCount=0;
            
        }
    } else if (KEY_1 == 1)
    {
        keyState = 0;

    }
}

