//############################################################################
//
// File:      actuator.cpp
// Version:   1.0 (nov/2020)
//            2.0 (aug/2021)
//
// Description: DC motor (winch) actuator functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include "ds.h"
#include "actuator.h"
//#include "debug.h"


/*******************************************************************************
* Function Name  : setup_actuator
* Input          : None
* Output         : None
* Return         : None
* Description    : Setup all the GPIOs related to the actuators.              
*******************************************************************************/
void setup_actuator()
{
  // All pins should be setup as outputs:
  pinMode(PIN_WINCH_PWM, OUTPUT);
  pinMode(PIN_WINCH_DIR, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PIN_WINCH_PWM, LOW);
  digitalWrite(PIN_WINCH_DIR, LOW);
}


/*******************************************************************************
* Function Name  : init_actuator
* Input          : struct_actuator_t *actuator
* Output         : None
* Return         : None
* Description    : Defines the direction and speed of the actuators.              
*******************************************************************************/
void init_actuator(struct_actuator_t *actuator)
{
  actuator->dir = ACTUATOR_REEL_IN;  // Use a macro to set for UP/DOWN;
  actuator->spd = STOP_SPEED;    // Start with PWM = 0
}


/*******************************************************************************
* Function Name  : stop_actuator
* Input          : struct_actuator_t *actuator
* Output         : None
* Return         : None
* Description    : Set the speed of the actuator to zero to stop it.              
*******************************************************************************/
void stop_actuator(struct_actuator_t *actuator)
{
  analogWrite(PIN_WINCH_PWM, STOP_SPEED);
}


/*******************************************************************************
* Function Name  : drive_actuator
* Input          : struct_actuator_t *actuator
* Output         : None
* Return         : None
* Description    : Set direction and speed of the actuators.              
*******************************************************************************/
void drive_actuator(struct_actuator_t *actuator)
{
  digitalWrite(PIN_WINCH_DIR, actuator->dir);
  analogWrite(PIN_WINCH_PWM, actuator->spd);
}


/*******************************************************************************
* Function Name  : read_current_actuator
* Input          : struct_actuator_t *actuator
* Output         : struct_actuator_t *actuator
* Return         : None
* Description    : Read the raw current (from internal 10-bit ADC) and scales it              
*                  to mili amperes (mA).
*******************************************************************************/
//void read_current_actuator(struct_actuator_t *actuator)
//{
//  uint16_t raw_current; // 0 to 1023 counts from 10-bit ADC
//
//  /* Read and convert current of actuator A */
//  raw_current = analogRead(CURRENT_A);
//  actuator->which[ACTUATOR_A].i_ma = (float)ADC2MA(raw_current);
//
//  /* Read and convert current of actuator B */
//  raw_current = analogRead(CURRENT_B);
//  actuator->which[ACTUATOR_B].i_ma = (float)ADC2MA(raw_current);
//}


/*******************************************************************************
* Function Name  : angle2motion
* Input          : float u_roll
*                : float u_pitch
* Output         : struct_actuator_t *actuator
* Return         : false: if the set point is notreached
*                : true:  if the set point is reached
* Description    : From the signal controls 'sp_tension' and 'u_tension', in 
*                  newtons, the actuator driving direction, as well as the stop 
*                  condition and the speed of actuation are defined.
*******************************************************************************/
uint8_t update_actuator(float sp_tension, float u_tension, struct_actuator_t *actuator)
{
  uint8_t spd;
  uint8_t retval = false;

  /* Release cable */
  if (u_tension > (sp_tension + TENSION_RNG_LIMIT) )
  {
    // Set turn direction UP
    actuator->dir = ACTUATOR_REEL_IN;                    
    
    // Compute a PWM proportional to the distance outside the range
    spd = DEVIATION2SPEED(u_tension - (sp_tension + TENSION_RNG_LIMIT));
    
    // Limit the value to the max allowed PWM value (255)
    actuator->spd = (spd <= 255)?(spd):(255);
  }
  /* Rectract cable */
  else if (u_tension < (sp_tension - TENSION_RNG_LIMIT))    
  {
    // Set turn direction DOWN
    actuator->dir = ACTUATOR_REEL_OUT;
    
    // Compute a PWM proportional to the distance outside the range
    spd = DEVIATION2SPEED((sp_tension - TENSION_RNG_LIMIT) - u_tension);
    
    // Limit the value to the max allowed PWM value (255)
    actuator->spd = (spd <= 255)?(spd):(255);
  }
  /* Stop, otherwise */
  else
  {
    actuator->spd = STOP_SPEED;
  }

  return retval;
}
