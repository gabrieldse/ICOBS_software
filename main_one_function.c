//-----------------------------------------------------------
// main.c
// Author: Gabriel Oliveira
// Update: 04-04-2024
//-----------------------------------------------------------

#include "system.h"
#include "bsp.h"

// static functions
static void timer_clock_cb(int);

void auto_bouncer(volatile unsigned int *spritex, volatile unsigned int *spritey, int spriteh, int spritew, int xspeed, int yspeed);

// global variable
// Define the size of each sprite
#define SPRITE_W_1 95 // width
#define SPRITE_H_1 95 // Height
#define SPRITE_W_2 95
#define SPRITE_H_2 95
#define SPRITE_W_3 95
#define SPRITE_H_3 95
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
int TIMER_FLAG = 0;

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

	MY_VGA.X1POS = 100;
	MY_VGA.Y1POS = SCREEN_HEIGHT / 2;
	MY_VGA.X2POS = SCREEN_WIDTH - SPRITE_W_2 - 100;
	MY_VGA.Y2POS = SCREEN_HEIGHT / 2;
	MY_VGA.X3POS = SCREEN_WIDTH / 2;
	MY_VGA.Y3POS = SCREEN_HEIGHT / 2;

	// main loop
	while (1)
	{
		// auto_bouncer(int spritex,int spritey,int spriteh,int spritew,int xspeed,int yspeed)
		
		auto_bouncer(&(MY_VGA.X3POS), &(MY_VGA.X3POS), SPRITE_H_3, SPRITE_W_3, 10, 10);

		/*
			if (MY_VGA.X3POS == 0)
			dx = -3;
			else if (MY_VGA.X3POS + SPRITE_W_3> SCREEN_WIDTH)
			dx = 3;
			if (MY_VGA.Y3POS == 0)
			dy =3;
			else if (MY_VGA.Y3POS +SPRITE_H_3 > SCREEN_HEIGHT)
			dy = -3;
			MY_VGA.X3POS += dx;
			MY_VGA.Y3POS += dy;

		*/

		// LIMITE SUPERIOR YPOS  = 0
		// LIMITE INFERIOR YPOS = SCREEN_HEIGHT-SPRITE_H

		// LIMITE INICIO XPOS = 0
		// LIMITE FINAL XPOS =   SCREEN_WIDTH-SPRITE_W

		/** PLAYER 1 **/
		/* LOCALIZADO A  ESQUERDA  DA TELA USA OS SWITCH FINAIS*/
		// Verifica se pode mover e movimenta na direção parando nos limites da tela
		//  descomentar
		if (SW15 && (MY_VGA.Y1POS - 5 != 0) && !SW14)					  // Switch de fora sobe
			MY_VGA.Y1POS -= 5;											  // sobe
		else if (SW14 && (MY_VGA.Y1POS + 5 < SCREEN_HEIGHT - SPRITE_H_1)) // switch de dentro desce
			MY_VGA.Y1POS += 5;

		/** PLAYER 2 **/
		/* LOCALIZADO A  DIREITA  DA TELA USA OS SWITCH INICIAS*/
		// Verifica se pode mover e movimenta na direção parando nos limites da tela
		//  descomentar
		if (SW0 && (MY_VGA.Y2POS - 5 != 0) && !SW1)						 // Switch de fora sobe
			MY_VGA.Y2POS -= 5;											 // sobe
		else if (SW1 && (MY_VGA.Y2POS + 5 < SCREEN_HEIGHT - SPRITE_H_2)) // switch de dentro desce
			MY_VGA.Y2POS += 5;

		if (BTND)
			MY_VGA.BACK -= 10;
		if (BTNU)
			MY_VGA.BACK += 10;

		/*if (SW4)
			MY_VGA.X3POS += 3; // DIR FINAl
		if (SW5)
			MY_VGA.X3POS -= 3; // DIR INICIO/*

		/*do{


			if (SW0)
			{
			MY_VGA.X1POS ++;
			}
			if (SW1)
			{
			MY_VGA.X1POS --;
			}
			if (SW3)
			{
			MY_VGA.Y2POS ++;
			}
			if (SW4)
			{
			MY_VGA.Y2POS --;
			}

		}while(!TIMER_FLAG);
		*/
		// if (sameSpot(MY_VGA.X1POS,MY_VGA.X2POS,MY_VGA.Y1POS,MY_VGA.Y2POS))
		//	myprintf("\n ++++++++++++++++++++++++\nBATIIIIIIIIIIIIIII\n++++++++++++++++++\n");

		TIMER_FLAG = 0;
		delay_ms(10);
	}
	return 0;
}

void Default_Handler(void)
{
	GPIOB.ODR = 0xFFFF;
}

static void timer_clock_cb(int code)
{
	TIMER_FLAG = 1;
	((void)code);
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
			myprintf("%d\n",count);
			GPIOB.ODR = count;
		}
	*/

// ----------------- GAME FUNCTIONS --------------------------

void auto_bouncer(volatile unsigned int *spritex, volatile unsigned int *spritey, int spriteh, int spritew, int xspeed, int yspeed) {
    if (*spritex <= 0) {
        xspeed = -xspeed;
    }
    else if (*spritex + spritew >= SCREEN_WIDTH) {
        xspeed = -xspeed;
    }
    if (*spritey <= 0) {
        yspeed = -yspeed;
    }
    else if (*spritey + spriteh >= SCREEN_HEIGHT) {
        yspeed = -yspeed;
    }
	 
	myprintf("-------------------------------\n"); 
	myprintf("before X: %u\n", *spritex);
	myprintf("delta X: %d\n", xspeed);
    *spritex += xspeed;
    myprintf("after X: %u\n", *spritex);
	myprintf("-------------------------------\n"); 


	myprintf("before Y: %u\n", *spritey);
	myprintf("delta Y: %d\n", yspeed);
    *spritey += yspeed;
    myprintf("after Y: %u\n", *spritey);
	myprintf("-------------------------------\n"); 
}