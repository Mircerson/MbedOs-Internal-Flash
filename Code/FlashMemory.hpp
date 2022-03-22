#ifndef __FLASH__MEMORY__H
#define __FLASH__MEMORY__H

#include "mbed.h"
#include <inttypes.h>



struct dataToWrite{
    uint8_t bytes[100];
    uint8_t len;
};

//Feels like inheritance.. ? 
class FlashMemory : private FlashIAP {


    public:
    FlashMemory();
    int8_t writeMemory(dataToWrite data,uint32_t addressToWrite);
    dataToWrite readMemory(uint32_t addressToReadFrom,uint16_t lenToRead);
    private:

    uint32_t _flashStartAddress;
    uint32_t _flashSize;
    uint32_t _pageSize;
    uint32_t _lastSectorSize;
    uint32_t _flashEndAddress;
    uint32_t _sectorSize;
    uint32_t _whereToWrite;

    int8_t _eraseMemory(uint32_t addressToWrite);

};


#endif