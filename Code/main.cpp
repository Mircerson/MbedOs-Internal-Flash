/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <inttypes.h>

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


FlashIAP flash;


int main()
{
    uint8_t resultInit;
    resultInit = flash.init();

    uint32_t flash_start = flash.get_flash_start();
    printf("start address: %" PRIX32 "\r\n", flash_start);

    uint32_t flash_size = flash.get_flash_size();
    printf("flash size: %" PRIX32 "\r\n", flash_size);

    uint32_t page_size = flash.get_page_size();
    printf("page size: %" PRIu32 "\r\n", page_size);

    

    uint32_t last_sector_size = flash.get_sector_size(flash_start + flash_size - 1);
    printf("last sector size: %" PRIu32 "\r\n", last_sector_size);

    const uint32_t flash_end = flash_start + flash_size;
    printf("flash end %d \r\n", flash_end);

    uint32_t sector_size = flash.get_sector_size(flash_end-1);

    printf("sector size : %d \n\r",sector_size);

    uint32_t addr = flash_end - sector_size;

    printf("sector addr : %x \n\r",addr);

    uint32_t start_address = flash_start;
    uint32_t erase_size = flash_size;
    


    const unsigned char loraCredentials[128]= { 0x2C, 0xF7, 0xF1, 0x20, 0x32, 0x30, 0x87, 0x43,
                                               0xF7, 0x75, 0x1F, 0xD3, 0x75, 0xB2, 0xBB, 0x66, 0xD4, 0xD2, 0xEF, 0xBC, 0x2E, 0x2E, 0x36, 0x2B };
    unsigned char readBuffer[256];
    int8_t result = -32;

    addr = 0x08040000;


    // result = flash.erase(addr,sector_size);
    // printf("Result erase %d\n\r",result);
    // result = flash.program(loraCredentials,addr,24);
    printf("Result pg %d\n\r",result);
    result = flash.read(readBuffer,addr,24);
    printf("Result read %d\n\r",result);

    for(uint8_t i = 0 ; i <= 30 ; i ++)
    {
        printf("Byte %d %x\n\r",i,readBuffer[i]);

    }


    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
