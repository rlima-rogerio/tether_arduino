//############################################################################
//
// File:        length.h
// Version:     1.0 (dec/2020)
//
// Description: Tether length macros, structs and function prototypes.
//
// Library:     Encoder Library 
//              https://www.pjrc.com/teensy/td_libs_Encoder.html
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################


#ifndef __LENGTH_H
#define __LENGTH_H 

// Macros
#define ENCODER_OPTIMIZE_INTERRUPTS // Optimize the usage of Encoder lib.
#define PIN_ENCODER_A         2     // Quadrature encoder signal A
#define PIN_ENCODER_B         3     // Quadrature encoder signal B
#define ENCODER_START_COUNT   0     // Encoder initial count value



// Prototype Functions
void calc_tether_length(struct_tether_t *tether, int32_t encoder_count);


#endif
