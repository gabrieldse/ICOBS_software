//-----------------------------------------------------------
// main.c
// Author: Gabriel Oliveira
// Update: 04-04-2024
//-----------------------------------------------------------

#include "system.h"
#include "bsp.h"

// static functions
static void timer_clock_cb(int);

void auto_bouncer(int *spritex, int *spritey, int spriteh, int spritew, int *xspeed, int *yspeed);

// global variable
// Define the size of each sprite
#define SPRITE_W_1 79 // width
#define SPRITE_H_1 79 // Height
#define SPRITE_W_2 78
#define SPRITE_H_2 78
#define SPRITE_W_3 34
#define SPRITE_H_3 34
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int TIMER_FLAG = 0;
static void timer_clock_cb(int code)
{
	TIMER_FLAG = 1;
	((void)code);
}

// main function
int main(void)
{
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

	MY_VGA.BACK = 0xFFFFFF; // initial background color

	// sprites initial position
	MY_VGA.X3POS = SCREEN_WIDTH / 2;
	MY_VGA.Y3POS = SCREEN_HEIGHT / 2;

	int X3POS = MY_VGA.X3POS;
	int Y3POS = MY_VGA.Y3POS;
	int xspeed = 3;
	int yspeed = 3;

	MY_VGA.X2POS = SCREEN_WIDTH - SPRITE_W_2 - 100;
	MY_VGA.Y2POS = SCREEN_HEIGHT / 2;
	int X2POS = MY_VGA.X2POS;
	int Y2POS = MY_VGA.Y2POS;
	int xspeed2 = 3;
	int yspeed2 = -3;

	MY_VGA.X1POS = 100;
	MY_VGA.Y1POS = SCREEN_HEIGHT / 2;
	int X1POS = MY_VGA.X1POS;
	int Y1POS = MY_VGA.Y1POS;
	int xspeed1 = +3;
	int yspeed1 = -3;

	// main loop
	while (1)
	{
		//
		auto_bouncer(&X3POS, &Y3POS, SPRITE_H_3, SPRITE_W_3, &xspeed, &yspeed);
		MY_VGA.X3POS = X3POS;
		MY_VGA.Y3POS = Y3POS;
		auto_bouncer(&X2POS, &Y2POS, SPRITE_H_2, SPRITE_W_2, &xspeed2, &yspeed2);
		MY_VGA.X2POS = X2POS;
		MY_VGA.Y2POS = Y2POS;
		auto_bouncer(&X1POS, &Y1POS, SPRITE_H_1, SPRITE_W_1, &xspeed1, &yspeed1);
		// delay_ms(3);
		// updates positons modified by the auto_bouncer to the VGA

		MY_VGA.X1POS = X1POS;
		MY_VGA.Y1POS = Y1POS;

		/** PLAYER 1 **/
		if (SW15 && (MY_VGA.Y1POS - 5 != 0) && !SW14)					  // Switch de fora sobe
			MY_VGA.Y1POS -= 5;											  // sobe
		else if (SW14 && (MY_VGA.Y1POS + 5 < SCREEN_HEIGHT - SPRITE_H_1)) // switch de dentro desce
			MY_VGA.Y1POS += 5;

		/** PLAYER 2 **/
		/* LOCALIZADO A  DIREITA  DA TELA USA OS SWITCH INICIAS*/
		// Verifica se pode mover e movimenta na direção parando nos limites da tela

		if (SW0 && (MY_VGA.Y2POS - 5 != 0) && !SW1)						 // Switch de fora sobe
			MY_VGA.Y2POS -= 5;											 // sobe
		else if (SW1 && (MY_VGA.Y2POS + 5 < SCREEN_HEIGHT - SPRITE_H_2)) // switch de dentro desce
			MY_VGA.Y2POS += 5;

		if (BTND)
			MY_VGA.BACK -= 10;
		if (BTNU)
			MY_VGA.BACK += 10;

		TIMER_FLAG = 0;
		delay_ms(10);
	}
	return 0;
}

void Default_Handler(void)
{
	GPIOB.ODR = 0xFFFF;
}

// Gerenciador de colisão
/**
 * A posição conta do canto superior esquerdo da imagem, então os sprites vão colidir se:
 * PY1 == PY2+ H2
 * PX1 == PX2 + W2
 * PY2 == PY1+ H1
 * PX2 == PX1 + W1
 *


		do{
			if(BTNU){dx=1;
			}
			if(BTND){dx=-1;}
			if(BTNL){dx=0;}
			if(BTNR){
				count = 0;
				last_count = -1;

			}

		}while(!TIMER_FLAG);


		TIMER_FLAG = 0;
		last_count = count;
		count = count+dx;
		if(count!=last_count){
			mymyprintf("%d\n",count);
			GPIOB.ODR = count;
		}
	*/

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
