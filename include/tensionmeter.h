//############################################################################
//
// File:        tensionmeter.h
// Version:     1.0 (dec/2020)
//
// Description: Tension measurement macros, structs and function prototypes.
//
// Library:     Dynamixel_Servo-2.1.0 
//              https://github.com/michaelkrzyzaniak/Dynamixel_Servo
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################


#ifndef __TENSIONMETER_H
#define __TENSIONMETER_H 

// Macros
#define PIN_SERVO_RX                  0     // Servo RX-64 Rx line
#define PIN_SERVO_TX                  1     // Servo RX-64 Tx line
#define HALF_DUPLEX_DIRECTION_PIN     4     // Servo RX-64 direction line
#define SERVO_TIMEOUT_READ            5     // Reduced read timeout, [ms]
#define SERVO_TIMEOUT_WRITE           50    // Suggested timeout, [ms]

#define ERROR_INPUT_VOLTAGE           0x01  // Applied voltage is out of range
#define ERROR_ANGLE_LIMIT             0x02  // Goal angle is out of range
#define ERROR_OVERHEATING             0x04  // Operating temperature is out of range
#define ERROR_RANGE                   0x08  // Command code is out of range
#define ERROR_CHECKSUM                0x10  // Checksum is invalid
#define ERROR_OVERLOAD                0x20  // Current load is out of range
#define ERROR_INSTRUCTION             0x40  // Undefined instruction transmitted

#define SERVO_PARAM_ALARM_LED_ON      (ERROR_INPUT_VOLTAGE | ERROR_ANGLE_LIMIT | ERROR_OVERHEATING | ERROR_OVERLOAD)
#define SERVO_PARAM_ALARM_SHUTDOWN_ON (ERROR_INPUT_VOLTAGE | ERROR_ANGLE_LIMIT | ERROR_OVERHEATING | ERROR_OVERLOAD)
#define SERVO_PARAM_MAX_TORQUE        100   // Maximum torque | 1023
#define SERVO_PARAM_MIN_ANGLE         0     // Minimum limit angle (  0 deg)
#define SERVO_PARAM_MAX_ANGLE         PI    // Maximum limit angle (300 deg) | 1023
#define SERVO_PARAM_MIN_VOLTAGE       10    // Minimum limit voltage 10V (value/10) | 100
#define SERVO_PARAM_MAX_VOLTAGE       21    // Maximum limit voltage 21V (value/10) | 210
#define SERVO_PARAM_GOAL_ANGLE        (PI/2)// Goal position (min < goal < max) | 512
#define SERVO_PARAM_RETURN_DELAY_TIME 100   // 1 unit = 2 usec
#define SERVO_PARAM_TORQUE_ENABLE     0x01  // Enable torque generation

#define RX64_STALL_TORQUE             5.3   // Stall torque @ 18.5V
#define SERVO_ARM_LENGTH              0.3   // Arm length attached to the servo
#define TENSIONMETER_WRAP_ANGLE       (PI/4)  // Wrap angle of the tension device


// Data Structures
// Tether Data Structure 


// Prototype Functions
void conv_torque2tension(struct_tether_t *tether, float torque_percentage);

#endif
