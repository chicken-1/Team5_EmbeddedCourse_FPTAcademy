#include <MKE16Z4.h>
//#include "Flash.h"

uint8_t  Erase_Sector(uint32_t Addr)
{
    /* wait previous cmd finish */
    while (FTFA->FSTAT == 0x00);

    /* clear previous cmd error */
    if(FTFA->FSTAT != 0x80)
    {
        FTFA->FSTAT = 0x30;
    }
    /* Erase all bytes in a program flash sector */
    FTFA->FCCOB0 = 0x09;

    /* fill Address */
    FTFA->FCCOB1 = (uint8_t)(Addr >> 16);
    FTFA->FCCOB2 = (uint8_t)(Addr >> 8);
    FTFA->FCCOB3 = (uint8_t)(Addr >> 0);

    /* Clear CCIF */
    FTFA->FSTAT = 0x80;
    /* wait cmd finish */
    while (FTFA->FSTAT == 0x00);

    return 1;
}

/* Erase all flash sector */
uint8_t  Erase_Multi_Sector(uint32_t Addr, uint8_t Size)
{
    uint8_t index;

    for(index = 0; index < Size; index++)
    {
        Erase_Sector(Addr + index * 1024);
    }

    return 1;
}


void Program_LongWord(uint32_t Address, uint8_t *Data)
{
	// wait previous command finish
	while (FTFA->FSTAT == 0x00);

	// clear previous cmd error
	if (FTFA->FSTAT != 0x80)
	{
		FTFA->FSTAT = 0x30; // Clear 2 error flag
	}

	// Flash 4 bytes in a program flash sector
	FTFA->FCCOB0 = 0x06;  // command erase
	FTFA->FCCOB1 = (Address >> 16) & 0xFF;
	FTFA->FCCOB2 = (Address >> 8) & 0xFF;
	FTFA->FCCOB3 = (Address >> 0) & 0xFF;

	FTFA->FCCOB4 = Data[0];
	FTFA->FCCOB5 = Data[1];
	FTFA->FCCOB6 = Data[2];
	FTFA->FCCOB7 = Data[3];

	// run command
	FTFA->FSTAT = 0x80;

	// wait command finish
	while (FTFA->FSTAT == 0x00);

}

uint32_t Read_Flash_Address(uint32_t Address)
{
	return *(volatile uint32_t *)Address;
}


int main(){
	uint8_t Data[4] = {0x12, 0x13, 0x14, 0x15};
	uint32_t Addr_Check = 0;
	uint32_t Addr_Check2 = 0;
	uint32_t Addr_Check3 = 0;

	Erase_Sector(0xA000);
	Program_LongWord(0xA000, Data);

	Addr_Check = Read_Flash_Address(0xA000);

	//Erase_Sector(0xA004);
	Program_LongWord(0xA004, Data);

	Addr_Check2 = Read_Flash_Address(0xA004);

	Program_LongWord(0xA008, Data);

	Addr_Check3 = Read_Flash_Address(0xA008);

	Erase_Sector(0xA008);
	while(1){

	}

	return 0;
}

