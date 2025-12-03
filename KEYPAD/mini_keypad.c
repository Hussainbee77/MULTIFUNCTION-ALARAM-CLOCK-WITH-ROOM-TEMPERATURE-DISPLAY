#include<lpc21xx.h>
#include"keypad_defines.h"
#include"mini_keypad.h"
#include"types.h"
#include"delay.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"defines.h"
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
u8 key=0,cnt=0;
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
