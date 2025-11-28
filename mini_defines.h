#define READBIT(WORD,BIT) ((WORD>>BIT)&1)
#define WRITENIBBLE(WORD,NIBBLESTARTBITPOS,VAL) \
        WORD=((WORD&~(15<<NIBBLESTARTBITPOS))|(VAL<<NIBBLESTARTBITPOS))
#define READNIBBLE(WORD,NIBBLESTARTBIT) \
        ((WORD>>NIBBLESTARTBIT)&15)
#define WRITEBYTE(WORD,BYTESTARTBITPOS,VAL) \
        WORD=((WORD&~(0xFF<<BYTESTARTBITPOS))|((VAL<<BYTESTARTBITPOS)))
#define WRITEBIT(WORD,BITPOS,BITVAL)\
		WORD=((WORD&~(1<<BITPOS))|(BITVAL<<BITPOS))

//clock defines
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADCCLK 3000000
#define CLKDIV ((PCLK/ADCCLK)-1)
//ADDR sfr defines
#define RESULT_BITS 6
#define DONE_BIT 31
//ADCR sfr defines
#define CLKDIV_BITS 8
#define PDN_BIT 21
#define ADC_START_BIT  24
//lcd commands
#define CLEAR_LCD            0x01 
#define RET_CUR_HOME         0x02 
#define SHIFT_CUR_RIGHT      0x06 
#define SHIFT_CUR_LEFT       0x07 
#define DSP_OFF              0x08 
#define DSP_ON_CUR_OFF       0x0c 
#define DSP_ON_CUR_ON        0x0E 
#define DSP_ON_CUR_BLINK     0x0F 
#define SHIFT_DISP_LEFT      0x10 
#define SHIFT_DISP_RIGHT     0x14 
#define MODE_8BIT_1LINE      0x30 
#define MODE_4BIT_1LINE      0x20 
#define MODE_8BIT_2LINE      0x38 
#define MODE_4BIT_2LINE      0x28 
#define GOTO_LINE1_POS0      0x80 
#define GOTO_LINE2_POS0      0xC0 
#define GOTO_LINE3_POS0      0x94 
#define GOTO_LINE4_POS0      0xD4 
#define GOTO_CGRAM_START     0x40 
//lpc2129 port pin connection to lcd
#define LCD_DATA        8//@p0.8(d0) to p0.15(d7)
#define LCD_RS         16//@p0.16
#define LCD_RW         18//@p0.18
#define LCD_EN         17//@p0.17
//kpm defines
#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19
#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23
#define ROWs_4 16
#define COLs_4 20
//RTC defines
#define RTC_DEFINES_H
#define FOSC  12000000
#define PCLK  (CCLK/4)
#define PREINT_VAL  ((int)((PCLK/32768)-1))
#define PREFRAC_VAL  (PCLK - ((PREINT_VAL+1)*32768))
#define RTC_ENABLE  (1<<0)
#define RTC_RESET  (1<<1)
//Pin connect block defines
#define pin_func1 0
#define pin_func2 1
#define pin_func3 2
#define pin_func4 3
#define EINT0_0_1 3
#define EINT1_0_3 3
#define EINT2_0_7 3

