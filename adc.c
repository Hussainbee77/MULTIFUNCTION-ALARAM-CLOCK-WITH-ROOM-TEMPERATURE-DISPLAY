#include<lpc21XX.h>
#include"types.h"
#include"delay.h"
#include"pin_connect_block.h"
#include"pin_function_defines.h"
#include"adc_defines.h"
#include"adc.h"

void Init_ADC(void)
{
ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
cfgportpinfunc(0,28,pin_func2);
}
void Read_ADC(u32 chno,u32 *adcDVal,f32 *eAR)
{
ADCR&=0XFFFFFF00;
ADCR|=1<<chno|1<<ADC_START_BIT;
delayUS(3);
while(((ADDR>>DONE_BIT)&1)==0);
ADCR&=~(1<<ADC_START_BIT);
*adcDVal=((ADDR>>RESULT_BITS)&1023);
*eAR=(*adcDVal * (3.3/1023));
}
