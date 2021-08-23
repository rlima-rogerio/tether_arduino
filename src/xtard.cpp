//############################################################################
//
// File:      xtard.cpp
// Version:   1.0 (dec/2020)
//
// Description: Interface to communicate with external Arduino. Macros, 
//              structs and prototype functions.
//
//===========================================================================
// Author:  Rogerio Lima
// Place:   Morgantonw/WV
//############################################################################

#include <Arduino.h>
#include "ds.h"
#include "xtard.h"


/*******************************************************************************
* Function Name  : set_xtard_cmd
* Input          : None
* Output         : None
* Return         : udoo_cmd_t cmd
* Description    : Encodes the command to send to ext. Arduino via 2-bit comm.
*******************************************************************************/
xtard_cmd_t set_xtard_cmd(void)
{
  xtard_cmd_t cmd;

  cmd = (xtard_cmd_t)(ANALOG2BOOL(PIN_EXT_ARD_COMM_BIT0) | (ANALOG2BOOL(PIN_EXT_ARD_COMM_BIT1)<<1));
  
  return cmd;
}
