//############################################################################
//
// File:      control.cpp
// Version:   1.0 (mar/2020)
//            2.0 (may/2020)
//
// Description: PID controller functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include "ds.h"
#include "control.h"


/*
  a[0] = KP + KI*(TS/2) + KD/Ts;
  a[1] = -KP + KI*(TS/2) - 2*KD/TS;
  a[2] = KD/TS;

  u[k] = u[k-1] + a[0]*e[k] + a[1]*e[k-1] + a[2]*e[k-2];

  y: output signal (roll or pitch)
  r: setpoint or reference signal
  e: error (= y - r)
  u: controller signal
*/  


/*******************************************************************************
* Function Name  : init_pid
* Input          : struct_pid_t *pid
* Output         : None
* Return         : None
* Description    : Initialize PID controller with pre-defined parameters.
*******************************************************************************/
void init_pid(struct_pid_t *pid)
{
  pid->y    = 0.0;  // y[0]
  pid->u[0] = 0.0;  // u[k]
  pid->u[1] = 0.0;  // u[k-1]
  pid->e[0] = 0.0;  // e[k]
  pid->e[1] = 0.0;  // e[k-1]
  pid->e[2] = 0.0;  // e[k-2]
  pid->a[0] = KP + KI*(TS/2) + KD/TS;     // a[0] = KP + KI*(TS/2) + KD/Ts
  pid->a[1] = -KP + KI*(TS/2) - 2*KD/TS;  // a[1] = -KP + KI*(TS/2) - 2*KD/TS
  pid->a[2] = KD/TS;                      // a[2] = KD/TS
  pid->setpoint = DEFAULT_SETPOINT;       // r[k] = 0.0
}


/*******************************************************************************
* Function Name  : update_pid
* Input          : struct_pid_t *pid
* Output         : struct_pid_t *pid
* Return         : None
* Description    : Update the PID controller.
*******************************************************************************/
void update_pid(struct_pid_t *pid)
{
  pid->e[0] = pid->setpoint - pid->y;
  
  pid->u[0] = pid->u[1] + 
              pid->a[0]*pid->e[0] + 
              pid->a[1]*pid->e[1] + 
              pid->a[2]*pid->e[2];

  pid->u[1] = pid->u[0];
  pid->e[2] = pid->e[1];
  pid->e[1] = pid->e[0];

  /* Anti-windup */
  if (abs(pid->u[0]) > MAX_ANGLE_RAD)
    pid->u[0] = (pid->u[0]/abs(pid->u[0]))*MAX_ANGLE_RAD;
}
