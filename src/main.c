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
int check_contact_boss(int *sprite1x, int *sprite1y, int sprite1h, int sprite1w, int *sprite2x, int *sprite2y, int sprite2h, int sprite2w);
void initial_pos();
void rand_walk(int *spritex, int *spritey, int spriteh, int spritew);
int check_contact_projectile(int *sprite3x, int *sprite3y, int sprite3h, int sprite3w,
							 int *sprite4x, int *sprite4y, int sprite4h, int sprite4w,
							 int *sprite5x, int *sprite5y, int sprite5h, int sprite5w,
							 int *sprite6x, int *sprite6y, int sprite6h, int sprite6w,
							 int *sprite7x, int *sprite7y, int sprite7h, int sprite7w);

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
	// srand(count);
	// rand();
	//  arch initialization
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
    // main caracter speed
	int xspeed3 = 5;

	int xspeed2 = 3;
	int yspeed2 = -3;

	int xspeed1 = +3;
	int yspeed1 = +3;

	int xspeed4 = -4;
	int yspeed4 = +4;

	int xspeed5 = -4;
	int yspeed5 = -4;
	
	int xspeed6 = -5;
	int yspeed6 = +5;

	int xspeed7 = +5;
	int yspeed7 = -5;

	// int X8POS = MY_VGA.X8POS;
	// int Y8POS = MY_VGA.Y8POS;
	// int xspeed8 = +3;
	// int yspeed8 = -3;

	// int X9POS = MY_VGA.X9POS;
	// int Y9POS = MY_VGA.Y9POS;
	// int xspeed9 = +3;
	// int yspeed9 = -3;

	// int X10POS = MY_VGA.X10POS;
	// int Y10POS = MY_VGA.Y10POS;
	// int xspeed10 = +3;
	// int yspeed10 = -3;

	initial_pos();

	// passes the inital position to the X3 variables
	int X3POS = MY_VGA.X3POS;
	int Y3POS = MY_VGA.Y3POS;
	int X2POS = MY_VGA.X2POS;
	int Y2POS = MY_VGA.Y2POS;
	int X1POS = MY_VGA.X1POS;
	int Y1POS = MY_VGA.Y1POS;
	int X4POS = MY_VGA.X4POS;
	int Y4POS = MY_VGA.Y4POS;
	int X5POS = MY_VGA.X5POS;
	int Y5POS = MY_VGA.Y5POS;
	int X6POS = MY_VGA.X6POS;
	int Y6POS = MY_VGA.Y6POS;
	int X7POS = MY_VGA.X7POS;
	int Y7POS = MY_VGA.Y7POS;

	// update positions on the hardware
	MY_VGA.X3POS = X3POS;
	MY_VGA.Y3POS = Y3POS;
	MY_VGA.X2POS = X2POS;
	MY_VGA.Y2POS = Y2POS;
	MY_VGA.X1POS = X1POS;
	MY_VGA.Y1POS = Y1POS;
	MY_VGA.X4POS = X4POS;
	MY_VGA.Y4POS = Y4POS;
	MY_VGA.X5POS = X5POS;
	MY_VGA.Y5POS = Y5POS;
	MY_VGA.X6POS = X6POS;
	MY_VGA.Y6POS = Y6POS;
	MY_VGA.X7POS = X7POS;
	MY_VGA.Y7POS = Y7POS;

	int count = 0;
	int contact_boss_flag = 0;
	int contact_projectile_flag = 0;
	int contact_boss_counter = 0;
	int contact_projectile_counter = 0;
	int level = 0;

	delay_ms(1000);
	// main loop
	while (1)
	{
		//every 10ms x 100 = 1s
		if( count >= 10){
			if((contact_boss_flag = check_contact_boss(&X3POS, &Y3POS, SPRITE_H_3, SPRITE_W_3, &X1POS, &Y1POS, SPRITE_H_1, SPRITE_W_1))){
				contact_boss_counter = contact_boss_counter + contact_boss_flag;
				MY_PERIPH.REG2 = contact_boss_counter % 10;
				MY_PERIPH.REG1 = (contact_boss_counter)/10 % 10;

				count = 0;

			}
		}

// Define constants for speed increments
#define SPEED_INCREMENT_1 1
#define SPEED_INCREMENT_2 1
#define SPEED_INCREMENT_3 2

if (contact_boss_counter == 60 && level == 2) {
    xspeed3 = 5;

    xspeed6 += (xspeed6 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    yspeed6 += (yspeed6 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    xspeed7 += (xspeed7 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    yspeed7 += (yspeed7 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    xspeed1 += (xspeed1 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    yspeed1 += (yspeed1 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    xspeed4 += (xspeed4 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    yspeed4 += (yspeed4 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    xspeed5 += (xspeed5 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
    yspeed5 += (yspeed5 < 0 ? -SPEED_INCREMENT_3 : SPEED_INCREMENT_3);
	level++;
}
else if (contact_boss_counter == 45 && level == 1) {
    xspeed3 = 5;

    xspeed6 += (xspeed6 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    yspeed6 += (yspeed6 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    xspeed7 += (xspeed7 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    yspeed7 += (yspeed7 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    xspeed1 += (xspeed1 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    yspeed1 += (yspeed1 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    xspeed4 += (xspeed4 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    yspeed4 += (yspeed4 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    xspeed5 += (xspeed5 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
    yspeed5 += (yspeed5 < 0 ? -SPEED_INCREMENT_2 : SPEED_INCREMENT_2);
	level++;
}
else if (contact_boss_counter == 15 && level == 0) {
    xspeed3 = 5;

    xspeed6 += (xspeed6 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    yspeed6 += (yspeed6 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    xspeed7 += (xspeed7 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    yspeed7 += (yspeed7 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    xspeed1 += (xspeed1 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    yspeed1 += (yspeed1 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    xspeed4 += (xspeed4 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    yspeed4 += (yspeed4 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    xspeed5 += (xspeed5 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
    yspeed5 += (yspeed5 < 0 ? -SPEED_INCREMENT_1 : SPEED_INCREMENT_1);
	level++;
}

		
		contact_projectile_flag = check_contact_projectile(&X3POS, &Y3POS, SPRITE_H_3, SPRITE_W_3,
														   &X4POS, &Y4POS, SPRITE_H_4, SPRITE_W_4,
														   &X5POS, &Y5POS, SPRITE_H_5, SPRITE_W_5,
														   &X6POS, &Y6POS, SPRITE_H_6, SPRITE_W_6,
														   &X7POS, &Y7POS, SPRITE_H_7, SPRITE_W_7);
		
		contact_projectile_counter = contact_projectile_counter + contact_projectile_flag;

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

		// Increaseas the position on the bounce direction
		auto_bouncer(&X1POS, &Y1POS, SPRITE_H_1, SPRITE_W_1, &xspeed1, &yspeed1);
		auto_bouncer(&X2POS, &Y2POS, SPRITE_H_2, SPRITE_W_2, &xspeed2, &yspeed2);
		auto_bouncer(&X4POS, &Y4POS, SPRITE_H_4, SPRITE_W_4, &xspeed4, &yspeed4);
		auto_bouncer(&X5POS, &Y5POS, SPRITE_H_5, SPRITE_W_5, &xspeed5, &yspeed5);
		auto_bouncer(&X6POS, &Y6POS, SPRITE_H_6, SPRITE_W_6, &xspeed6, &yspeed6);
		auto_bouncer(&X7POS, &Y7POS, SPRITE_H_7, SPRITE_W_7, &xspeed7, &yspeed7);

		TIMER_FLAG = 0;
		delay_ms(10);

		count++;

        // - lifes
		MY_PERIPH.REG4 = contact_projectile_counter;
		//MY_PERIPH.REG3 = MY_PERIPH.REG4 % 10;

		// PAUSE THE GAME WHEN PRESSED
		while (SW0)
		{
		}
		// initial pos
		if (contact_projectile_flag)
		{
			X1POS = SCREEN_WIDTH / 2 - SPRITE_W_1 / 2;
			Y1POS = SCREEN_HEIGHT / 2 - SPRITE_H_1 / 2;

			// main caracter
			X3POS = SCREEN_WIDTH / 2 - SPRITE_W_3 / 2;
			Y3POS = SCREEN_HEIGHT - SPRITE_H_3;

			X4POS = SCREEN_WIDTH / 2 - SPRITE_W_4 / 2;
			Y4POS = SCREEN_HEIGHT / 2 - SPRITE_H_4 / 2;

			X5POS = SCREEN_WIDTH / 2 - SPRITE_W_5 / 2;
			Y5POS = SCREEN_HEIGHT / 2 - SPRITE_H_5 / 2;

			X6POS = SCREEN_WIDTH / 2 - SPRITE_W_6 / 2;
			Y6POS = SCREEN_HEIGHT / 2 - SPRITE_H_6 / 2;

			X7POS = SCREEN_WIDTH / 2 - SPRITE_W_7 / 2;
			Y7POS = SCREEN_HEIGHT / 2 - SPRITE_H_7 / 2;

			// out of the screen
			X2POS = SCREEN_WIDTH + SPRITE_W_2;
			Y2POS = SCREEN_HEIGHT + SPRITE_H_2;
		}

///////// LOSER SCREEN --------------------------------------------------------------
		if (contact_projectile_counter >= 3){
		// at the center
		X1POS = SCREEN_WIDTH / 2 - SPRITE_W_1 / 2;
        Y1POS = SCREEN_HEIGHT / 2 - SPRITE_H_1 / 2;
		
		//out of the screen
		X2POS = SCREEN_WIDTH + SPRITE_W_2;
		Y2POS = SCREEN_WIDTH + SPRITE_W_2;

		// main caracter at center lower part
		X3POS = SCREEN_WIDTH / 2 - SPRITE_W_3 / 2;
		Y3POS = SCREEN_HEIGHT - SPRITE_H_3 - 100 ;
        
		//out of the screen
		X4POS = SCREEN_WIDTH + SPRITE_W_2;
		Y4POS = SCREEN_WIDTH + SPRITE_W_2;

		X5POS = SCREEN_WIDTH + SPRITE_W_2;
		Y5POS = SCREEN_WIDTH + SPRITE_W_2;

		X6POS = SCREEN_WIDTH + SPRITE_W_2;
		Y6POS = SCREEN_WIDTH + SPRITE_W_2;

		X7POS = SCREEN_WIDTH + SPRITE_W_2;
		Y7POS = SCREEN_WIDTH + SPRITE_W_2;         
		}

///////// WIN SCREEN --------------------------------------------------------------

//When the score gets to 90
		if ((contact_boss_counter) >= 10){
		// at the center
		X2POS = SCREEN_WIDTH / 2 - SPRITE_W_1 / 2;
        Y2POS = SCREEN_HEIGHT / 2 - SPRITE_H_1 / 2;
		
		//out of the screen
		X1POS = SCREEN_WIDTH + SPRITE_W_2;
		Y1POS = SCREEN_WIDTH + SPRITE_W_2;

		// main caracter at center lower part
		X3POS = SCREEN_WIDTH / 2 - SPRITE_W_3 / 2;
		Y3POS = SCREEN_HEIGHT - SPRITE_H_3 - 100;

		X4POS = SCREEN_WIDTH + SPRITE_W_2;
		Y4POS = SCREEN_WIDTH + SPRITE_W_2;

		X5POS = SCREEN_WIDTH + SPRITE_W_2;
		Y5POS = SCREEN_WIDTH + SPRITE_W_2;

		X6POS = SCREEN_WIDTH + SPRITE_W_2;
		Y6POS = SCREEN_WIDTH + SPRITE_W_2;

		X7POS = SCREEN_WIDTH + SPRITE_W_2;
		Y7POS = SCREEN_WIDTH + SPRITE_W_2;         
		}

 if(contact_projectile_flag)
    initial_pos();

// ---------------------------------------------------------- Update the position to the hardware ---------------
		MY_VGA.X3POS = X3POS;
		MY_VGA.Y3POS = Y3POS;
		MY_VGA.X2POS = X2POS;
		MY_VGA.Y2POS = Y2POS;
		MY_VGA.X1POS = X1POS;
		MY_VGA.Y1POS = Y1POS;
		MY_VGA.X4POS = X4POS;
		MY_VGA.Y4POS = Y4POS;
		MY_VGA.X5POS = X5POS;
		MY_VGA.Y5POS = Y5POS;
		MY_VGA.X6POS = X6POS;
		MY_VGA.Y6POS = Y6POS;
		MY_VGA.X7POS = X7POS;
		MY_VGA.Y7POS = Y7POS;
	}
	return 0;
};

// ---------------------------------------------------------------------------------------------

void Default_Handler(void)
{
	GPIOB.ODR = 0xFFFF;
};

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
};

/*void auto_bouncer(int *bossx, int *bossy, int *shot1x, int *shot1y, int *shot2x, int *shot2y)
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
};*/

/*void rand_walk(int *spritex, int *spritey, int spriteh, int spritew)
{
	//int xspeed = rand()%32;
	//int yspeed = rand()%32;
	if (*spritex <= 0 || *spritex + spritew >= SCREEN_WIDTH)
	{
		xspeed = -xspeed;
	}

	if (*spritey <= 0 || *spritey + spriteh >= SCREEN_HEIGHT)
	{
		yspeed = -yspeed;
	}

	*spritex += xspeed;
	*spritey += yspeed;
};*/

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
		*spritey = SCREEN_HEIGHT - spriteh;
	}
};

int check_contact_boss(int *sprite1x, int *sprite1y, int sprite1h, int sprite1w, int *sprite2x, int *sprite2y, int sprite2h, int sprite2w)
{
	int contact_flag = 0;
	int contact_x = 0;
	int contact_y = 0;

	if (*sprite1x >= *sprite2x && *sprite1x <= *sprite2x + sprite2w)
		contact_x = 1;
	if (*sprite2x >= *sprite1x && *sprite2x <= *sprite1x + sprite1w)
		contact_x = 1;

	if (*sprite1y >= *sprite2y && *sprite1y <= *sprite2y + sprite2h)
		contact_y = 1;
	if (*sprite2y >= *sprite1y && *sprite2y <= *sprite1y + sprite1h)
		contact_y = 1;

	if (contact_x && contact_y)
		contact_flag = 1;

	return contact_flag;
};

int check_contact_projectile(int *sprite3x, int *sprite3y, int sprite3h, int sprite3w,
							 int *sprite4x, int *sprite4y, int sprite4h, int sprite4w,
							 int *sprite5x, int *sprite5y, int sprite5h, int sprite5w,
							 int *sprite6x, int *sprite6y, int sprite6h, int sprite6w,
							 int *sprite7x, int *sprite7y, int sprite7h, int sprite7w)
{
	int contact_flag = 0;

	if ((*sprite3x >= *sprite4x && *sprite3x <= *sprite4x + sprite4w) && (*sprite3y >= *sprite4y && *sprite3y <= *sprite4y + sprite4h))
		contact_flag = 1;

	if ((*sprite4x >= *sprite3x && *sprite4x <= *sprite3x + sprite3w) && (*sprite4y >= *sprite3y && *sprite4y <= *sprite3y + sprite3h))
		contact_flag = 1;

	if ((*sprite3x >= *sprite5x && *sprite3x <= *sprite5x + sprite5w) && (*sprite3y >= *sprite5y && *sprite3y <= *sprite5y + sprite5h))
		contact_flag = 1;

	if ((*sprite5x >= *sprite3x && *sprite5x <= *sprite3x + sprite3w) && (*sprite5y >= *sprite3y && *sprite5y <= *sprite3y + sprite3h))
		contact_flag = 1;

	if ((*sprite3x >= *sprite6x && *sprite3x <= *sprite6x + sprite6w) && (*sprite3y >= *sprite6y && *sprite3y <= *sprite6y + sprite6h))
		contact_flag = 1;

	if ((*sprite6x >= *sprite3x && *sprite6x <= *sprite3x + sprite3w) && (*sprite6y >= *sprite3y && *sprite6y <= *sprite3y + sprite3h))
		contact_flag = 1;

	if ((*sprite3x >= *sprite7x && *sprite3x <= *sprite7x + sprite7w) && (*sprite3y >= *sprite7y && *sprite3y <= *sprite7y + sprite7h))
		contact_flag = 1;

	if ((*sprite7x >= *sprite3x && *sprite7x <= *sprite3x + sprite3w) && (*sprite7y >= *sprite3y && *sprite7y <= *sprite3y + sprite3h))
		contact_flag = 1;

	return contact_flag;
};

// ----------------------------------------------------------------------------------------INITIAL POS
void initial_pos()
{
	MY_VGA.X1POS = SCREEN_WIDTH / 2 - SPRITE_W_1 / 2;
	MY_VGA.Y1POS = SCREEN_HEIGHT / 2 - SPRITE_H_1 / 2;

	// main caracter
	MY_VGA.X3POS = SCREEN_WIDTH / 2 - SPRITE_W_3 / 2;
	MY_VGA.Y3POS = SCREEN_HEIGHT - SPRITE_H_3;

	MY_VGA.X4POS = SCREEN_WIDTH / 2 - SPRITE_W_4 / 2;
	MY_VGA.Y4POS = SCREEN_HEIGHT / 2 - SPRITE_H_4 / 2;

	MY_VGA.X5POS = SCREEN_WIDTH / 2 - SPRITE_W_5 / 2;
	MY_VGA.Y5POS = SCREEN_HEIGHT / 2 - SPRITE_H_5 / 2;

	MY_VGA.X6POS = SCREEN_WIDTH / 2 - SPRITE_W_6 / 2;
	MY_VGA.Y6POS = SCREEN_HEIGHT / 2 - SPRITE_H_6 / 2;

	MY_VGA.X7POS = SCREEN_WIDTH / 2 - SPRITE_W_7 / 2;
	MY_VGA.Y7POS = SCREEN_HEIGHT / 2 - SPRITE_H_7 / 2;

	// out of the screen
	MY_VGA.X2POS = SCREEN_WIDTH + SPRITE_W_2;
	MY_VGA.Y2POS = SCREEN_HEIGHT + SPRITE_H_2;

	// MY_VGA.X8POS = 100;
	// MY_VGA.Y8POS = SCREEN_HEIGHT / 2;

	// MY_VGA.X9POS = 100;
	// MY_VGA.Y9POS = SCREEN_HEIGHT / 2;

	// MY_VGA.X10POS = 100;
	// MY_VGA.Y10POS = SCREEN_HEIGHT / 2;
};