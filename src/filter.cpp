//############################################################################
//
// File:      filter.cpp
// Version:   1.0 (dec/2020)
//
// Description: Low-pass filtering functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include <math.h>
#include "ds.h"
#include "tether.h"
#include "filter.h"



/*******************************************************************************
* Function Name  : lpf_butter_init
* Input          : struct_filter_t *lpf_filter
* Output         : None
* Return         : None
* Description    : Initialize the digital low pass filter.
*******************************************************************************/
void lpf_butter_init(struct_filter_t *lpf_filter)
{
  int i;
  
  // denominator
  lpf_filter->a[0] = LPF_BUTTER_DEN_A1;
  lpf_filter->a[1] = LPF_BUTTER_DEN_A2;
  lpf_filter->a[2] = LPF_BUTTER_DEN_A3;
  // numerator
  lpf_filter->b[0] = LPF_BUTTER_NUM_B1;
  lpf_filter->b[1] = LPF_BUTTER_NUM_B2;
  lpf_filter->b[2] = LPF_BUTTER_NUM_B3;

    for (i=0; i<4; i++)
  {
    lpf_filter->xk[i] = 0.0;
    lpf_filter->xk_1[i] = 0.0;
    lpf_filter->xk_2[i] = 0.0;
    lpf_filter->yk[i] = 0.0;
    lpf_filter->yk_1[i] = 0.0;
    lpf_filter->yk_2[i] = 0.0;
  }
}


/*******************************************************************************
* Function Name  : lpf_butter
* Input          : struct_filter_t *lpf_filter
*                : struct_tether_t *tether
* Output         : struct_tether_t *tether
* Return         : None
* Description    : Apply low pass filter to tether variables.
*******************************************************************************/
void lpf_butter(struct_tether_t *tether, struct_filter_t *lpf_filter)
{
  int i;
  // accel data
  lpf_filter->xk[0] = tether->az;
  lpf_filter->xk[1] = tether->el;
  lpf_filter->xk[2] = tether->len;
  lpf_filter->xk[3] = tether->tension;

  //xk and yk indices defines different variables
  // Tether variables
  // Azimuth angle
  lpf_filter->yk[0] = lpf_filter->b[0]*lpf_filter->xk[0] + lpf_filter->b[1]*lpf_filter->xk_1[0] + lpf_filter->b[2]*lpf_filter->xk_2[0] - lpf_filter->a[1]*lpf_filter->yk_1[0] - lpf_filter->a[2]*lpf_filter->yk_2[0];
  // Elevation angle
  lpf_filter->yk[1] = lpf_filter->b[0]*lpf_filter->xk[1] + lpf_filter->b[1]*lpf_filter->xk_1[1] + lpf_filter->b[2]*lpf_filter->xk_2[1] - lpf_filter->a[1]*lpf_filter->yk_1[1] - lpf_filter->a[2]*lpf_filter->yk_2[1];
  // Tether length
  lpf_filter->yk[2] = lpf_filter->b[0]*lpf_filter->xk[2] + lpf_filter->b[1]*lpf_filter->xk_1[2] + lpf_filter->b[2]*lpf_filter->xk_2[2] - lpf_filter->a[1]*lpf_filter->yk_1[2] - lpf_filter->a[2]*lpf_filter->yk_2[2];
  // Tether tension
  lpf_filter->yk[3] = lpf_filter->b[0]*lpf_filter->xk[3] + lpf_filter->b[1]*lpf_filter->xk_1[3] + lpf_filter->b[2]*lpf_filter->xk_2[3] - lpf_filter->a[1]*lpf_filter->yk_1[3] - lpf_filter->a[2]*lpf_filter->yk_2[3];


  for (i=0; i<4 ; i++)
  {
    lpf_filter->xk_1[i] = lpf_filter->xk[i];
    lpf_filter->xk_2[i] = lpf_filter->xk_1[i];
    lpf_filter->yk_1[i] = lpf_filter->yk[i];
    lpf_filter->yk_2[i] = lpf_filter->yk_1[i];
  }

  // Filtered tether variables
  tether->az = lpf_filter->yk[0];
  tether->el = lpf_filter->yk[1];
  tether->len = lpf_filter->yk[2];
  tether->tension = lpf_filter->yk[3];
}
