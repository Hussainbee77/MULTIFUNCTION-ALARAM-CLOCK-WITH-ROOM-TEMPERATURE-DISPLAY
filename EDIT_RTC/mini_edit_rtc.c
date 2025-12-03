#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
#include"lcd_defines.h"
#include"mini_keypad.h"
#include"lcd.h"
//edit rtc
void edit(s32*hour,s32*min,s32*sec,s32*day,s32*date,s32*month,s32*year)
{
s32 num;
extern u8 key;

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
