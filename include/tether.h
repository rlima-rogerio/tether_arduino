//############################################################################
//
// File:      tether.h
// Version:   1.0 (dec/2020)
//
// Description: Tether macros, structs and function prototypes.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################


#ifndef __TETHER_H
#define __TETHER_H 

// Macros
#define PIN_TETHER_ANG_AX     A0      // x-axis potentiometer
#define PIN_TETHER_ANG_AY     A1      // y-axis potentimometer
#define ADC_FULLSCALE         1023.0  // Float
#define ADC_HALFSCALE_AX      477U     // Integer
#define ADC_HALFSCALE_AY      471U     // Integer


// Data Structures
// Tether Data Structure 
typedef struct struct_tether_t
{
  float az;       // Azimuth angle
  float el;       // Elevation angle
  float len;      // Tether length
  float tension;  // Tether tension
}tether_t;



// Prototype Functions
void calc_tether_angles(struct_tether_t *tether);

#endif
