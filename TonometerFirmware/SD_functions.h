#ifndef SD_FUNCTIONS_H_
#define SD_FUNCTIONS_H_

#include <avr/io.h>

const char SD_MOSI, SD_MISO, SD_SCK, SD_SS;
const unsigned char SD_CMD0[6];
const unsigned char SD_CMD1[6];

void SPI_send_byte(unsigned char byte);
unsigned char SPI_recieve_byte();
unsigned char SD_send_cmd(const unsigned char *cmd);
unsigned char SD_init();
unsigned char SD_write_block(char * bf, unsigned char ad1,
		unsigned char ad2, unsigned char ad3, unsigned char ad4);
unsigned char SD_read_block(char * bf, unsigned char ad1,
		unsigned char ad2, unsigned char ad3, unsigned char ad4);

#endif /* SD_FUNCTIONS_H_ */
