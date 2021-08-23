//############################################################################
//
// File:      control.h
// Version:   1.0 (mar/2020)
//            2.0 (may/2020)
//
// Description: PID controller macros, structs and prototype functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#ifndef __CONTROL_H
#define __CONTROL_H 

// Macros
#define KP                        0.8     // Proportional gain
#define KD                        0.00    // Derivative gain
#define KI                        0.00    // Integral gain 
#define TS                        0.02    // Time sampling: 20 ms or 50 Hz
#define MAX_ANGLE_RAD             0.3142  // Radians
#define DEFAULT_SETPOINT          2.0     // Tension in newtons, [N]


// PID structure
typedef struct struct_pid_t
{
  float y;        // Output signal
  float u[2];     // Controller signal
  float e[3];     // Error signal
  float setpoint; // Set-point or reference
  float a[3];     // Coefficients
}pid_t;

// Prototype Functions
void init_pid(struct_pid_t *pid);
void update_pid(struct_pid_t *pid);

#endif
