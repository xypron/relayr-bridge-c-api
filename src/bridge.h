/*
 * Copyright 2015, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#ifndef _BRIDGE_
#define _BRIDGE_

#include <stddef.h>
#include <stdint.h>
#include "bridgeconst.h"

uint16_t crc16(uint8_t *data, size_t size);
size_t prepare_send(uint8_t *out, uint8_t *in, size_t size);
void print_package(uint8_t *data, size_t size);

#endif // _BRIDGE_
