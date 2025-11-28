void Init_ADC(void);
void Read_ADC(u32 ChNo,u32*adcDVal,f32*eaR);
void Init_LCD(void);
void Write_LCD(u8 byte);
void CmdLCD(u8 cmd);
void CharLCD(u8 asciiVal);
void StrLCD(s8*);
void U32LCD(u32);
void BuildCGRAM(u8 *,u8);
void Init_KPM(void);
u32 ColScan(void);
u32 RowCheck(void);
u32 ColCheck(void);
u32 KeyScan(void);
s32 ReadNum(void);
void eint0_isr(void)__irq;
void Init_Interrupt(void);
void RTC_Init(void);
void GetRTCTimeInfo(s32*,s32*,s32*);
void DisplayRTCTime(s32,s32,s32);
void GetRTCDateInfo(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);
void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);
void GetRTCDay(s32 *);
void DisplayRTCDay(u32);
void SetRTCDay(u32);
void SetRTCHour(u32);
void SetRTCMin(u32);
void SetRTCSec(u32);
void SetRTCDate(u32);
void SetRTCMonth(u32);
void SetRTCYear(u32);
void SetRTCDay(u32);
void GetRTCHour(s32 *);
void GetRTCMin(s32 *);
void GetRTCSec(s32 *);
void GetRTCDate(s32 *);
void GetRTCMonth(s32 *);
void GetRTCYear(s32 *);
void GetDay(void);
void cfgportpinfunc(u32 portno,u32 pinno,u32 pinfunc);




