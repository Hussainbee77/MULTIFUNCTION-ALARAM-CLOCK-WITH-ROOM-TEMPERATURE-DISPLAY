#include<lpc214x.h>
#include"mini_defines.h"
#include"types.h"
#include"delay.h"
#include"mini.h"

extern volatile u8 ShowMenu;

/* configure port pin function */

void cfgportpinfunc(u32 portno,u32 pinno,u32 pinfunc)
{
if(portno==0)
{
if(pinno<=15)
{
PINSEL0=((PINSEL0&~(3<<(pinno*2)))|(pinfunc<<(pinno*2)));
}
else if((pinno>=16)&&(pinno<=31))
{
PINSEL1=(((PINSEL1&~(3<<(pinno-16)*2)))|(pinfunc<<((pinno-16)*2)));
}
}
}

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

/* --- LCD --- */
void WriteLCD(u8 byte)
{
        //select write operation
        IOCLR0=1<<LCD_RW;
        //write byte to lcd data pins
        WRITEBYTE(IOPIN0,LCD_DATA,byte);
        //provide high to low pulse
        IOSET0=1<<LCD_EN;
        delayUS(1);
        IOCLR0=1<<LCD_EN;
        delayMS(2);
}

void CmdLCD(u8 cmdByte)
{
        //set rs pin for cmd/inst reg
  IOCLR0=1<<LCD_RS;
  //write cmd byte to cmd reg
  WriteLCD(cmdByte);
}

void Init_LCD(void)
{
        //cfg p0.8(d0) to p0.15(d7),
        //p0.16(rs),p0.17(rw),p0.18(en) 
        //as gpio output pins
        IODIR0|=((0xFF<<LCD_DATA)|
                 (1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));

        //power on delay
        delayMS(15);
        CmdLCD(0x30);
        delayMS(4);
        delayUS(100);
        CmdLCD(0x30);
        delayUS(100);
        CmdLCD(0x30);
        CmdLCD(MODE_8BIT_2LINE);
        CmdLCD(DSP_ON_CUR_ON);
        CmdLCD(CLEAR_LCD);
        CmdLCD(SHIFT_CUR_RIGHT);
}
void CharLCD(u8 asciiVal)
{				 
        //sel data reg
        IOSET0=1<<LCD_RS;
        //write ascii value via data reg to ddram
        WriteLCD(asciiVal);
}

void StrLCD(s8 *str)
{
        while(*str)
                CharLCD(*str++);
}

void U32LCD(u32 n)
{
        s32 i=0;
        u8 a[10];
        if(n==0)
        {
                CharLCD('0');
        }
        else
        {
          while(n>0)
    {
                  a[i++]=(n%10)+48;
      n/=10;
    }
    for(--i;i>=0;i--)
      CharLCD(a[i]);
        }
}
void BuildCGRAM(u8 *p,u8 nBytes)
{
	u32 i;
	CmdLCD(GOTO_CGRAM_START);
	IOSET0=1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
	WriteLCD(p[i]);
	}
	CmdLCD(GOTO_LINE1_POS0);
}

/* --- KEYPAD MATRIX --- */

u8 kpmLUT[4][4]={
				{'1','2','3','/'},
				{'4','5','6','x'},
				{'7','8','9','-'},
				{'C','0','=','+'}
				};

void Init_KPM(void)
{
WRITEBYTE(IODIR1,ROWs_4,15);/* rows as outputs(grounded) */
}
u32 ColScan(void)
{
return(READNIBBLE(IOPIN1,COLs_4)<15)?0:1;
}
u32 RowCheck(void)
{
u32 r;
for(r=0;r<=3;r++)
{
WRITENIBBLE(IOPIN1,ROWs_4,~(1<<r));
if(ColScan()==0)
{
break;
}
}
WRITENIBBLE(IOPIN1,ROWs_4,0);
return r;
}
u32 ColCheck(void)
{
u32 c;
for(c=0;c<=3;c++)
{
if(READBIT(IOPIN1,COL0+c)==0)
{
break;
}
}
return c;
}
u32 KeyScan(void)
{
u32 r,c,keyv;
while(ColScan());
r=RowCheck();
c=ColCheck();
keyv=kpmLUT[r][c];
while(ColScan()==0);
delayMS(200);
return keyv;
}
/* ReadNum (returns number entered,shows digits) */
s32 ReadNum(void)
{
s32 num=0;
u8 key,cnt=0;
while(1)
{
key=(u8)KeyScan();
if(key>='0'&&key<='9')
{
if(cnt<2)
{
num=(num*10)+(key-48);
CmdLCD(GOTO_LINE2_POS0);
U32LCD(num);
cnt++;
}
else
{
CmdLCD(CLEAR_LCD);
StrLCD("Invalid!");
delayMS(200);
break;
}
}
else if(key=='C')
{
if(cnt==0)
{
continue;
}
cnt--;
num=num/10;
CmdLCD(GOTO_LINE2_POS0+cnt);
CharLCD(' ');
CmdLCD(GOTO_LINE2_POS0+cnt);
}
else if(key=='=')
{
break;
}
}
return num;
}

/* --- RTC  --- */

s8 week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
void RTC_Init(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
  // Enable the RTC
	CCR = RTC_ENABLE|(1<<4);  
}

/*Get the current RTC time*/

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}


/*
Display the RTC time on LCD
hour value (0 23)
minute value (0 59)
second value (0 59) seperated by ':'
*/

void DisplayRTCTime(s32 hour, s32 minute, s32 second)
{
		CmdLCD(GOTO_LINE1_POS0);
		CharLCD((hour/10)+48);
		CharLCD((hour%10)+48);
		CharLCD(':');
		CharLCD((minute/10)+0x30);
		CharLCD((minute%10)+0x30);
		CharLCD(':');
		CharLCD((second/10)+'0');
		CharLCD((second%10)+'0');
}

/*
Get the current RTC date
date Pointer to store the current date (1 31)
month Pointer to store the current month (1 12)
year Pointer to store the current year (four digits)
*/

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

/*
Display the RTC date on LCD
Date of month (1 31)
Month (1 12)
Year (four digits) and seperated by '/'
*/

void DisplayRTCDate(u32 date, u32 month, u32 year)
{
		CmdLCD(GOTO_LINE2_POS0);
		CharLCD((date/10)+48);
		CharLCD((date%10)+48);
		CharLCD('/');
		CharLCD((month/10)+0x30);
		CharLCD((month%10)+0x30);
		CharLCD('/');
		U32LCD(year);	
}
/*
Set the RTC time
Hour to set (0 23)
Minute to set (0 59)
Second to set (0 59)
*/

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;
}

/*
Set the RTC date
date of month to set (1 31)
month to set (1 12)
year to set (four digits)
*/

void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}
/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/

void GetRTCDay(s32 *dayofweek)
{
	*dayofweek=DOW; 
}

/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/

void DisplayRTCDay(u32 dayofweek)
{
	CmdLCD(GOTO_LINE1_POS0+10);
	StrLCD(week[dayofweek]);  
}
/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32 dayofweek)
{
		DOW = dayofweek;
}

void EINT1_ISR(void)__irq;
void Init_Interrupt(void)
{
//configure p0.3 as EINT1(function 3)
cfgportpinfunc(0,1,EINT0_0_1);
//PINSEL0=(PINSEL0 &~(3U<<6))|(3U<<6); // bits 7:6 =11->EINT1 cfgportpinfunc(0,1,3);
//Edge sensitive falling edge
VICIntEnable=1<<14;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
VICVectCntl0=(1<<5)|14;
VICVectAddr0=(u32)EINT1_ISR;
EXTMODE=1<<0;
//IODIR1|=1<<24;
}

/*ISR HANDLER */
void Menu(void);
void EINT1_ISR(void)__irq
{
Menu();
EXTINT = 1<<0;
VICVectAddr = 0;
}



