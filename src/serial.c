/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "serial.h"

void sersetoptions(int fd) {
  struct termios options;
  struct termios options22;

  tcgetattr(fd, &options);

  /*
   * Baud rate 115200
   */
  cfsetispeed(&options, B115200);
  cfsetospeed(&options, B115200);

  /*
   * Ignore modem control lines.
   * Enable receiver.
   */
  options.c_cflag |= (CLOCAL | CREAD);

  /*
   * 8 bit not parity,  8N1
   */
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  /*
   * set raw input, 1 second timeout
   */
  options.c_cflag     |= (CLOCAL | CREAD);
  options.c_lflag     &= ~(ICANON | ECHO | ECHOE | ISIG);
  options.c_oflag     &= ~OPOST;
  options.c_cc[VMIN]  = 0;
  options.c_cc[VTIME] = 10;

  /*
   * set the options
   */
  tcsetattr(fd, TCSANOW, &options);
}

int seropen(const char *tty) {
  int fd = open(tty, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("seropen");
    exit(EXIT_FAILURE);
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
