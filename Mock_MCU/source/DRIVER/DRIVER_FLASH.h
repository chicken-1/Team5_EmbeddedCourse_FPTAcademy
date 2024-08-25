#ifndef DRIVER_DRIVER_FLASH_H_
#define DRIVER_DRIVER_FLASH_H_

#include <string.h>
#include <stdint.h>
#include <MKE16Z4.h>

uint8_t hex_to_uint8(uint8_t high, uint8_t low);
void hex_string_to_byte_array(const uint8_t *hex_string, uint8_t *byte_array, uint8_t length);
uint8_t Erase_Sector(uint32_t Addr);
void Program_LongWord(uint32_t Address, uint8_t *Data);

#endif /* DRIVER_DRIVER_FLASH_H_ */
