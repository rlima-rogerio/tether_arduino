//############################################################################
//
// FILE:        Smart Winch and Tether Angle Firmware
// VERSION:     1.0 (dec/2020)
//
// DESCRIPTION: Main function to control winch managing the reeling in and
//              paying out of the tether. Also, the tether angles are computed
//              at the landing platform.
//            
// NOTES:       This codes go to the Arduino Leonardo embedded on UDOO.
//============================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

// Encoder
// https://www.pjrc.com/teensy/td_libs_Encoder.html

// #include <Firmata.h>          // https://www.arduino.cc/en/reference/firmata
#include <Arduino.h>            
#include <Encoder.h>            // Encoder Library (length.*)
#include <Servo.h>
#include "ds.h"
#include "actuator.h"
#include "xtard.h"
#include "control.h"
#include "tether.h"
#include "filter.h"
#include "length.h"
#include "tensionmeter.h"
#include "srv.h"
#include "debug.h"

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   avoid using pins with LEDs attached
Encoder encoder(PIN_ENCODER_A, PIN_ENCODER_B);

Servo servo;

/* Landing Platform variables */
struct_filter_t lpf_filter;
struct_actuator_t actuator;
struct_pid_t pid_tension;
struct_tether_t tether;
struct_servo_t srv;

/* General variables */
state_t state;
error_t error;
// servo_error_t srv_error;

uint16_t count = 0U;
uint32_t timer_us = 0U;
float torque_percentage = 0.0F;

void setup(void)
{
  /* Serial used to communicate with UDOO */
  Serial.begin(9600);

  servo.attach(PIN_SERVO);

  //SERIAL_LN_DEBUG("DEBUG MODE ENABLED...")

  //#ifdef DEBUG
  //  Serial.println(""); Serial.println("");
  //#endif

}

void loop(void)
{

  switch (state)
  {
    /*----------------------------- SETUP_SYSTEM -----------------------------*/
    // State: Initialize the modules
    case SETUP_SYSTEM:

      /* Winch configuration */
      setup_actuator();
      init_actuator(&actuator);

      /* Tension Control Configuration */
      init_pid(&pid_tension);
      pid_tension.setpoint = 2.0; // Tension in newtons, [N]
      lpf_butter_init(&lpf_filter);

      /* Encoder Configuration (tether length) */
      encoder.write(ENCODER_START_COUNT);

      /* Servo Configuration */
      init_servo(&srv);


      delay(1000);

      // Assign the next state
      state = COMMUNICATE_UDOO;
      break;

    /*--------------------------- LISTEN_UDOO -----------------------------*/
    // State: Decode message received from UDOO
    case COMMUNICATE_UDOO:

      /* Send and receive data from UDOO processor */
      // xchange_data;

      /* Build a conditional state transition based on received data */

      // Assign the next state
      state = COMMUNICATE_EXTERNAL_ARDUINO;
      break;

    /*----------------------------- COMMUNICATE_EXTERNAL_ARDUINO -----------------------------*/
    // State: Send command to external Arduino to command the platform and locking mechanism.
    case COMMUNICATE_EXTERNAL_ARDUINO:
      /* Send command to external Arduino */
      // cmd_platform(LEVEL_PLATFORM | LOCK_PLATFORM);

      // Assign the next state
      state = COMPUTE_TETHER_ANGLES;
      break;

    /*----------------------------- COMPUTE_TETHER_ANGLES -----------------------------*/
    // State: Sample potentiometers and compute azimuth and elevation angles
    case COMPUTE_TETHER_ANGLES:
      calc_tether_angles(&tether);


      // Assign the next state
      state = COMPUTE_TETHER_LENGTH;
      break;

    /*----------------------------- COMPUTE_TETHER_LENGTH -----------------------------*/
    // State: Retrieve data from encoder and compute the tether length
    case COMPUTE_TETHER_LENGTH:
      calc_tether_length(&tether, encoder.read());

      // Assign the next state
      state = COMPUTE_TETHER_TENSION;
      break;

    /*------------------------ COMPUTE_TETHER_TENSION ------------------------*/
    // State: Compute tether tension from RX-64 servo's readings
    case COMPUTE_TETHER_TENSION:
      // srv_error =  servo_get(SERVO_DEFAULT_ID,
      //                        SERVO_REGISTER_PRESENT_TORQUE,
      //                        &torque_percentage,    
      //                        SERVO_TIMEOUT_READ);

      // Converts the torque percentage to tension in newtons [N]
      conv_torque2tension(&tether,torque_percentage);
      
      //tether.tension = calc_tether_tension(&tether);

      // Assign the next state
      state = FILTER_TETHER_VARIABLES;
      break;

    /*------------------------ COMPUTE_TETHER_TENSION ------------------------*/
    // State: Compute tether tension from RX-64 servo's readings
    case FILTER_TETHER_VARIABLES:

      lpf_butter(&tether, &lpf_filter);

      // Assign the next state
      state = TETHER_TENSION_CONTROL;
      break;

    /*------------------------ TETHER_TENSION_CONTROL ------------------------*/
    // State: Update PID controller
    case TETHER_TENSION_CONTROL:
      //pid_tension.y = tether.tension;
      //update_pid(&pid_tension);


      // Assign the next state
      state = SERVO_ACTUATION;
      break;

    /*------------------------------ SERVO_ACTUATION -----------------------------*/
    // State: Control servo using encoder's readings
    case SERVO_ACTUATION:
      // set_servo_position(&srv, desired_position);
      servo_pos_ctrl_from_encoder(&srv,encoder.read());
      
      // Assign the next state
      state = WINCH_ACTUATION;
      break;

    /*------------------------------ SERVO_ACTUATION -----------------------------*/
    // State: Control action translated into actuator's behavior
    case WINCH_ACTUATION:
    //sp = update_actuator(pid_tension.u[0], &actuator);
    //drive_actuator(&actuator);

    //if (sp)
    //  state = LISTEN_UDOO;  // Set-point reached, wait for new commands
    //else
    //  state = TIMING;       // Set-point not reached, stays in the loop.
      break;

    /*------------------------ TIMING ------------------------*/
    // State: Control the sampling period
    case TIMING:
      // Timing:
      if ((micros() - timer_us) > TIME_SAMPLING_US)
      {
        timer_us = micros();
        state = COMPUTE_TETHER_ANGLES;      // Think a way to perform communication w/ UDOO
#ifdef DEBUG                                // at lower frequency (other than the closed-loop control rate)
        state = DEBUG_STATE;
#endif
      }
      else
      {
        state = TIMING;
      }

      break;

    /*------------------------ DEBUG ------------------------*/
    // State: Sample accelerometers and current from actuators
    case DEBUG_STATE:
#ifdef DEBUG
      /* ('m': serial monitor, 'p': serial plotter) */
      print_tether_angles(&tether, 'p');
#endif
      // Assign the next state
      state = COMPUTE_TETHER_ANGLES;
      break;

    /*------------------------------ DEFAULT ------------------------------*/
    default:
      // State non-defined:
      state = SETUP_SYSTEM;
      SERIAL_DEBUG("DEFAULT");
      break;
  }  /* Switch case end */
} /* Loop end */
