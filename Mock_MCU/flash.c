#include "MKE16Z4.h"
#include "flash.h"


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
