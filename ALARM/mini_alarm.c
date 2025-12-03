#include<lpc21xx.h>
#include"types.h"
#include"lcd.h"
#include"delay.h"
#include"lcd_defines.h"
#include"mini_keypad.h"
#include"rtc.h"
#include"mini_alarm.h"
s32 num;
u32 key;
u32 alarm_hour = 0,alarm_min = 0,Alarm_Ring,ent_flag = 0;;
u8 bell[]={0x04,0x0E,0x0E,0x0E,0x01F,0x00,0x0E,0x00};
/* ====== ALARM SET ===== */
void Alarm(void)
{
alarm_hour=0;
alarm_min=0;
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
			alarm_hour=num;
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
			alarm_min=num;
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
			StrLCD("ALARM SET");
			delayMS(200);
      		CmdLCD(CLEAR_LCD);
      return;
			}
      }
	  }
void check_alarm(void)
{
if(HOUR==alarm_hour && MIN==alarm_min)
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
	 
    
