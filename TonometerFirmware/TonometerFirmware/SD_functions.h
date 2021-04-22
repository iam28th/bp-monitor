/*
 * SD_functions.h
 *
 * Created: 4/19/2021 7:53:50 AM
 *  Author: Home
 */ 


#ifndef SD_FUNCTIONS_H_
#define SD_FUNCTIONS_H_

#include <avr/io.h>

const char MOSI, MISO, SCK, SS;
const unsigned char SD_CMD0[6];
const unsigned char SD_CMD1[6];

void SPI_send_byte(unsigned char byte);
unsigned char SPI_recieve_byte();
unsigned char SD_send_cmd(const unsigned char *cmd);
unsigned char SD_init();

#endif /* SD_FUNCTIONS_H_ */