/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

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
  size_t ret;
  int i;
  struct timespec pause = {0, 1000000};

  if (argc != 2) {
    help(argv[0]);
  }

  len = prepare_send(buf, mytext, sizeof(mytext) - 1);

  printf("crc16 %x\n", crc16(mytext, sizeof(mytext)));

  print_package(buf, len);

  fd = seropen(argv[1]);
  if (fd == -1) {
    exit(EXIT_FAILURE);
  }

  ret = serwriteb(fd, BRIDGE_COMM_PING);
  printf("%d bytes written to %s\n", ret, argv[1]);

  for (i = 0; i < 1000; ++i) {
    ret = serread(fd, buf, sizeof(buf));
    if (ret > 0) {
      printf("%d bytes read from %s\n", ret, argv[1]);
      printf("%02x\n", buf[0]);
    }
    nanosleep(&pause, NULL);
  }

  ret = serwrite(fd, buf, len);
  printf("%d bytes written to %s\n", ret, argv[1]);

  for (i = 0; i < 1000; ++i) {
    ret = serread(fd, buf, sizeof(buf));
    if (ret > 0) printf("%d bytes read from %s\n", ret, argv[1]);
    nanosleep(&pause, NULL);
  }

  serclose(fd);

  return EXIT_SUCCESS;

}
