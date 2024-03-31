#ifndef _ARCH_VGA_H_
#define _ARCH_VGA_H_

typedef struct 
{
   volatile unsigned int BACK;
   volatile unsigned int X1POS;
   volatile unsigned int Y1POS;
   volatile unsigned int X2POS;
   volatile unsigned int Y2POS;
   volatile unsigned int X3POS;
   volatile unsigned int Y3POS;
}VGA_PERIPH_t;

#endif