//############################################################################
//
// File:        tensionmeter.cpp
// Version:     1.0 (dec/2020)
//
// Description: Tension measurement functions using servo RX-64.
//
// Library:     Dynamixel_Servo-2.1.0 
//              https://github.com/michaelkrzyzaniak/Dynamixel_Servo
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include "ds.h"
#include "tether.h"
#include "tensionmeter.h"



/*******************************************************************************
* Function Name  : conv_torque2tension
* Input          : struct_tether_t *tether
*                : float torque_percentage
* Output         : struct_tether_t *tether
* Return         : None
* Description    : Converts the torque in % into tension in newtons [N].              
*******************************************************************************/
void conv_torque2tension(struct_tether_t *tether, float torque_percentage)
{
  float scaled_tension;

  scaled_tension = RX64_STALL_TORQUE*(torque_percentage/100.0);

  // Tether tension calculation
  tether->tension = scaled_tension/(2*SERVO_ARM_LENGTH*cos(TENSIONMETER_WRAP_ANGLE));  
}
