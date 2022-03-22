#include "FlashMemory.hpp"



FlashMemory::FlashMemory()
{
    //Try to initialise flash
    int8_t rslt=-1;
    // 0 on success
    rslt = this->init();

    if(rslt!=0)
    {
        //Failed to initialise -- print
        printf("Failed to initialise IAP obj\n\r");
        //Stop here & error function
    }
    //Get start address -- for checking
    _flashStartAddress = this->get_flash_start();
    //Get flash size
    _flashSize = this->get_flash_size();
    //Get page size
    _pageSize = this->get_page_size();
    //Last sector size
    _lastSectorSize = this->get_sector_size(this->_flashStartAddress + this->_flashSize - 1);
    //Get flash end -- for checking
    this->_flashEndAddress = this->_flashStartAddress + this->_flashSize;
    //Sector size
    this->_sectorSize = this->get_sector_size(this->_flashEndAddress-1);
}


int8_t FlashMemory::writeMemory(dataToWrite data,uint32_t addressToWrite)
{
    // TO ADD CHECK IF VALID ADDRESS IS PROVIDED!

    //Succesful erase
    if( _eraseMemory(addressToWrite) == 0)
    {
        //Try to write
        if(this->program(data.bytes, addressToWrite, data.len)==0)
        {
            printf("Succesfully written %d bytes at address:%" PRIX32"\n\r",data.len,addressToWrite);
            return 0;
        }
        //Add a read
        //Add a comparison
    }
    return -1;
}

int8_t FlashMemory::_eraseMemory(uint32_t addressToWrite)
{
    //Try to erase sector
    if( this->erase(addressToWrite,this->_sectorSize) == 0)
    {
        printf("Succesfully erased the sector starting at address %" PRIX32"\n\r",addressToWrite);
        return 0;
    }
    else
    {
        printf("Failed to erase memory.\n\r");
        return -1;
    }
}


dataToWrite FlashMemory::readMemory(uint32_t addressToReadFrom,uint16_t lenToRead)
{
    dataToWrite dataHolder;
    uint8_t rslt;

    dataHolder.len = lenToRead;


    rslt = this->read(dataHolder.bytes, addressToReadFrom, dataHolder.len);

    if(rslt == 0)
    {
        printf("Succesfully read %d bytes from address %" PRIX32"\n\r ",
        lenToRead,addressToReadFrom);
        for(uint8_t i = 0 ; i<lenToRead;i++)
        {
            printf("Byte[%d]=%x\n\r",i,dataHolder.bytes[i]);
        }
        return dataHolder;
    
    }

    //Read failed -- return struct with 0
    dataHolder.bytes[99] = {22} ;
    dataHolder.len = 0;
    return dataHolder;
}
