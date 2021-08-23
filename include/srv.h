//############################################################################
//
// File:      srv.h
// Version:   1.0 (aug/2021)
//            
//
// Description: servo macros, structs and prototype functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#ifndef __SRV_H
#define __SRV_H 

// Macros
#define PIN_SERVO                 5U      // GPIO D5
#define SERVO_MIN_ANGLE           55U     // left  (cw)
#define SERVO_MAX_ANGLE           137U    // right (ccw)
#define SERVO_NEUTRAL_ANGLE       100U    // Neutral angle
#define SERVO_DIRECTION_CW        0U      // Clockwise direction (+)
#define SERVO_DIRECTION_CCW       1U      // Counter clockwise direction (-)
#define ENCODER_TRAVEL_COUNT      500     // Encoder travel counts used to drive servo


// Servo structure
typedef struct struct_servo_t
{
  uint8_t pin;        // GPIO Pin
  uint8_t pos;        // Commanded position
  uint8_t dir;        // Direction
}srv_t;

// Prototype Functions
void init_servo(struct_servo_t *srv);
void set_servo_position(struct_servo_t *srv, uint8_t desired_position);
void servo_pos_ctrl_from_encoder(struct_servo_t *srv, int32_t encoder_position);

#endif
