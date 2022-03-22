/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <inttypes.h>



#include "FlashMemory.hpp"
// Blinking rate in milliseconds


//FlashIAP flash;


FlashMemory internalFlash;
dataToWrite myData;


int main()
{
    myData.bytes[0]=0x20;
    myData.bytes[1] = 0x30;
    myData.bytes[2] = 0x40;
    myData.len = 3;
    internalFlash.writeMemory(myData, 0x08040000);
    internalFlash.readMemory(0x08040000, 3);
    while (true) {
    }
}
