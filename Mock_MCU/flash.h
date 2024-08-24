#ifndef FLASH_H
#define FLASH_H

#include "MKE16Z4.h"
#include "string.h"

uint8_t  Erase_Sector(uint32_t Addr);
void Program_LongWord(uint32_t Address, uint8_t *Data);
uint32_t Read_Flash_Address(uint32_t Address);

#endif
