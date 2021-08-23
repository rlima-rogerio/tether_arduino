//############################################################################
//
// File:      actuator.h
// Version:   1.0 (nov/2020)
//            2.0 (aug/2021)
//
// Description: DC motor (winch) macros, structs and function prototypes.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################


#ifndef __ACTUATOR_H
#define __ACTUATOR_H 

// Macros
#define PIN_WINCH_DIR       4     // Winch direction
#define PIN_WINCH_PWM       6     // PWM control (speed) for winch
#define STOP_SPEED          0     // Minimum allowed winch speed (STOP)
#define MIN_SPEED           0     // Minimum allowed winch speed (STOP)
#define MAX_SPEED           255   // Maximum allowed winch speed
#define ACTUATOR_REEL_IN    0U    // Winch reels in
#define ACTUATOR_REEL_OUT   1U    // Winch reels out
#define TENSION_RNG_LIMIT   1.0   // Tension range in Newtons, [N]
#define DEVIATION2SPEED(x)  ((uint8_t)100*x)  // Converts deviation from
                                              // range to speed.


// Data Structures
// Actuator Data Structure 
typedef struct struct_actuator_t
{
  uint8_t dir;  // Boolean value: 0-up, 1-down (or vice-versa)
  uint8_t spd;  // PWM value: 0-stop, 255-max speed
  float   pos;  // Actuator position: -100 to 100.
}actuator_t;


// Prototype Functions
void setup_actuator(void);
void init_actuator(struct_actuator_t *actuator);
void stop_actuator(struct_actuator_t *actuator);
void drive_actuator(struct_actuator_t *actuator);
//void read_current_actuator(struct_actuator_t *actuator);
uint8_t update_actuator(float sp_tension, float tension, struct_actuator_t *actuator);

#endif
