/*
 * Author: Daniel Mancuso, 2014
 */

#ifndef _BRIDGECONST_H_
#define _BRIDGECONST_H_

/**
 * Maximum payload length for the Bridge UART packet.
 */
#define PAYLOAD_MAX_LENGTH  19

typedef enum {
  BRIDGE_COMM_WRITE_UP_CHANNEL  = 0x01,
  BRIDGE_COMM_READ_UP_CHANNEL   = 0x02,
  BRIDGE_COMM_READ_DOWN_CHANNEL = 0x03,
  BRIDGE_COMM_ACK               = 0x04,
  BRIDGE_COMM_NACK              = 0x05,
  BRIDGE_COMM_PING              = 0x06,
  BRIDGE_COMM_RCV_FROM_BLE      = 0x07,
  BRIDGE_COMM_NCONN             = 0x08,
}
bridge_commands_t;

#endif // _BRIDGECONST_H_
