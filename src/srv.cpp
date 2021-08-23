//############################################################################
//
// File:      servo.cpp
// Version:   1.0 (aug/2021)
//
//
// Description: Servo functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include "ds.h"
#include "srv.h"


/*******************************************************************************
* Function Name  : init_servo
* Input          : struct_servo_t *srv
* Output         : None
* Return         : None
* Description    : Initialize servo with assigned GPIO Pin.
*******************************************************************************/
void init_servo(struct_servo_t *srv)
{
  srv->pin = PIN_SERVO;
  srv->dir = SERVO_DIRECTION_CW;
  pinMode(srv->pin, SERVO_NEUTRAL_ANGLE);
}


/*******************************************************************************
* Function Name  : set_servo_position
* Input          : struct_servo_t *servo
* Input          : uint8_t desired_position
* Output         : None
* Return         : None
* Description    : Set the desired position to the servo.
*******************************************************************************/
void set_servo_position(struct_servo_t *srv, uint8_t desired_position)
{
  srv->pos = constrain(desired_position, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
  pinMode(srv->pin, srv->pos);
}

/*******************************************************************************
* Function Name  : servo_pos_ctrl_from_encoder
* Input          : struct_servo_t *servo
* Input          : int32_t encoder_position
* Output         : None
* Return         : None
* Description    : Set the desired position to the servo.
*******************************************************************************/
void servo_pos_ctrl_from_encoder(struct_servo_t *srv, int32_t encoder_position)
{
  static int32_t previous_enc_pos = 0;
  int32_t diff = 0;

  diff = encoder_position - previous_enc_pos;

  if (abs(diff) > ENCODER_TRAVEL_COUNT)
  {
    if (srv->dir)
      // srv->pos++;
      srv->pos = constrain(srv->pos + 1, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
    else
      // srv->pos--;
      srv->pos = constrain(srv->pos - 1, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
  }

  /* Invert rotation direction if the MAX limit is reached */
  if (srv->pos >= SERVO_MAX_ANGLE)
  {
    if (srv->dir == SERVO_DIRECTION_CW)
      srv->dir = SERVO_DIRECTION_CCW;
    else
      srv->dir = SERVO_DIRECTION_CW;
  }

  /* Invert rotation direction if the MIN limit is reached */
  if (srv->pos <= SERVO_MIN_ANGLE)
  {
    if (srv->dir == SERVO_DIRECTION_CW)
      srv->dir = SERVO_DIRECTION_CCW;
    else
      srv->dir = SERVO_DIRECTION_CW;
  }

  /* Drive servo */
  pinMode(srv->pin, srv->pos);

  /* Stores the last encoder position for the next function call */
  previous_enc_pos = encoder_position;
}