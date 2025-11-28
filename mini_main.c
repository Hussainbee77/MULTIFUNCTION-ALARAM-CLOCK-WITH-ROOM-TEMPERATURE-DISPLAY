#include<lpc214x.h>
#include"types.h"
#include"mini.h"
#include"mini_defines.h"
#include"delay.h"

s32 hour,min,sec,date,month,year,day,num;
u32 adcDVal,temp,ChNo=1,key,Alarm_Ring;
u8 bell[]={0x04,0x0E,0x0E,0x0E,0x01F,0x00,0x0E,0x00};
f32 eAR;
volatile u8 ShowMenu = 0; //Global and volatile(modified in ISR)
u32 alaram_hour = 0,alaram_min = 0,ent_flag = 0;
u32 key;
u32 i;																										 
void Alaram(void);
void edit(s32*hour,s32*min,s32*sec,s32*day,s32*date,s32*month,s32*year);
void Menu(void);

int main()
{
Init_ADC();
Init_LCD();
Init_KPM();
Init_Interrupt();
RTC_Init();
SetRTCTimeInfo(15,35,00);
IODIR0|=1<<0;
SetRTCDateInfo(29,10,2025);
SetRTCDay(1);
while(1)
{	 
if(ShowMenu == 0)
{
/*--- Line 1:time+Day ---*/
CmdLCD(GOTO_LINE1_POS0);
GetRTCTimeInfo(&hour,&min,&sec);
DisplayRTCTime(hour,min,sec);
GetRTCDay(&day);
CmdLCD(GOTO_LINE1_POS0+10);
DisplayRTCDay(day);

/* --- Line 2:Date + Temperature --- */
CmdLCD(GOTO_LINE2_POS0);
GetRTCDateInfo(&date,&month,&year);
DisplayRTCDate(date,month,year);
Read_ADC(ChNo,&adcDVal,&eAR);
temp=(u32)(eAR*100.0f);
CmdLCD(GOTO_LINE2_POS0+12);
U32LCD(temp);
CharLCD(0XDF); /* Degree Synbol */
CharLCD('C');

/* Alaram check(when seconds == 0 to trigger once per mintute)*/
if(HOUR==alaram_hour && MIN==alaram_min)
		{
			if(Alarm_Ring==0)
			{  
			 BuildCGRAM(bell,8);
			 CmdLCD(GOTO_LINE1_POS0+15);
		      CharLCD(0);
			 IOSET0=1<<0;
			if((IOPIN0>>22&1)==0)//switch for stop the alarm
			{	
		    	IOCLR0=1<<0;
			   CmdLCD(GOTO_LINE1_POS0+15);
			   CharLCD(' ');
			   Alarm_Ring=1;
			}

			}											 
			   //CharLCD(' ');
	}
		else
	  	{	
				CmdLCD(GOTO_LINE1_POS0+15);
			   CharLCD(' ');
				Alarm_Ring=0;
		}
    }
    }
    }
/* ====MENU =====*/
void Menu(void)
{
while(1)
{
CmdLCD(CLEAR_LCD);
StrLCD("1.Edit RTC");
CmdLCD(GOTO_LINE2_POS0);
StrLCD("2.ALARAM 3.EXIT");
key=(u8)KeyScan();
while(ColScan()==0);/* Wait Release */
CmdLCD(CLEAR_LCD);
CharLCD(key);
switch(key)
{
case '1':edit(&hour,&min,&sec,&day,&date,&month,&year);
		break;

case '2':Alaram();
		break;

case '3':CmdLCD(0X01);
		 return;
}
}
}
/* ====== ALARAM SET ===== */
void Alaram(void)
{
alaram_hour=0;
alaram_min=0;
while(1)
{
CmdLCD(CLEAR_LCD);
StrLCD("SET ALARM");
CmdLCD(GOTO_LINE2_POS0);
StrLCD("1.HH2.MM3.EXIT");

key=(u8)KeyScan();
while(ColScan()==0);
switch(key)
	{
	case'1':CmdLCD(0x01);
			StrLCD("ENTER HOUR(0-23)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=0 && num<24)
			{
			alaram_hour=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			CmdLCD(0X01);
			}
			break;
	case '2':CmdLCD(0X01);
			StrLCD("ENTER MIN(0-59)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=0 && num<60)
			{
			alaram_min=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			CmdLCD(0X01);
			}
			break;
	case '3':CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("ALARAM SET");
			delayMS(200);
      		CmdLCD(CLEAR_LCD);
      return;
			}
      }
      }

/* ====== EDIT FUNCTION ====== */
void edit(s32*hour,s32*min,s32*sec,s32*day,s32*date,s32*month,s32*year)
{
s32 num;
u8 key;

while(1)
{
	CmdLCD(CLEAR_LCD);
	StrLCD("1.H2.M3.S4.D");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("5.DD6.MM7.Y8.E");
	key=(u8)KeyScan();
	while(ColScan()==0);
	switch(key)
	{
	case'1':CmdLCD(0x01);
			StrLCD("ENTER HOUR(0-23)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=0 && num<24)
			{
			HOUR=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;
	case '2':CmdLCD(0X01);
			StrLCD("ENTER MIN(0-59)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=0 && num<60)
			{
			MIN=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;
	case '3':CmdLCD(0X01);
			StrLCD("ENTER SEC(0-59)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=0 && num<60)
			{
			   SEC=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;
	case '4':CmdLCD(0X01);
			StrLCD("ENTER DAY(0-6)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=0 && num<7)
			{
			   DOW=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}	
			break;											  

			
	case '5':CmdLCD(0X01);
			StrLCD("ENTER DATE(1-31)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=1 && num<=31)
			{
			DOM=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;
			
	case '6':CmdLCD(0X01);
			StrLCD("ENTER MONTH(1-12)");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=1 && num<=12)
			{
			MONTH=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;

	case '7':CmdLCD(CLEAR_LCD);
			StrLCD("ENTER YEAR");
			CmdLCD(GOTO_LINE2_POS0);
			num=ReadNum();
			if(num>=2000 && num<=2200)
			{
			YEAR=num;
			}
			else
			{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("Invalid Inputs");
			delayMS(200);
			}
			break;
			
	case '8':CmdLCD(0X01);
			 return;

	default:CmdLCD(0X01);
			StrLCD("INVALID INPUT");
			delayS(1);
			break;
		}
	}
}


