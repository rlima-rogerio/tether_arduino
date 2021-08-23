//############################################################################
//
// File:      debug.cpp
// Version:   1.0 (mar/2020)
//            2.0 (may/2020)
//
// Description: Debug functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include <math.h>
// #include <Adafruit_ADXL345_U.h>
#include "ds.h"
#include "tether.h"
#include "actuator.h"
#include "control.h"
#include "debug.h"

/*******************************************************************************
* Function Name  : print_tether_angles
* Input          : struct_tether_t *th
*                : char *c ('m': serial monitor, 'p': serial plotter)
* Output         : None
* Return         : None
* Description    : Prints the tether angles.
*******************************************************************************/
void print_tether_angles(struct_tether_t *th, char c)
{
  if(c == 'm')        // Serial monitor
  {
    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print(th->az); 
    Serial.print("  "); 
    Serial.print(th->el); 
    Serial.println();
  }
  else if(c == 'p')   // Serial plotter (plot)
  {
    Serial.print(RAD2DEG(th->az)); Serial.print("\t");
    Serial.print(RAD2DEG(th->el)); Serial.println("\t");
  }

}
