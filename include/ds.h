//############################################################################
//
// File:      ds.h
// Version:   1.0 (mar/2020)
//            2.0 (may/2020)
//
// Description: Data structure macros, structs and prototype functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#ifndef __DS_H
#define __DS_H

#define int8_t                    char
#define uint8_t                   unsigned char
#define uint16_t                  unsigned int
#define int16_t                   int
#define int32_t                   long
#define uint32_t                  unsigned long

#define HBYTE(x)                  ((x&0xFF00) >> 8)
#define LBYTE(x)                  ((x&0x00FF) >> 0)

#define RAD2DEG(x)                57.2957*(x)
#define DEG2RAD(x)                0.01745*(x)

#define ANALOG2BOOL(x)            (analogRead(x) < 800 ? false : true)

#define TIME_SAMPLING_US          20000 // 20000 us = 20 ms

/* Low-power mode variable definition */
typedef struct struct_sleeping_t
{
  bool b_turn_day;
  bool b_is_working;
  uint16_t lowpower_count; /* Counter for lowpower mode */
  uint16_t sleep_period;
}sleeping_t;

typedef enum enum_state_t
{
  SETUP_SYSTEM,
  COMMUNICATE_UDOO,
  COMMUNICATE_EXTERNAL_ARDUINO,
  COMPUTE_TETHER_ANGLES,
  COMPUTE_TETHER_LENGTH,
  COMPUTE_TETHER_TENSION,
  FILTER_TETHER_VARIABLES,
  TETHER_TENSION_CONTROL,
  SERVO_ACTUATION,
  WINCH_ACTUATION,
  TIMING,
  DEBUG_STATE
}state_t;

/* Enum to manage errors */
typedef enum enum_error_t
{
  ERR_NONE,
  ERR_ACCEL,
  ERR_ACTUATOR,
}error_t;

error_t id_error(error_t error);

/* Enum to inform the platform status */
typedef enum enum_status_platform_t
{
  STA_PLATFORM_HALT,
  STA_PLATFORM_LEVEL,
  STA_PLATFORM_LOCKED,
  STA_PLATFORM_UNLOCKED
}status_platform_t;



#endif
