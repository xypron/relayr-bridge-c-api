/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#include <stdio.h>
#include <stdint.h>

#include "bridge.h"

int main() {
  char mytext[] = "Hello world!";
  uint8_t buf[256];
  size_t len;

  len = prepare_send(buf, mytext, sizeof(mytext));
  
  printf("crc16 %x\n", crc16(mytext, sizeof(mytext)));

  print_package(buf, len);

  return 0;

}
