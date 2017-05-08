#ifndef MAIN_H
#define MAIN_H

//INCLUDES DEFINITON OF 8051 HEADER FILE
#include "INCLUDES.H"
  
//DEFINE CONSTANT
#define TIMER1_TH1				50
#define TIMER1_TL1				0

#define TIMER0_TH0				150
#define TIMER0_TL0				150

#define MAX_SPEED				100
#define MIN_SPEED 				0

#define START					1
#define STOP					0

#define OUTPUT_PIN				0

#define ENABLE					1

//DEFINE PORTS/PINS											
#define ENABLE_PIN				P0_7
#define DC_MOTOR_ANODE			P0_6
#define DC_MOTOR_CATHODE		P0_5


#define SWITCH_PORT				P1

struct  {
	volatile int8u ON_OFF:1;
	volatile int8u CLOCK_ANTI:1;
}AppFlags;



//DEFINE PUSH BUTTON SWITCHES

//DEFINE MACROS
#define RotateClockwise()		DC_MOTOR_ANODE = 1; DC_MOTOR_CATHODE = 0
#define RotateAntiClockwise()	DC_MOTOR_ANODE = 0; DC_MOTOR_CATHODE = 1
#define StopMotor()				ENABLE_PIN = 0

#define StartProc()					TR1 = 1
#define StopProc()					TR1 = 0

//DEFINE USER DEFINED DATA TYPE
typedef unsigned char ubyte;

//FUNCTION PROTOTYPES
void main(void);
static void MainSystemInitialize(void);
static void MainDisplayProjectTitle(void);
static void	Timer0_init(void);
static unsigned char MainConvertToBinary(unsigned char Position);
static void Timer0_isr(void);
static void MainDisplayControls(void);
static void tmr1_init(void);
#endif
