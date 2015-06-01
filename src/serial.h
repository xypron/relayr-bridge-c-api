/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdint.h>
#include <unistd.h>

int seropen(const char *tty);
ssize_t serwrite(int fd, const uint8_t *buf, size_t count);
ssize_t serwriteb(int fd, const uint8_t byte);
ssize_t serread(int fd, uint8_t *buf, size_t count);
int setclose(int fd);

#endif // _SERIAL_H_
