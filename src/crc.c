/*
 * Author: Daniel Mancuso, 2014
 */

#include "bridge.h"

/**
 * Calculates a 16 bit redundancy checksum.
 *
 * @param data data
 * @param size number of elements in data
 * @return checksum
 */
uint16_t crc16(uint8_t *data, size_t size) {
  size_t i;
  uint16_t crc = 0xffff;

  for (i = 0; i < size; ++i) {
    crc = (crc >> 8) | (crc << 8);
    crc ^= data[i];
    crc ^= (crc & 0xf0) >> 4;
    crc ^= crc << 12;
    crc ^= (crc & 0xff) << 5;
  }
  return crc;
}
