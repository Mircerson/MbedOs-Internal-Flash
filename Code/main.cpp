#include "mbed.h"
#include "FlashMemory.hpp"


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
    while (true) {};
}
