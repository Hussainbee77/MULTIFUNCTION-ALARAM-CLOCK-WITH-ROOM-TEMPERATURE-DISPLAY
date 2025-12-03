#include<lpc214x.h>
#include"mini_adc.h"
#include"delay.h"
#include"types.h"
#include"pin_connect_block.h"
#include"pin_function_defines.h"
#include"adc_defines.h"
#include"defines.h"
/* ---ADC --- */
void Init_ADC(void)
{
AD0CR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
cfgportpinfunc(0,28,pin_func2);
}
void Read_ADC(u32 ChNo,u32*adcDVal,f32*eAR)
{
AD0CR&=0XFFFFFF00;
AD0CR|=1<<ChNo|1<<ADC_START_BIT;
delayUS(3);
while(((AD0GDR>>DONE_BIT)&1)==0);
AD0CR&=~(1<<ADC_START_BIT);
*adcDVal=((AD0GDR>>RESULT_BITS)&1023);
*eAR=(*adcDVal * (3.3/1023));
}
