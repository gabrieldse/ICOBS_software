//-----------------------------------------------------------
// main.c
// Author: Gabriel Oliveira
// Update: 04-04-2024
//-----------------------------------------------------------

#include "system.h"
#include "bsp.h"
#include <stdlib.h>

// static functions
static void timer_clock_cb(int);

void auto_bouncer(int *spritex, int *spritey, int spriteh, int spritew, int *xspeed, int *yspeed);
void wall_checker(int *spritex, int *spritey, int spriteh, int spritew);

// global variable
// Define the size of each sprite
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SPRITE_W_1 79 // width
#define SPRITE_H_1 79 // Height
#define SPRITE_W_2 78
#define SPRITE_H_2 78
#define SPRITE_W_3 34
#define SPRITE_H_3 34
#define SPRITE_W_4 34
#define SPRITE_H_4 34
#define SPRITE_W_5 34
#define SPRITE_H_5 34
#define SPRITE_W_6 24
#define SPRITE_H_6 24
#define SPRITE_W_7 20
#define SPRITE_H_7 15
// #define SPRITE_W_8 640
// #define SPRITE_H_8 480
// #define SPRITE_W_9 230
// #define SPRITE_H_9 175
// #define SPRITE_W_10 195
// #define SPRITE_H_10 175

int TIMER_FLAG = 0;
static void timer_clock_cb(int code)
{
	TIMER_FLAG = 1;
	((void)code);
}

// main function
int main(void)
{
	//srand(count);
	//rand();
	// arch initialization
	RSTCLK.GPIOAEN = 1;
	RSTCLK.GPIOBEN = 1;
	RSTCLK.GPIOCEN = 1;

	GPIOB.ODR = 0x0000;	  //  Define as an output
	GPIOB.MODER = 0xFFFF; // Define as ?????

	BSP_Button_Init();
	BSP_Switch_Init();

	// UART1 initialization
	UART1_Init(115200);
	UART1_Enable();
	IBEX_SET_INTERRUPT(IBEX_INT_UART1);
	IBEX_ENABLE_INTERRUPTS;
	myprintf("\n#####################\nDEMO\n#####################\n");
	set_timer_ms(1, timer_clock_cb, 0);

	MY_VGA.BACK = 0x0; // initial background color

	// sprites 3 initial position -------------------------
	MY_VGA.X3POS = SCREEN_WIDTH / 2;
	MY_VGA.Y3POS = SCREEN_HEIGHT / 2;
	int X3POS = MY_VGA.X3POS;
	int Y3POS = MY_VGA.Y3POS;
	int xspeed3 = 10;
	int yspeed3 = 3;

	// sprites 2 initial position -------------------------
	MY_VGA.X2POS = SCREEN_WIDTH - SPRITE_W_2 - 100;
	MY_VGA.Y2POS = SCREEN_HEIGHT / 2;
	int X2POS = MY_VGA.X2POS;
	int Y2POS = MY_VGA.Y2POS;
	int xspeed2 = 3;
	int yspeed2 = -3;

	// sprites 1 initial position -------------------------
	MY_VGA.X1POS = 100;
	MY_VGA.Y1POS = SCREEN_HEIGHT / 2;
	int X1POS = MY_VGA.X1POS;
	int Y1POS = MY_VGA.Y1POS;
	int xspeed1 = +3;
	int yspeed1 = -3;

	// sprites 4 initial position -------------------------
	MY_VGA.X4POS = 100;
	MY_VGA.Y4POS = SCREEN_HEIGHT / 2;
	int X4POS = MY_VGA.X4POS;
	int Y4POS = MY_VGA.Y4POS;
	int xspeed4 = +10;
	int yspeed4 = -10;

	// sprites 5 initial position -------------------------
	MY_VGA.X5POS = 100;
	MY_VGA.Y5POS = SCREEN_HEIGHT / 2;
	int X5POS = MY_VGA.X5POS;
	int Y5POS = MY_VGA.Y5POS;
	int xspeed5 = +3;
	int yspeed5 = -3;

	// sprites 6 initial position -------------------------
	MY_VGA.X6POS = 100;
	MY_VGA.Y6POS = SCREEN_HEIGHT / 2;
	int X6POS = MY_VGA.X6POS;
	int Y6POS = MY_VGA.Y6POS;
	int xspeed6 = -20;
	int yspeed6 = +20;

	// sprites 7 initial position -------------------------
	MY_VGA.X7POS = 100;
	MY_VGA.Y7POS = SCREEN_HEIGHT / 2;
	int X7POS = MY_VGA.X7POS;
	int Y7POS = MY_VGA.Y7POS;
	int xspeed7 = +20;
	int yspeed7 = -20;

	// sprites 8 initial position -------------------------
	// MY_VGA.X8POS = 100;
	// MY_VGA.Y8POS = SCREEN_HEIGHT / 2;
	// int X8POS = MY_VGA.X8POS;
	// int Y8POS = MY_VGA.Y8POS;
	// int xspeed8 = +3;
	// int yspeed8 = -3;

	// sprites 9 initial position -------------------------
	// MY_VGA.X9POS = 100;
	// MY_VGA.Y9POS = SCREEN_HEIGHT / 2;
	// int X9POS = MY_VGA.X9POS;
	// int Y9POS = MY_VGA.Y9POS;
	// int xspeed9 = +3;
	// int yspeed9 = -3;

	// sprites 10 initial position -------------------------
	// MY_VGA.X10POS = 100;
	// MY_VGA.Y10POS = SCREEN_HEIGHT / 2;
	// int X10POS = MY_VGA.X10POS;
	// int Y10POS = MY_VGA.Y10POS;
	// int xspeed10 = +3;
	// int yspeed10 = -3;

	int count = 0;

	// main loop
	while (1)
	{

		// main caracter control
		if (BTND)
			Y3POS += xspeed3;
		if (BTNU)
			Y3POS -= xspeed3;
		if (BTNL)
			X3POS -= xspeed3;
		if (BTNR)
			X3POS += xspeed3;
		wall_checker(&X3POS, &Y3POS, SPRITE_H_3, SPRITE_W_3);
		MY_VGA.X3POS = X3POS;
		MY_VGA.Y3POS = Y3POS;
		
		auto_bouncer(&X1POS, &Y1POS, SPRITE_H_1, SPRITE_W_1, &xspeed1, &yspeed1);
		MY_VGA.X1POS = X1POS;
		MY_VGA.Y1POS = Y1POS;
		auto_bouncer(&X2POS, &Y2POS, SPRITE_H_2, SPRITE_W_2, &xspeed2, &yspeed2);
		MY_VGA.X2POS = X2POS;
		MY_VGA.Y2POS = Y2POS;
		auto_bouncer(&X4POS, &Y4POS, SPRITE_H_4, SPRITE_W_4, &xspeed4, &yspeed4);
		MY_VGA.X4POS = X4POS;
		MY_VGA.Y4POS = Y4POS;
		auto_bouncer(&X5POS, &Y5POS, SPRITE_H_5, SPRITE_W_5, &xspeed5, &yspeed5);
		MY_VGA.X5POS = X5POS;
		MY_VGA.Y5POS = Y5POS;
		auto_bouncer(&X6POS, &Y6POS, SPRITE_H_6, SPRITE_W_6, &xspeed6, &yspeed6);
		MY_VGA.X6POS = X6POS;
		MY_VGA.Y6POS = Y6POS;
		auto_bouncer(&X7POS, &Y7POS, SPRITE_H_7, SPRITE_W_7, &xspeed7, &yspeed7);
		MY_VGA.X7POS = X7POS;
		MY_VGA.Y7POS = Y7POS;

		TIMER_FLAG = 0;
		delay_ms(10);

		count++;
		MY_PERIPH.REG4 = count / 30;
		MY_PERIPH.REG3 = MY_PERIPH.REG4 / 10;
		MY_PERIPH.REG2 = MY_PERIPH.REG3 / 10;
		MY_PERIPH.REG1 = MY_PERIPH.REG2 / 10;

		// PAUSE THE GAME WHEN PRESSED
		while (SW0)
		{
		}
	}
	return 0;
}

void Default_Handler(void)
{
	GPIOB.ODR = 0xFFFF;
}

// ----------------- GAME FUNCTIONS --------------------------

void auto_bouncer(int *spritex, int *spritey, int spriteh, int spritew, int *xspeed, int *yspeed)
{

	if (*spritex <= 0 || *spritex + spritew >= SCREEN_WIDTH)
	{
		*xspeed = -*xspeed;
	}

	if (*spritey <= 0 || *spritey + spriteh >= SCREEN_HEIGHT)
	{
		*yspeed = -*yspeed;
	}

	*spritex += *xspeed;
	*spritey += *yspeed;
}

void wall_checker(int *spritex, int *spritey, int spriteh, int spritew)
{

	if (*spritex <= 0)
	{
		*spritex = 0;
	}
	else if (*spritex + spritew >= SCREEN_WIDTH)
	{
		*spritex = SCREEN_WIDTH - spritew;
	}

	if (*spritey <= 0)
	{
		*spritey = 0;
	}
	else if (*spritey + spriteh >= SCREEN_HEIGHT)
	{
		*spritey = SCREEN_HEIGHT-spriteh;
	}
}

void rand_walk(int *spritex, int *spritey, int spriteh, int spritew)
{
	*spritex += rand()%32;
	*spritey += rand()%32;

}