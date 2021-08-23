//############################################################################
//
// File:      length.cpp
// Version:   1.0 (dec/2020)
//
// Description: Tether length measurement functions using an encoder.
//
// Library:     Encoder Library 
//              https://www.pjrc.com/teensy/td_libs_Encoder.html
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include "ds.h"
#include "tether.h"
#include "length.h"



/*******************************************************************************
* Function Name  : init_actuator
* Input          : struct_tether_t *tether
*                : int32_t encoder_count 
* Output         : struct_tether_t *tether
* Return         : None
* Description    : Calculates the tether length from the encoder output count.              
*******************************************************************************/
void calc_tether_length(struct_tether_t *tether, int32_t encoder_count)
{
  // TBD
  tether->len = (float)1.0*encoder_count;  // Converts the counts to meter
}
