//############################################################################
//
// File:      tether.cpp
// Version:   1.0 (dec/2020)
//
// Description: Tether functions to compute azimuth & elevation angles (pot.) 
//              tether length (encoder), and tether tension (servo RX-64). 
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include <math.h>
#include "ds.h"
#include "tether.h"

/*******************************************************************************
* Function Name  : read_current_actuator
* Input          : struct_actuator_t *actuator
* Output         : struct_actuator_t *actuator
* Return         : None
* Description    : Read the raw current (from internal 10-bit ADC) and scales it              
*                  to mili amperes (mA).
*******************************************************************************/
void calc_tether_angles(struct_tether_t *tether)
{
  int16_t raw_ax, raw_ay, raw_max;   // 0 to 1023 counts from 10-bit ADC

  /* Read and convert tether azimuth angle */
  raw_ax = analogRead(PIN_TETHER_ANG_AX) - ADC_HALFSCALE_AX;
  raw_ay = analogRead(PIN_TETHER_ANG_AY) - ADC_HALFSCALE_AY;

//  Serial.print(raw_ax); Serial.print("\t");
//  Serial.print(raw_ay); Serial.println("\t");
  
  /* Take the greater value */
  raw_max = (abs(raw_ax) > abs(raw_ay)) ? raw_ax : raw_ay;

  /* Azimuth angle */
  if (raw_ax == 0U && raw_ay > 0U)
    tether->az = 90.0F;
  else if (raw_ax == 0U && raw_ay < 0U)
    tether->az = -90.0F;
  else
    tether->az = atan2((double)raw_ay, (double)raw_ax);

  /* Elevation angle */
  if (raw_max == 0U)
    tether->el = 90.0F;
  else
    tether->el = acos( abs((double)raw_max/ADC_FULLSCALE) );
}
