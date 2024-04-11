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
   volatile unsigned int X4POS;
   volatile unsigned int Y4POS;
   volatile unsigned int X5POS;
   volatile unsigned int Y5POS;
   volatile unsigned int X6POS;
   volatile unsigned int Y6POS;
   volatile unsigned int X7POS;
   volatile unsigned int Y7POS;
   
   //volatile unsigned int X8POS; volatile unsigned int Y8POS;
   //volatile unsigned int X9POS; volatile unsigned int Y9POS;
   //volatile unsigned int X10POS; volatile unsigned int Y10POS; //newimage
}VGA_PERIPH_t;

#endif