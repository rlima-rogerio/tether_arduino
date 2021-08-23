//############################################################################
//
// File:      filter.h
// Version:   1.0 (mar/2020)
//            2.0 (may/2020)
//
// Description: Filtering macros, structs and prototype functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################


#ifndef __FILTER_H
#define __FILTER_H

#define LPF_BUTTER_DEN_A1         1.0000
#define LPF_BUTTER_DEN_A2         -1.5645
#define LPF_BUTTER_DEN_A3         0.6437
#define LPF_BUTTER_NUM_B1         0.0198
#define LPF_BUTTER_NUM_B2         0.0396
#define LPF_BUTTER_NUM_B3         0.0198
#define GRAVITY                   9.81    // Value acquired from sensos static
#define TOL                       1.0
#define NORM_INF                  (GRAVITY - TOL)
#define NORM_SUP                  (GRAVITY + TOL)


/* Filter Data Structure                                          */
/*y[k] = -a2*y[k-1] - a3*y[k-2] + b1*x[k] + b2*x[k-1] + b3*x[k-2] */
typedef struct struct_filter_t
{
  float a[3];     // a1, a2, a3: three bc/ it's a 3rd order filter
  float b[3];     // b1, b2, b3
  float yk[4];    // y[k] for azimuth, elevation, length, tension
  float yk_1[4];  // y[k-1] for azimuth, elevation, length, tension
  float yk_2[4];  // y[k-2] for for azimuth, elevation, length, tension
  float xk[4];    // x[k] for for azimuth, elevation, length, tension
  float xk_1[4];  // x[k-1] for for azimuth, elevation, length, tension
  float xk_2[4];  // x[k-2] for for azimuth, elevation, length, tension
}filter_t;


// Prototype Functions
void lpf_butter_init(struct_filter_t *lpf_filter);
void lpf_butter(struct_tether_t *tether, struct_filter_t *lpf_filter);

#endif
