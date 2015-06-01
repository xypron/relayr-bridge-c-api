/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#include <stdio.h>

#include "bridge.h"

/**
 * Sends a data package.
 *
 * @param out data out
 * @param in data in
 * @param size number of elements in data in
 * @return number of elements in data out
 */
size_t prepare_send(uint8_t *out, uint8_t *in, size_t size) {
   size_t i;
   size_t pos = 0;;
   uint16_t crc;

   if (size > PAYLOAD_MAX_LENGTH) {
     return 0;
   }

   out[pos] = BRIDGE_COMM_WRITE_UP_CHANNEL;
   out[++pos] = size;
   for (i = 0; i < size; ++i) {
     out[++pos] = in[i];
   }
   crc = crc16(in, size);
   out[++pos] = crc & 0xff;
   out[++pos] = crc >> 8;
   return ++pos;
}

/**
 * Prints a data package.
 *
 * @param dat data
 * @param size number of elements in data
 */
void print_package(uint8_t *data, size_t size) {
  size_t i;

  for (i = 0; i < size; ++i) {
    printf("%02x ", data[i]);
  }
  printf("| ");
  for (i = 0; i < size; ++i) {
    if (32 < data[i] && data[i] < 127) {
      printf("%c", data[i]);
    } else { 
      printf(".");
    }
  }
  printf("\n");
}

