//############################################################################
//
// File:      udooi.h
// Version:   1.0 (dec/2020)
//
// Description: Interface to communicate with external Arduino. Macros, 
//              structs and prototype functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################


#ifndef __XTARD_H
#define __XTARD_H


#define PIN_EXT_ARD_COMM_BIT0 8  // Bit 0 of 2-bit comm. w/ ext. Arduino
#define PIN_EXT_ARD_COMM_BIT1 12 // Bit 1 of 2-bit comm. w/ ext. Arduino

/* Enum to manage errors */
typedef enum enum_xtard_cmd_t
{
  CMD_HALT    = 0U,
  CMD_LEVEL   = 1U,
  CMD_LOCK    = 2U,
  CMD_UNLOCK  = 3U
}xtard_cmd_t;

// Prototype Functions
xtard_cmd_t set_xtard_cmd(void);

#endif
