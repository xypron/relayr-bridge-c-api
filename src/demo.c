/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "bridge.h"
#include "serial.h"

void help(char *p) {

  printf("Usage: %s TTY\n"
    "Output data to Relayr bridge module connected to serial port TTY.\n\n"
    "Example:\n"
    "  %s /dev/ttyUSB0\n\n", p, p);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  char mytext[] = "Hello world!";
  uint8_t buf[256];
  size_t len;
  int fd;

  if (argc != 2) {
    help(argv[0]);
  }

  len = prepare_send(buf, mytext, sizeof(mytext));
  
  printf("crc16 %x\n", crc16(mytext, sizeof(mytext)));

  print_package(buf, len);

  fd = seropen(argv[1]);
  len = serwrite(fd, buf, len);

  printf("%d bytes written to %s\n", len, argv[1]);

  len = serread(fd, buf, sizeof(buf));

  printf("%d bytes read from %s\n", len, argv[1]);

  serclose(fd);

  return EXIT_SUCCESS;

}
