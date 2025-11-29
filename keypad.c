#include<lpc21xx.h>
#include"defines.h"
#include"keypad_defines.h"
#include"types.h"
u32 KPMLUT[4][4]={
{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
void KPM_Init()
{
WRITENIBBLE(IODIR1,ROWs_4,15);
}
u32 ColScan()
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
 return c;
 }
 }
 }
 u32 KeyScan()
 {
 u32 r,c,keyv;
 while(ColScan());
 r=RowCheck();
 c=ColScan();
 keyv=KPMLUT[r][c];
 return keyv;
 }
 void ReadNum(u32*num,u32*key)
 {
 *num=0;
 while(1)
 {
 *key=KeyScan();
 if(*key>='0'&&*key<='9')
 {
 while(ColScan()==0);
 }
 else
 {
 while(ColScan()==0);
 break;
 }
 }
 }
