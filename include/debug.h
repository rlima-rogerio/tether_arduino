//############################################################################
//
// File:      debug.h
// Version:   1.0 (mar/2020)
//            2.0 (may/2020)
//
// Description: Debug macros, structs and prototype functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#ifndef __DEBUG_H
#define __DEBUG_H

#define DEBUG

#ifdef DEBUG
#define SERIAL_ERROR(x)           Serial.println(x)
#define SERIAL_DEBUG(x)           Serial.print(x);
#define SERIAL_LN_DEBUG(x)        Serial.println(x);
#else
#define SERIAL_ERROR(x)
#define SERIAL_DEBUG(x)
#endif

//#define DEBUG_SERIAL_MONITOR
//#define DEBUG_SERIAL_PLOTTER




void print_tether_angles(struct_tether_t *th, char c);

#endif
