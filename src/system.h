// ##########################################################
// ##########################################################
// ##    __    ______   ______   .______        _______.   ##
// ##   |  |  /      | /  __  \  |   _  \      /       |   ##
// ##   |  | |  ,----'|  |  |  | |  |_)  |    |   (----`   ##
// ##   |  | |  |     |  |  |  | |   _  <      \   \       ##
// ##   |  | |  `----.|  `--'  | |  |_)  | .----)   |      ##
// ##   |__|  \______| \______/  |______/  |_______/       ##
// ##                                                      ##
// ##########################################################
// ##########################################################
//-----------------------------------------------------------
// system.h
// Author: Soriano Theo
// Update: 23-09-2020
//-----------------------------------------------------------

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

// Architecture definition
#include <arch.h>
#include <ibex_csr.h>

// UART1 configuration
#define UART1_TXBUFFERSIZE      128
#define UART1_RXBUFFERSIZE      32

// ----------------------------------------------------------------------------
// Application headers
#include <ascii.h>
#include <ansi.h>
#include <print.h>
#include <types.h>
#include <uart.h>
#include <timer.h>

// Printf-like function (does not support all formats...)
#define myprintf(...)             print(UART1_Write, __VA_ARGS__)


//-------------------------------------------------------------------------------
// Hadware definitions
// Buttons
#define _BTNU_MODE  GPIOC.MODEbits.P0
#define BTNU        GPIOC.IDRbits.P0

#define _BTNL_MODE  GPIOC.MODEbits.P1
#define BTNL        GPIOC.IDRbits.P1

#define _BTNR_MODE  GPIOC.MODEbits.P2
#define BTNR        GPIOC.IDRbits.P2

#define _BTND_MODE  GPIOC.MODEbits.P3
#define BTND        GPIOC.IDRbits.P3

//Switch
#define _SW0_MODE  GPIOA.MODEbits.P0
#define SW0        GPIOA.IDRbits.P0

#define _SW1_MODE  GPIOA.MODEbits.P1
#define SW1        GPIOA.IDRbits.P1

#define _SW2_MODE  GPIOA.MODEbits.P2
#define SW2        GPIOA.IDRbits.P2

#define _SW3_MODE  GPIOA.MODEbits.P3
#define SW3  		GPIOA.MODEbits.P3  

#define _SW4_MODE  GPIOA.MODEbits.P4
#define SW4        GPIOA.IDRbits.P4

#define _SW5_MODE  GPIOA.MODEbits.P5
#define SW5        GPIOA.IDRbits.P5

#define _SW6_MODE  GPIOA.MODEbits.P6
#define SW6        GPIOA.IDRbits.P6

#define _SW7_MODE  GPIOA.MODEbits.P7
#define SW7        GPIOA.IDRbits.P7

#define _SW8_MODE  GPIOA.MODEbits.P8
#define SW8        GPIOA.IDRbits.P8

#define _SW9_MODE  GPIOA.MODEbits.P9
#define SW9        GPIOA.IDRbits.P9

#define _SW10_MODE  GPIOA.MODEbits.P10
#define SW10        GPIOA.IDRbits.P10

#define _SW11_MODE  GPIOA.MODEbits.P11
#define SW11        GPIOA.IDRbits.P11

#define _SW12_MODE  GPIOA.MODEbits.P12
#define SW12        GPIOA.IDRbits.P12

#define _SW13_MODE  GPIOA.MODEbits.P13
#define SW13        GPIOA.IDRbits.P13

#define _SW14_MODE  GPIOA.MODEbits.P14
#define SW14        GPIOA.IDRbits.P14

#define _SW15_MODE  GPIOA.MODEbits.P15
#define SW15        GPIOA.IDRbits.P15



#endif
