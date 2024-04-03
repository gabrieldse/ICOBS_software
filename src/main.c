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
// main.c
// Author: Soriano Theo
// Update: 23-09-2020
//-----------------------------------------------------------
#include "system.h"

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

//Define the size of each sprite
#define SPRITE_W_1 95 // width
#define SPRITE_H_1 95 // Height

#define SPRITE_W_2 95
#define SPRITE_H_2 95

#define SPRITE_W_3 95
#define SPRITE_H_3 95

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int TIMER_FLAG = 0;

static void timer_clock_cb(int code)
{
	TIMER_FLAG=1;
	((void)code);
}

int main(void)
{
	RSTCLK.GPIOAEN = 1;
	RSTCLK.GPIOBEN = 1;
	RSTCLK.GPIOCEN = 1;

	GPIOB.ODR = 0x0000; //  Define as an output
	GPIOB.MODER = 0xFFFF; // Define as ?????

    _BTNU_MODE = GPIO_MODE_INPUT;
	_BTNL_MODE = GPIO_MODE_INPUT;
	_BTNR_MODE = GPIO_MODE_INPUT;
	_BTND_MODE = GPIO_MODE_INPUT;

	_SW0_MODE = GPIO_MODE_INPUT;
	_SW1_MODE = GPIO_MODE_INPUT;
	_SW2_MODE = GPIO_MODE_INPUT;
	_SW3_MODE = GPIO_MODE_INPUT;
	_SW4_MODE = GPIO_MODE_INPUT;
	_SW5_MODE = GPIO_MODE_INPUT;
	_SW6_MODE = GPIO_MODE_INPUT;
	_SW7_MODE = GPIO_MODE_INPUT;
	_SW8_MODE = GPIO_MODE_INPUT;
	_SW9_MODE = GPIO_MODE_INPUT;
	_SW10_MODE = GPIO_MODE_INPUT;
	_SW11_MODE = GPIO_MODE_INPUT;
	_SW12_MODE = GPIO_MODE_INPUT;
	_SW13_MODE = GPIO_MODE_INPUT;
	_SW14_MODE = GPIO_MODE_INPUT;
	_SW15_MODE = GPIO_MODE_INPUT;

	// UART1 initialization
	UART1_Init(115200);
	UART1_Enable();
	IBEX_SET_INTERRUPT(IBEX_INT_UART1);

	IBEX_ENABLE_INTERRUPTS;

	myprintf("\n#####################\nDEMO\n#####################\n");

	set_timer_ms(1, timer_clock_cb, 0);


	//Define a cor inicial do fundo
	MY_VGA.BACK =  0xFFFFFF;
	// Defini a posição inicial dos sprites
	MY_VGA.X1POS = 100;
	MY_VGA.Y1POS = SCREEN_HEIGHT/2;
	MY_VGA.X2POS = SCREEN_WIDTH-SPRITE_W_2-100;
	MY_VGA.Y2POS = SCREEN_HEIGHT/2;
	MY_VGA.X3POS = SCREEN_WIDTH/2;
	MY_VGA.Y3POS = SCREEN_HEIGHT/2;
	int8_t dx=3;
	int8_t dy=3;

	while(1) {

	/**BOLA - MOVIMENTO AUTOMÁTICO DENTRO DA TELA**/
	//Verifica os limites da tela
	//NÃO RESPEITA OS LIMITES LATERAIS
	
	if (MY_VGA.X3POS == 0) //Limite do inicio
	dx = 3; //DIR FINAl
	else if (MY_VGA.X3POS + SPRITE_W_3>= SCREEN_WIDTH) //limite do final
	dx =-3;// DIR INICIO
	if (MY_VGA.Y3POS ==0)
	dy =5;
	else if (MY_VGA.Y3POS +SPRITE_H_3 >=SCREEN_HEIGHT-1)
	dy = -5;
	MY_VGA.X3POS += dx;
	MY_VGA.Y3POS += dy;
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

//LIMITE INICIO XPOS = 0
//LIMITE FINAL XPOS =   SCREEN_WIDTH-SPRITE_W

	/** PLAYER 1 **/
	/* LOCALIZADO A  ESQUERDA  DA TELA USA OS SWITCH FINAIS*/
	//Verifica se pode mover e movimenta na direção parando nos limites da tela
	// descomentar
	if (SW15 && (MY_VGA.Y1POS-5 != 0)&& !SW14) //Switch de fora sobe
	MY_VGA.Y1POS -= 5; //sobe
	else if (SW14 && (MY_VGA.Y1POS+5 < SCREEN_HEIGHT-SPRITE_H_1)) // switch de dentro desce
	MY_VGA.Y1POS += 5;

	/** PLAYER 2 **/
	/* LOCALIZADO A  DIREITA  DA TELA USA OS SWITCH INICIAS*/
	//Verifica se pode mover e movimenta na direção parando nos limites da tela
	// descomentar
	if (SW0 && (MY_VGA.Y2POS-5 != 0)&& !SW1) //Switch de fora sobe
	MY_VGA.Y2POS -= 5; //sobe
	else if (SW1 && (MY_VGA.Y2POS+5 < SCREEN_HEIGHT-SPRITE_H_2)) // switch de dentro desce
	MY_VGA.Y2POS += 5;
	
	 
	if(BTND)
	MY_VGA.BACK -=10;
	if(BTNU)
	MY_VGA.BACK +=10;
	
	if (SW4)
	MY_VGA.X3POS +=3; //DIR FINAl
	if (SW5)
	MY_VGA.X3POS -=3;// DIR INICIO
			



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
	//if (sameSpot(MY_VGA.X1POS,MY_VGA.X2POS,MY_VGA.Y1POS,MY_VGA.Y2POS))
	//	myprintf("\n ++++++++++++++++++++++++\nBATIIIIIIIIIIIIIII\n++++++++++++++++++\n");

		TIMER_FLAG = 0;
		delay_ms(10);
		
	}
	return 0;
}

void Default_Handler(void){
	GPIOB.ODR = 0xFFFF;
}

//Gerenciador de colisão
/**
 * A posição conta do canto superior esquerdo da imagem, então os sprites vão colidir se:
 * PY1 == PY2+ H2 
 * PX1 == PX2 + W2
 * PY2 == PY1+ H1
 * PX2 == PX1 + W1
 * 


		/*do{
			/*if(BTNU){dx=1;
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