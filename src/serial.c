/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#define _POSIX_SOURCE 1

#include "serial.h"

void sersetoptions(int fd) {
  int ret;
  struct termios config;

  ret = tcgetattr(fd, &config);
  if (ret == -1) {
    perror("tcgetattr");
    exit(EXIT_FAILURE);
  }

  /*
   *  Turn off input processing.
   */
  config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
                      INLCR | PARMRK | INPCK | ISTRIP | IXON);

  /*
   *  Turn off output processing.
   */
  config.c_oflag = 0;

  /*
   *  No line processing.
   */
  config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

  /*
   *  Turn off character processing.
   */
  config.c_cflag &= ~(CSIZE | PARENB);
  config.c_cflag |= CS8;

  /*
   *  Wait for a maximum of one second.
   *  Inter-character timer off
   */
  config.c_cc[VMIN]  = 0;
  config.c_cc[VTIME] = 10;

  /*
   * Set baud rate.
   */
  if(cfsetispeed(&config, B115200) == -1
      || cfsetospeed(&config, B115200) == -1) {
    perror("Baud rate not supported");
    exit(EXIT_FAILURE);
  }

  /*
   * set the options
   */
  tcsetattr(fd, TCSANOW, &config);
}

int seropen(const char *tty) {
  int fd = open(tty, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("seropen");
    exit(EXIT_FAILURE);
  }

  /*
   * Check this is a serial device.
   */
  if(!isatty(fd)) {
    fprintf(stderr, "%s is not a serial device\n", tty);
    close(fd);
    return -1;
  }


  return fd;
}

ssize_t serwrite(int fd, const uint8_t *buf, size_t count) {
  ssize_t ret = write(fd, buf, count);
  if (ret == -1) {
    perror("serwrite");
    exit(EXIT_FAILURE);
  }

  return ret;
}

ssize_t serwriteb(int fd, const uint8_t byte) {
  return serwrite(fd, &byte, 1);
}

ssize_t serread(int fd, uint8_t *buf, size_t count) {
  ssize_t ret = read(fd, buf, count);

  if (ret == -1) {
    if (errno != EAGAIN) {
      perror("serread");
      exit(EXIT_FAILURE);
    }
    ret = 0;
  }

  return ret;
}


int serclose(int fd) {
  return close(fd);
}
