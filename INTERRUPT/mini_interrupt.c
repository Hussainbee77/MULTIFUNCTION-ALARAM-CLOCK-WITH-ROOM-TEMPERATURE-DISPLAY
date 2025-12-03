#include<lpc214x.h>
#include"mini_interrupt.h"
#include"types.h"
#include"interrupt_defines.h"
void Init_Interrupt(void)
{
//configure p0.3 as EINT1(function 3)
cfgportpinfunc(0,1,EINT0_0_1);
//Edge sensitive falling edge
VICIntEnable=1<<14;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
VICVectCntl0=(1<<5)|14;
VICVectAddr0=(u32)EINT1_ISR;
EXTMODE=1<<0;
}
/*ISR HANDLER */
void Menu(void);
void EINT1_ISR(void)__irq
{
Menu();
EXTINT = 1<<0;
VICVectAddr = 0;
}
