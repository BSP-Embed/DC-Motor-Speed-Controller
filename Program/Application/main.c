//INCLUDE MAIN HEADER FILE
#include"main.h"

//GLOBAL VARIABLES


unsigned char count = 0;
unsigned char PercentageOfModulation = 50;
unsigned char seccount = 0;

extern int8u lcdptr;

//MAIN FUNCTION BEGINS
void main(void)
{
	MainSystemInitialize();
	AppFlags.ON_OFF = LOW;
			
	while(1) {
	
		switch(SWITCH_PORT & 0x0f) {
			case 0X0E:
					beep(1,150);
					AppFlags.ON_OFF = ~AppFlags.ON_OFF;
				 	if (AppFlags.ON_OFF == HIGH)	 {
						lcdptr = 0x85;
						lcdws("ON ");
						TR0 = 1;	
					} else {
						TR0 = 0;
						StopMotor();
						lcdptr = 0x85;
						lcdws("OFF");
					}
					
					while ((SWITCH_PORT & 0x0f) == 0X0E);

					break;

			case 0X0D:
					
					if (AppFlags.ON_OFF == LOW) {
						beep(1,150);
						AppFlags.CLOCK_ANTI = ~AppFlags.CLOCK_ANTI;
					
						if (AppFlags.CLOCK_ANTI == HIGH)  {
							lcdptr = 0xCA;
				   			lcdws("ANTICK");
							RotateClockwise();
						} else {			
							lcdptr = 0xCA;
				   			lcdws("CLOCK ");
							RotateAntiClockwise();
						}
					}
			  		break;

			case 0x0B:
					if (AppFlags.ON_OFF == LOW) {
						beep(1,150);
						if (PercentageOfModulation < 100)  {
							PercentageOfModulation += 10;
							lcdwint(0x8d,PercentageOfModulation);
						}
					}
					break;

			case 0X07:
					if (AppFlags.ON_OFF == LOW) {
						beep(1,150);
						if (PercentageOfModulation > 10)  {
							PercentageOfModulation -= 10;
							lcdwint(0x8d,PercentageOfModulation);
						}
					}
					break;

			default:
					break;
		}		
	}
}
static void MainSystemInitialize(void)
{
	
    DC_MOTOR_ANODE           = OUTPUT_PIN;
	DC_MOTOR_CATHODE         = OUTPUT_PIN;
	ENABLE_PIN               = OUTPUT_PIN;
	
	beep(2,150);

	lcdinit();
	MainDisplayProjectTitle();
	MainDisplayControls();

	tmr1_init();
	Timer0_init();

	beep(1,150);
	RotateAntiClockwise();		/* Inital Motor Direction */
	StartProc();

}
static void MainDisplayControls(void)
{
	lcdclr();
	lcdws("MOTOROFF PWM-50");
	lcdr2();
	lcdws("DIRECTION-CLOCK");
}
static void MainDisplayProjectTitle(void)
{
	lcdclr();
	lcdws(" BIDIRECTION DC");
	lcdr2();
	lcdws("MOTOR SPEED CO'L");

	dlyms(1000);
}
static void Timer0_init(void)
{
	TMOD &= 0xf0;
	TMOD |= 0X02;
	TH0 = TIMER0_TH0;
	TL0 = TIMER0_TL0;
	EA = 1;
	ET0 = 1;

}
//PWM BASED ON TIMER
static void Timer0_isr(void) interrupt 1 using 0
{
	if(count++ == 100)
		count = 0;

	if(count < PercentageOfModulation)
		ENABLE_PIN = 1;
	else
		ENABLE_PIN = 0;
}
static void tmr1_init(void)
{
	TMOD = TMOD & 0x0f | 0x10;		/* TMR1 in mode1*/
	TH1 = 0x4B;
	TL1 = 0xFD;
	EA = ET1 = 1;
} 

static void tmr1ISR() interrupt 3 using 0
{
	static int8u i,j;

	TH1 = 0x4B;
	TL1 = 0xFD;
		
	if (++i >= 2) {
		i = 0;
		if (++j >= 50) j = 0;
		switch(j) {
			case 0: case 2: ledon();  break;
			case 1: case 3: ledoff(); break;
		}

	
	}
} 
	   


