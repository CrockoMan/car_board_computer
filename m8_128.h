// ONLY for CodeVisionAVR C Compiler
/* (C) Termo  avr123.nm.ru 


 Нашли ошибку ? сообщите в мыло на mail.ru для bbigmak 
 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 Определения всех битов для микроконтроллеров 
 ATmega8 ATmega16 ATmega32 ATmega64 ATmega128

 по DataSheets на 2004/12/19 


поместите этот файл в папку:  CVAVR\inc

и включите его в исходник вашей программы вот так:

#include <mega16.h>  // это обычно включаемый файл дл выбраного МК

#include <m8_128.h>

Теперь вы можете использовать примеры на 
Си из ДШ в том виде как они там написаны.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++

теперь вы можете использовать более читаемый формат   

b_1010_1100   вместо   0b10101100
     
======================================================

 Found errors ? E-mail me to mail.ru for bbigmak 

 ALL BIT's definitions for ATmega8 ATmega16 
                           ATmega32 ATmega64 ATmega128

 from DataSheets at 2004/12/19 


Put this file into CVAVR\inc
and include this file after 
standart heder file for MCU

Example:

#include <mega16.h>

#include <m8_128.h>



NOW you can use:    b_1010_1100  

insted of less clearly  0b10101100


*/

///////////////////////////////////////////////

#define  u8 unsigned char    // 0 to 255
#define  s8   signed char    // -128 to 127

#define  u16 unsigned int    //  0 to 65535
#define  s16   signed int	   //	-32768 to 32767

#define  u32 unsigned long int	//	0 to 4294967295
#define  s32   signed long int	// -2147483648 to 2147483647

#define  f32 float	//	±1.175e-38 to ±3.402e38
#define  d32 double	//	±1.175e-38 to ±3.402e38

/*
Type	Size (Bits)	Range  from CodeVisionAVR help
bit	1	0 , 1
char	8	-128 to 127
unsigned char	8	0 to 255
signed char	8	-128 to 127
int	16	-32768 to 32767
short int	16	-32768 to 32767
unsigned int	16	0 to 65535
signed int	16	-32768 to 32767
long int	32	-2147483648 to 2147483647
unsigned long int	32	0 to 4294967295
signed long int	32	-2147483648 to 2147483647
float	32	±1.175e-38 to ±3.402e38
double	32	±1.175e-38 to ±3.402e38
*/

///////////////////////////////////////////////

#ifdef _MEGA8_INCLUDED_


/* 2 wire serial interface */

#define  TWPS1    1
#define  TWPS0    0

#define  TWINT    7
#define  TWEA     6
#define  TWSTA    5
#define  TWSTO    4
#define  TWWC     3
#define  TWEN     2
#define  TWIE     0

#define  TWGCE    0


/* ADC */

#define  ADEN     7
#define  ADSC     6
#define  ADFR     5
#define  ADIF     4
#define  ADIE     3
#define  ADPS2    2
#define  ADPS1    1
#define  ADPS0    0

#define  REFS1    7
#define  REFS0    6
#define  ADLAR    5
#define  MUX3     3
#define  MUX2     2
#define  MUX1     1
#define  MUX0     0

/* Analog Comparator */

#define  ACD      7
#define  ACBG     6
#define  ACO      5
#define  ACI      4
#define  ACIE     3
#define  ACIC     2
#define  ACIS1    1
#define  ACIS0    0

/* USART */

#define  URSEL    7

#define  URSEL    7
#define  UMSEL    6
#define  UPM1     5
#define  UPM0     4
#define  USBS     3
#define  UCSZ1    2
#define  UCSZ0    1
#define  UCPOL    0

#define  RXCIE    7
#define  TXCIE    6
#define  UDRIE    5
#define  RXEN     4
#define  TXEN     3
#define  UCSZ2    2
#define  RXB8     1
#define  TXB8     0

#define  RXC      7
#define  TXC      6
#define  UDRE     5
#define  FE       4
#define  DOR      3
#define  OVR      3    /*This definition differs from the databook*/
#define  PE       2

#define  UPE      2    /*This definition from CodeWizardAVR */

#define  U2X      1
#define  MPCM     0


/* SPI */

#define  SPIE     7
#define  SPE      6
#define  DORD     5
#define  MSTR     4
#define  CPOL     3
#define  CPHA     2
#define  SPR1     1
#define  SPR0     0

#define  SPIF     7
#define  WCOL     6
#define  SPI2X    0


/* EEPROM */

#define  EERIE    3
#define  EEMWE    2
#define  EEWE     1
#define  EERE     0


/* Watchdog Timer Control Register */

#define  WDCE     4
#define  WDTOE    4    /*This definition differs from the databook*/
#define  WDE      3
#define  WDP2     2
#define  WDP1     1
#define  WDP0     0

/* Timer/Counter 2 */

#define  AS2      3
#define  TCN2UB   2
#define  OCR2UB   1
#define  TCR2UB   0

#define  FOC2     7
#define  WGM20    6
#define  COM21    5
#define  COM20    4
#define  WGM21    3
#define  CS22     2
#define  CS21     1
#define  CS20     0

/* Timer/Counter 1 */

#define  ICNC1    7
#define  ICES1    6
#define  WGM13    4
#define  WGM12    3
#define  CS12     2
#define  CS11     1
#define  CS10     0

#define  COM1A1   7
#define  COM1A0   6
#define  COM1B1   5
#define  COM1B0   4
#define  FOC1A    3
#define  FOC1B    2
#define  WGM11    1
#define  WGM10    0

/* Special Function I/O register */

#define  ADHSM    4
#define  ACME     3
#define  PUD      2
#define  PSR2     1
#define  PSR10    0


/* Timer/Counter 0 */
#define  CS02     2
#define  CS01     1
#define  CS00     0

/* MCU general */

#define	 WDRF     3
#define  BORF     2
#define  EXTRF    1
#define  PORF     0

#define  SE       7
#define  SM2      6
#define  SM1      5
#define  SM0      4
#define  ISC11    3
#define  ISC10    2
#define  ISC01    1
#define  ISC00    0

/* SPM Conrol Register */

#define  SPMIE    7
#define  RWWSB    6
#define  RWWSRE   4
#define  BLBSET   3
#define  PGWRT    2
#define  PGERS    1
#define  SPMEN    0

/* Timer/Counter Interrupts */

#define  OCF2     7
#define  TOV2     6
#define  ICF1     5
#define  OCF1A    4
#define  OCF1B    3
#define  TOV1     2
#define  TOV0     0

#define  OCIE2    7
#define  TOIE2    6
#define  TICIE1   5
#define  OCIE1A   4
#define  OCIE1B   3
#define  TOIE1    2
#define  TOIE0    0

/* General Interrupts */

#define  INTF1    7
#define  INTF0    6

#define  INT1     7
#define  INT0     6
#define  IVSEL    1
#define  IVCE     0




/* Port B bits */
#define  PORTB7   7
#define  PORTB6   6
#define  PORTB5   5
#define  PORTB4   4
#define  PORTB3   3
#define  PORTB2   2
#define  PORTB1   1
#define  PORTB0   0

#define  PB7      7
#define  PB6      6
#define  PB5      5
#define  PB4      4
#define  PB3      3
#define  PB2      2
#define  PB1      1
#define  PB0      0

#define  DDB7     7
#define  DDB6     6
#define  DDB5     5
#define  DDB4     4
#define  DDB3     3
#define  DDB2     2
#define  DDB1     1
#define  DDB0     0

#define  PINB7    7
#define  PINB6    6
#define  PINB5    5
#define  PINB4    4
#define  PINB3    3
#define  PINB2    2
#define  PINB1    1
#define  PINB0    0

/* Port C bits */
#define  PORTC6   6
#define  PORTC5   5
#define  PORTC4   4
#define  PORTC3   3
#define  PORTC2   2
#define  PORTC1   1
#define  PORTC0   0
#define  PC6      6
#define  PC5      5
#define  PC4      4
#define  PC3      3
#define  PC2      2
#define  PC1      1
#define  PC0      0

#define  DDC6     6
#define  DDC5     5
#define  DDC4     4
#define  DDC3     3
#define  DDC2     2
#define  DDC1     1
#define  DDC0     0

#define  PINC6    6
#define  PINC5    5
#define  PINC4    4
#define  PINC3    3
#define  PINC2    2
#define  PINC1    1
#define  PINC0    0

/* Port D bits */
#define  PORTD7   7
#define  PORTD6   6
#define  PORTD5   5
#define  PORTD4   4
#define  PORTD3   3
#define  PORTD2   2
#define  PORTD1   1
#define  PORTD0   0
#define  PD7      7
#define  PD6      6
#define  PD5      5
#define  PD4      4
#define  PD3      3
#define  PD2      2
#define  PD1      1
#define  PD0      0

#define  DDD7     7
#define  DDD6     6
#define  DDD5     5
#define  DDD4     4
#define  DDD3     3
#define  DDD2     2
#define  DDD1     1
#define  DDD0     0

#define  PIND7    7
#define  PIND6    6
#define  PIND5    5
#define  PIND4    4
#define  PIND3    3
#define  PIND2    2
#define  PIND1    1
#define  PIND0    0


/* Lock and Fuse Bits with LPM/SPM instructions */

/* lock bits */
#define  BLB12    5
#define  BLB11    4
#define  BLB02    3
#define  BLB01    2
#define  LB2      1
#define  LB1      0

/* fuses low bits */
#define  BODLEVEL 7
#define  BODEN    6
#define  SUT1     5
#define  SUT0     4
#define  CKSEL3   3
#define  CKSEL2   2
#define  CKSEL1   1
#define  CKSEL0   0

/* fuses high bits */
#define  RSTDISBL 7
#define  WDTON    6
#define  SPIEN    5
#define  CKOPT    4
#define  EESAVE   3
#define  BOOTSZ1  2
#define  BOOTSZ0  1
#define  BOOTRST  0

#endif




///////////////////////////////////////////////

#ifdef _MEGA16_INCLUDED_


/* 2 wire serial interface */

#define  TWPS1    1
#define  TWPS0    0

#define  TWINT    7
#define  TWEA     6
#define  TWSTA    5
#define  TWSTO    4
#define  TWWC     3
#define  TWEN     2
#define  TWIE     0

#define  TWGCE    0


/* ADC */

#define  ADEN     7
#define  ADSC     6
#define  ADATE    5
#define  ADFR     5    /*This definition was in old datasheet*/
#define  ADIF     4
#define  ADIE     3
#define  ADPS2    2
#define  ADPS1    1
#define  ADPS0    0

#define  REFS1    7
#define  REFS0    6
#define  ADLAR    5
#define  MUX4     4
#define  MUX3     3
#define  MUX2     2
#define  MUX1     1
#define  MUX0     0

/* Analog Comparator */

#define  ACD      7
#define  ACBG     6
#define  ACO      5
#define  ACI      4
#define  ACIE     3
#define  ACIC     2
#define  ACIS1    1
#define  ACIS0    0

/* USART */

#define  URSEL    7

#define  URSEL    7
#define  UMSEL    6
#define  UPM1     5
#define  UPM0     4
#define  USBS     3
#define  UCSZ1    2
#define  UCSZ0    1
#define  UCPOL    0

#define  RXCIE    7
#define  TXCIE    6
#define  UDRIE    5
#define  RXEN     4
#define  TXEN     3
#define  UCSZ2    2
#define  RXB8     1
#define  TXB8     0

#define  RXC      7
#define  TXC      6
#define  UDRE     5
#define  FE       4
#define  DOR      3
#define  OVR      3    /*This definition differs from the databook*/
#define  PE       2

#define  UPE      2    /*This definition from CodeWizardAVR */

#define  U2X      1
#define  MPCM     0


/* SPI */

#define  SPIE     7
#define  SPE      6
#define  DORD     5
#define  MSTR     4
#define  CPOL     3
#define  CPHA     2
#define  SPR1     1
#define  SPR0     0

#define  SPIF     7
#define  WCOL     6
#define  SPI2X    0



/* EEPROM */

#define  EERIE    3
#define  EEMWE    2
#define  EEWE     1
#define  EERE     0


/* Watchdog Timer Control Register */

#define  WDTOE    4
#define  WDE      3
#define  WDP2     2
#define  WDP1     1
#define  WDP0     0


/* Timer/Counter 2 */

#define  AS2      3
#define  TCN2UB   2
#define  OCR2UB   1
#define  TCR2UB   0

#define  FOC2     7
#define  WGM20    6
#define  COM21    5
#define  COM20    4
#define  WGM21    3
#define  CS22     2
#define  CS21     1
#define  CS20     0

/* Timer/Counter 1 */

#define  ICNC1    7
#define  ICES1    6
#define  WGM13    4
#define  WGM12    3
#define  CS12     2
#define  CS11     1
#define  CS10     0

#define  COM1A1   7
#define  COM1A0   6
#define  COM1B1   5
#define  COM1B0   4
#define  FOC1A    3
#define  FOC1B    2
#define  WGM11    1
#define  WGM10    0

/* Special Function I/O register */

#define  ADTS2    7
#define  ADTS1    6
#define  ADTS0    5
#define  ADHSM    4
#define  ACME     3
#define  PUD      2
#define  PSR2     1
#define  PSR10    0



/* Timer/Counter 0 */

#define  FOC0     7
#define  WGM00    6
#define  COM01    5
#define  COM00    4
#define  WGM01    3
#define  CS02     2
#define  CS01     1
#define  CS00     0

/* MCU general */

#define	 JTD      7
#define	 ISC2     6
#define	 JTRF     4
#define	 WDRF     3
#define  BORF     2
#define  EXTRF    1
#define  PORF     0

#define  SM2      7
#define  SE       6
#define  SM1      5
#define  SM0      4
#define  ISC11    3
#define  ISC10    2
#define  ISC01    1
#define  ISC00    0

/* SPM Conrol Register */

#define  SPMIE    7
#define  RWWSB    6
#define  RWWSRE   4
#define  BLBSET   3
#define  PGWRT    2
#define  PGERS    1
#define  SPMEN    0

/* Timer/Counter Interrupts */

#define  OCF2     7
#define  TOV2     6
#define  ICF1     5
#define  OCF1A    4
#define  OCF1B    3
#define  TOV1     2
#define  OCF0     1
#define  TOV0     0

#define  OCIE2    7
#define  TOIE2    6
#define  TICIE1   5
#define  OCIE1A   4
#define  OCIE1B   3
#define  TOIE1    2
#define  OCIE0    1
#define  TOIE0    0

/* General Interrupts */

#define  INTF1    7
#define  INTF0    6
#define  INTF2    5

#define  INT1     7
#define  INT0     6
#define  INT2     5
#define  IVSEL    1
#define  IVCE     0




/* Port A bits */
#define  PORTA7   7
#define  PORTA6   6
#define  PORTA5   5
#define  PORTA4   4
#define  PORTA3   3
#define  PORTA2   2
#define  PORTA1   1
#define  PORTA0   0
#define  PA7      7
#define  PA6      6
#define  PA5      5
#define  PA4      4
#define  PA3      3
#define  PA2      2
#define  PA1      1
#define  PA0      0

#define  DDA7     7
#define  DDA6     6
#define  DDA5     5
#define  DDA4     4
#define  DDA3     3
#define  DDA2     2
#define  DDA1     1
#define  DDA0     0

#define  PINA7    7
#define  PINA6    6
#define  PINA5    5
#define  PINA4    4
#define  PINA3    3
#define  PINA2    2
#define  PINA1    1
#define  PINA0    0

/* Port B bits */
#define  PORTB7   7
#define  PORTB6   6
#define  PORTB5   5
#define  PORTB4   4
#define  PORTB3   3
#define  PORTB2   2
#define  PORTB1   1
#define  PORTB0   0
#define  PB7      7
#define  PB6      6
#define  PB5      5
#define  PB4      4
#define  PB3      3
#define  PB2      2
#define  PB1      1
#define  PB0      0

#define  DDB7     7
#define  DDB6     6
#define  DDB5     5
#define  DDB4     4
#define  DDB3     3
#define  DDB2     2
#define  DDB1     1
#define  DDB0     0

#define  PINB7    7
#define  PINB6    6
#define  PINB5    5
#define  PINB4    4
#define  PINB3    3
#define  PINB2    2
#define  PINB1    1
#define  PINB0    0

/* Port C bits */
#define  PORTC7   7
#define  PORTC6   6
#define  PORTC5   5
#define  PORTC4   4
#define  PORTC3   3
#define  PORTC2   2
#define  PORTC1   1
#define  PORTC0   0
#define  PC7      7
#define  PC6      6
#define  PC5      5
#define  PC4      4
#define  PC3      3
#define  PC2      2
#define  PC1      1
#define  PC0      0

#define  DDC7     7
#define  DDC6     6
#define  DDC5     5
#define  DDC4     4
#define  DDC3     3
#define  DDC2     2
#define  DDC1     1
#define  DDC0     0

#define  PINC7    7
#define  PINC6    6
#define  PINC5    5
#define  PINC4    4
#define  PINC3    3
#define  PINC2    2
#define  PINC1    1
#define  PINC0    0

/* Port D bits */
#define  PORTD7   7
#define  PORTD6   6
#define  PORTD5   5
#define  PORTD4   4
#define  PORTD3   3
#define  PORTD2   2
#define  PORTD1   1
#define  PORTD0   0
#define  PD7      7
#define  PD6      6
#define  PD5      5
#define  PD4      4
#define  PD3      3
#define  PD2      2
#define  PD1      1
#define  PD0      0

#define  DDD7     7
#define  DDD6     6
#define  DDD5     5
#define  DDD4     4
#define  DDD3     3
#define  DDD2     2
#define  DDD1     1
#define  DDD0     0

#define  PIND7    7
#define  PIND6    6
#define  PIND5    5
#define  PIND4    4
#define  PIND3    3
#define  PIND2    2
#define  PIND1    1
#define  PIND0    0


/* Lock and Fuse Bits with LPM/SPM instructions */

/* lock bits */
#define  BLB12    5
#define  BLB11    4
#define  BLB02    3
#define  BLB01    2
#define  LB2      1
#define  LB1      0

/* fuses low bits */
#define  BODLEVEL 7
#define  BODEN    6
#define  SUT1     5
#define  SUT0     4
#define  CKSEL3   3
#define  CKSEL2   2
#define  CKSEL1   1
#define  CKSEL0   0

/* fuses high bits */
#define  OCDEN    7
#define  JTAGEN   6
#define  SPIEN    5
#define  CKOPT    4
#define  EESAVE   3
#define  BOOTSZ1  2
#define  BOOTSZ0  1
#define  BOOTRST  0



#endif


#ifdef _MEGA32_INCLUDED_

/* 2 wire serial interface */

#define  TWPS1    1
#define  TWPS0    0

#define  TWINT    7
#define  TWEA     6
#define  TWSTA    5
#define  TWSTO    4
#define  TWWC     3
#define  TWEN     2
#define  TWIE     0

#define  TWGCE    0


/* ADC */

#define  ADEN     7
#define  ADSC     6
#define  ADATE    5
#define  ADIF     4
#define  ADIE     3
#define  ADPS2    2
#define  ADPS1    1
#define  ADPS0    0

#define  REFS1    7
#define  REFS0    6
#define  ADLAR    5
#define  MUX4     4
#define  MUX3     3
#define  MUX2     2
#define  MUX1     1
#define  MUX0     0

/* Analog Comparator */

#define  ACD      7
#define  ACBG     6
#define  ACO      5
#define  ACI      4
#define  ACIE     3
#define  ACIC     2
#define  ACIS1    1
#define  ACIS0    0

/* USART */

#define  URSEL    7

//#define  URSEL    7
#define  UMSEL    6
#define  UPM1     5
#define  UPM0     4
#define  USBS     3
#define  UCSZ1    2
#define  UCSZ0    1
#define  UCPOL    0

#define  RXCIE    7
#define  TXCIE    6
#define  UDRIE    5
#define  RXEN     4
#define  TXEN     3
#define  UCSZ2    2
#define  RXB8     1
#define  TXB8     0

#define  RXC      7
#define  TXC      6
#define  UDRE     5
#define  FE       4
#define  DOR      3
#define  OVR      3    /*This definition differs from the databook*/
#define  PE       2

#define  UPE      2    /*This definition from CodeWizardAVR */

#define  U2X      1
#define  MPCM     0


/* SPI */

#define  SPIE     7
#define  SPE      6
#define  DORD     5
#define  MSTR     4
#define  CPOL     3
#define  CPHA     2
#define  SPR1     1
#define  SPR0     0

#define  SPIF     7
#define  WCOL     6
#define  SPI2X    0




/* EEPROM */

#define  EERIE    3
#define  EEMWE    2
#define  EEWE     1
#define  EERE     0


/* Watchdog Timer Control Register */

#define  WDTOE    4
#define  WDE      3
#define  WDP2     2
#define  WDP1     1
#define  WDP0     0

/* Timer/Counter 2 */

#define  AS2      3
#define  TCN2UB   2
#define  OCR2UB   1
#define  TCR2UB   0

#define  FOC2     7
#define  WGM20    6
#define  COM21    5
#define  COM20    4
#define  WGM21    3
#define  CS22     2
#define  CS21     1
#define  CS20     0

/* Timer/Counter 1 */

#define  ICNC1    7
#define  ICES1    6
#define  WGM13    4
#define  WGM12    3
#define  CS12     2
#define  CS11     1
#define  CS10     0

#define  COM1A1   7
#define  COM1A0   6
#define  COM1B1   5
#define  COM1B0   4
#define  FOC1A    3
#define  FOC1B    2
#define  WGM11    1
#define  WGM10    0

/* Special Function I/O register */

#define  ADTS2    7
#define  ADTS1    6
#define  ADTS0    5
#define  ADHSM    4
#define  ACME     3
#define  PUD      2
#define  PSR2     1
#define  PSR10    0



/* Timer/Counter 0 */

#define  FOC0     7
#define  WGM00    6
#define  COM01    5
#define  COM00    4
#define  WGM01    3
#define  CS02     2
#define  CS01     1
#define  CS00     0

/* MCU general */

#define	 JTD      7
#define	 ISC2     6
#define	 JTRF     4
#define	 WDRF     3
#define  BORF     2
#define  EXTRF    1
#define  PORF     0

#define  SE       7
#define  SM2      6
#define  SM1      5
#define  SM0      4
#define  ISC11    3
#define  ISC10    2
#define  ISC01    1
#define  ISC00    0

/* SPM Conrol Register */
//#define SPMCR	
#define  SPMIE    7
#define  RWWSB    6
#define  RWWSRE   4
#define  BLBSET   3
#define  PGWRT    2
#define  PGERS    1
#define  SPMEN    0

/* Timer/Counter Interrupts */
//#define TIFR	
#define  OCF2     7
#define  TOV2     6
#define  ICF1     5
#define  OCF1A    4
#define  OCF1B    3
#define  TOV1     2
#define  OCF0     1
#define  TOV0     0
//#define TIMSK	
#define  OCIE2    7
#define  TOIE2    6
#define  TICIE1   5
#define  OCIE1A   4
#define  OCIE1B   3
#define  TOIE1    2
#define  OCIE0    1
#define  TOIE0    0

/* General Interrupts */
//#define GIFR	
#define  INTF1    7
#define  INTF0    6
#define  INTF2    5
//#define GICR	
#define  INT1     7
#define  INT0     6
#define  INT2     5
#define  IVSEL    1
#define  IVCE     0




/* Port A bits */
#define  PORTA7   7
#define  PORTA6   6
#define  PORTA5   5
#define  PORTA4   4
#define  PORTA3   3
#define  PORTA2   2
#define  PORTA1   1
#define  PORTA0   0
#define  PA7      7
#define  PA6      6
#define  PA5      5
#define  PA4      4
#define  PA3      3
#define  PA2      2
#define  PA1      1
#define  PA0      0

#define  DDA7     7
#define  DDA6     6
#define  DDA5     5
#define  DDA4     4
#define  DDA3     3
#define  DDA2     2
#define  DDA1     1
#define  DDA0     0

#define  PINA7    7
#define  PINA6    6
#define  PINA5    5
#define  PINA4    4
#define  PINA3    3
#define  PINA2    2
#define  PINA1    1
#define  PINA0    0

/* Port B bits */
#define  PORTB7   7
#define  PORTB6   6
#define  PORTB5   5
#define  PORTB4   4
#define  PORTB3   3
#define  PORTB2   2
#define  PORTB1   1
#define  PORTB0   0
#define  PB7      7
#define  PB6      6
#define  PB5      5
#define  PB4      4
#define  PB3      3
#define  PB2      2
#define  PB1      1
#define  PB0      0

#define  DDB7     7
#define  DDB6     6
#define  DDB5     5
#define  DDB4     4
#define  DDB3     3
#define  DDB2     2
#define  DDB1     1
#define  DDB0     0

#define  PINB7    7
#define  PINB6    6
#define  PINB5    5
#define  PINB4    4
#define  PINB3    3
#define  PINB2    2
#define  PINB1    1
#define  PINB0    0

/* Port C bits */
#define  PORTC7   7
#define  PORTC6   6
#define  PORTC5   5
#define  PORTC4   4
#define  PORTC3   3
#define  PORTC2   2
#define  PORTC1   1
#define  PORTC0   0
#define  PC7      7
#define  PC6      6
#define  PC5      5
#define  PC4      4
#define  PC3      3
#define  PC2      2
#define  PC1      1
#define  PC0      0

#define  DDC7     7
#define  DDC6     6
#define  DDC5     5
#define  DDC4     4
#define  DDC3     3
#define  DDC2     2
#define  DDC1     1
#define  DDC0     0

#define  PINC7    7
#define  PINC6    6
#define  PINC5    5
#define  PINC4    4
#define  PINC3    3
#define  PINC2    2
#define  PINC1    1
#define  PINC0    0

/* Port D bits */
#define  PORTD7   7
#define  PORTD6   6
#define  PORTD5   5
#define  PORTD4   4
#define  PORTD3   3
#define  PORTD2   2
#define  PORTD1   1
#define  PORTD0   0
#define  PD7      7
#define  PD6      6
#define  PD5      5
#define  PD4      4
#define  PD3      3
#define  PD2      2
#define  PD1      1
#define  PD0      0

#define  DDD7     7
#define  DDD6     6
#define  DDD5     5
#define  DDD4     4
#define  DDD3     3
#define  DDD2     2
#define  DDD1     1
#define  DDD0     0

#define  PIND7    7
#define  PIND6    6
#define  PIND5    5
#define  PIND4    4
#define  PIND3    3
#define  PIND2    2
#define  PIND1    1
#define  PIND0    0


/* Lock and Fuse Bits with LPM/SPM instructions */

/* lock bits */
#define  BLB12    5
#define  BLB11    4
#define  BLB02    3
#define  BLB01    2
#define  LB2      1
#define  LB1      0

/* fuses low bits */
#define  BODLEVEL 7
#define  BODEN    6
#define  SUT1     5
#define  SUT0     4
#define  CKSEL3   3
#define  CKSEL2   2
#define  CKSEL1   1
#define  CKSEL0   0

/* fuses high bits */
#define  OCDEN    7
#define  JTAGEN   6
#define  SPIEN    5
#define  CKOPT    4
#define  EESAVE   3
#define  BOOTSZ1  2
#define  BOOTSZ0  1
#define  BOOTRST  0


#endif


#ifdef _MEGA64_INCLUDED_


//#define ADCSRB	
#define  ADTS2    2
#define  ADTS1    1
#define  ADTS0    0
//#define ADCSRA	
#define  ADEN     7
#define  ADSC     6
#define  ADFR     5
#define  ADATE    5
#define  ADIF     4
#define  ADIE     3
#define  ADPS2    2
#define  ADPS1    1
#define  ADPS0    0
//#define ADMUX	
#define  REFS1    7
#define  REFS0    6
#define  ADLAR    5
#define  MUX4     4
#define  MUX3     3
#define  MUX2     2
#define  MUX1     1
#define  MUX0     0

/* Analog Comparator Control and Status Register */
//#define ACSR	
#define  ACD      7
#define  ACBG     6
#define  ACO      5
#define  ACI      4
#define  ACIE     3
#define  ACIC     2
#define  ACIS1    1
#define  ACIS0    0

/* USART0 */
//#define UBRR0H	
//#define UBRR0L	
//#define UCSR0C	
#define  UMSEL0   6
#define  UPM01    5
#define  UPM00    4
#define  USBS0    3
#define  UCSZ01   2
#define  UCSZ00   1
#define  UCPOL0   0
//#define UCSR0B	
#define  RXCIE0   7
#define  TXCIE0   6
#define  UDRIE0   5
#define  RXEN0    4
#define  TXEN0    3
#define  UCSZ02   2
#define  RXB80    1
#define  TXB80    0
//#define UCSR0A	
#define  RXC0     7
#define  TXC0     6
#define  UDRE0    5
#define  FE0      4
#define  DOR0     3
#define  UPE0     2
#define  U2X0     1
#define  MPCM0    0
//#define UDR0	

/* USART1 */
//#define UBRR1H	
//#define UBRR1L	
//#define UCSR1C	
#define  UMSEL1   6
#define  UPM11    5
#define  UPM10    4
#define  USBS1    3
#define  UCSZ11   2
#define  UCSZ10   1
#define  UCPOL1   0
//#define UCSR1B	
#define  RXCIE1   7
#define  TXCIE1   6
#define  UDRIE1   5
#define  RXEN1    4
#define  TXEN1    3
#define  UCSZ12   2
#define  RXB81    1
#define  TXB81    0
//#define UCSR1A	
#define  RXC1     7
#define  TXC1     6
#define  UDRE1    5
#define  FE1      4
#define  DOR1     3
#define  UPE1     2
#define  U2X1     1
#define  MPCM1    0
//#define UDR1	

/* 2-wire SI */
//#define TWBR	
//#define TWSR	
#define  TWPS1    1
#define  TWPS0    0
//#define TWAR	
#define  TWGCE    0
//#define TWDR	
//#define TWCR	
#define  TWINT    7
#define  TWEA     6
#define  TWSTA    5
#define  TWSTO    4
#define  TWWC     3
#define  TWEN     2
#define  TWIE     0

/* SPI */
//#define SPCR	
#define  SPIE     7
#define  SPE      6
#define  DORD     5
#define  MSTR     4
#define  CPOL     3
#define  CPHA     2
#define  SPR1     1
#define  SPR0     0
//#define SPSR	
#define  SPIF     7
#define  WCOL     6
#define  SPI2X    0
//#define SPDR	

/* EEPROM */
//#define EECR	
#define  EERIE    3
#define  EEMWE    2
#define  EEWE     1
#define  EERE     0
//#define EEDR	
//#define EEAR	
//#define EEARL	
//#define EEARH	

/* Special Function IO Register */
//#define SFIOR	
#define  TSM      7
#define  ADHSM    4
#define  ACME     3
#define  PUD      2
#define  PSR0     1
#define  PSR321   0

/* Watchdog Timer Control Register */
//#define WDTCR	
#define  WDCE     4
#define  WDE      3
#define  WDP2     2
#define  WDP1     1
#define  WDP0     0

/* OCDR */
//#define OCDR	
#define  IDRD     7

/* Timer/Counter3 */

#define  FOC3A    7
#define  FOC3B    6
#define  FOC3C    5
//#define TCCR3B	
#define  ICNC3    7
#define  ICES3    6
#define  WGM33    4
#define  WGM32    3
#define  CS32     2
#define  CS31     1
#define  CS30     0
//#define TCCR3A	
#define  COM3A1   7
#define  COM3A0   6
#define  COM3B1   5
#define  COM3B0   4
#define  COM3C1   3
#define  COM3C0   2
#define  WGM31    1
#define  WGM30    0

/* Timer/Counter2 */
//#define OCR2	
//#define TCNT2	
//#define TCCR2	
#define  FOC2     7
#define  WGM20    6
#define  COM21    5
#define  COM20    4
#define  WGM21    3
#define  CS22     2
#define  CS21     1
#define  CS20     0

/* Timer/Counter1 */

#define  FOC1A    7
#define  FOC1B    6
#define  FOC1C    5
//#define TCCR1B	
#define  ICNC1    7
#define  ICES1    6
#define  WGM13    4
#define  WGM12    3
#define  CS12     2
#define  CS11     1
#define  CS10     0
//#define TCCR1A	
#define  COM1A1   7
#define  COM1A0   6
#define  COM1B1   5
#define  COM1B0   4
#define  COM1C1   3
#define  COM1C0   2
#define  WGM11    1
#define  WGM10    0

/* Timer/Counter 0 */
//#define ASSR	
#define  AS0      3
#define  TCN0UB   2
#define  OCR0UB   1
#define  TCR0UB   0
//#define OCR0	
//#define TCNT0	
//#define TCCR0	
#define  FOC0     7
#define  WGM00    6
#define  COM01    5
#define  COM00    4
#define  WGM01    3
#define  CS02     2
#define  CS01     1
#define  CS00     0



/* MCU */
//#define MCUSR	
//#define MCUCSR	
#define  JTD      7
#define  JTRF     4
#define  WDRF     3
#define  BORF     2
#define  EXTRF    1
#define  PORF     0
//#define MCUCR	
#define  SRE      7
#define  SRW10    6
#define  SE       5
#define  SM1      4
#define  SM0      3
#define  SM2      2
#define  IVSEL    1
#define  IVCE     0

/* SPM Control and Status Register */
//#define SPMCSR	
#define  SPMIE    7
#define  RWWSB    6
#define  RWWSRE   4
#define  BLBSET   3
#define  PGWRT    2
#define  PGERS    1
#define  SPMEN    0

/* Timer/Counter Interrupts */
//#define TIFR	
#define  OCF2     7
#define  TOV2     6
#define  ICF1     5
#define  OCF1A    4
#define  OCF1B    3
#define  TOV1     2
#define  OCF0     1
#define  TOV0     0
//#define TIMSK	
#define  OCIE2    7
#define  TOIE2    6
#define  TICIE1   5
#define  OCIE1A   4
#define  OCIE1B   3
#define  TOIE1    2
#define  OCIE0    1
#define  TOIE0    0
//#define ETIFR	
#define  ICF3     5
#define  OCF3A    4
#define  OCF3B    3
#define  TOV3     2
#define  OCF3C    1
#define  OCF1C    0
//#define ETIMSK	
#define  TICIE3   5
#define  OCIE3A   4
#define  OCIE3B   3
#define  TOIE3    2
#define  OCIE3C   1
#define  OCIE1C   0

/* Иxternal Interrupts */
//#define EIFR	
#define  INTF7    7
#define  INTF6    6
#define  INTF5    5
#define  INTF4    4
#define  INTF3    3
#define  INTF2    2
#define  INTF1    1
#define  INTF0    0
//#define EIMSK	
#define  INT7     7
#define  INT6     6
#define  INT5     5
#define  INT4     4
#define  INT3     3
#define  INT2     2
#define  INT1     1
#define  INT0     0
//#define EICRB	
#define  ISC71    7
#define  ISC70    6
#define  ISC61    5
#define  ISC60    4
#define  ISC51    3
#define  ISC50    2
#define  ISC41    1
#define  ISC40    0
//#define EICRA	
#define  ISC31    7
#define  ISC30    6
#define  ISC21    5
#define  ISC20    4
#define  ISC11    3
#define  ISC10    2
#define  ISC01    1
#define  ISC00    0

/* XDIV Divide control register */
//#define XDIV	
#define  XDIVEN   7



/* eXternal Memory Control Register */
//#define XMCRB	
#define  XMBK     7
#define  XMM2     2
#define  XMM1     1
#define  XMM0     0
//#define XMCRA	
#define  SRL2     6
#define  SRL1     5
#define  SRL0     4
#define  SRW01    3
#define  SRW00    2
#define  SRW11    1


/* Port A bits */
#define  PORTA7   7
#define  PORTA6   6
#define  PORTA5   5
#define  PORTA4   4
#define  PORTA3   3
#define  PORTA2   2
#define  PORTA1   1
#define  PORTA0   0
#define  PA7      7
#define  PA6      6
#define  PA5      5
#define  PA4      4
#define  PA3      3
#define  PA2      2
#define  PA1      1
#define  PA0      0

#define  DDA7     7
#define  DDA6     6
#define  DDA5     5
#define  DDA4     4
#define  DDA3     3
#define  DDA2     2
#define  DDA1     1
#define  DDA0     0

#define  PINA7    7
#define  PINA6    6
#define  PINA5    5
#define  PINA4    4
#define  PINA3    3
#define  PINA2    2
#define  PINA1    1
#define  PINA0    0

/* Port B bits */
#define  PORTB7   7
#define  PORTB6   6
#define  PORTB5   5
#define  PORTB4   4
#define  PORTB3   3
#define  PORTB2   2
#define  PORTB1   1
#define  PORTB0   0
#define  PB7      7
#define  PB6      6
#define  PB5      5
#define  PB4      4
#define  PB3      3
#define  PB2      2
#define  PB1      1
#define  PB0      0

#define  DDB7     7
#define  DDB6     6
#define  DDB5     5
#define  DDB4     4
#define  DDB3     3
#define  DDB2     2
#define  DDB1     1
#define  DDB0     0

#define  PINB7    7
#define  PINB6    6
#define  PINB5    5
#define  PINB4    4
#define  PINB3    3
#define  PINB2    2
#define  PINB1    1
#define  PINB0    0

/* Port C bits */
#define  PORTC7   7
#define  PORTC6   6
#define  PORTC5   5
#define  PORTC4   4
#define  PORTC3   3
#define  PORTC2   2
#define  PORTC1   1
#define  PORTC0   0
#define  PC7      7
#define  PC6      6
#define  PC5      5
#define  PC4      4
#define  PC3      3
#define  PC2      2
#define  PC1      1
#define  PC0      0

#define  DDC7     7
#define  DDC6     6
#define  DDC5     5
#define  DDC4     4
#define  DDC3     3
#define  DDC2     2
#define  DDC1     1
#define  DDC0     0

#define  PINC7    7
#define  PINC6    6
#define  PINC5    5
#define  PINC4    4
#define  PINC3    3
#define  PINC2    2
#define  PINC1    1
#define  PINC0    0

/* Port D bits */
#define  PORTD7   7
#define  PORTD6   6
#define  PORTD5   5
#define  PORTD4   4
#define  PORTD3   3
#define  PORTD2   2
#define  PORTD1   1
#define  PORTD0   0
#define  PD7      7
#define  PD6      6
#define  PD5      5
#define  PD4      4
#define  PD3      3
#define  PD2      2
#define  PD1      1
#define  PD0      0

#define  DDD7     7
#define  DDD6     6
#define  DDD5     5
#define  DDD4     4
#define  DDD3     3
#define  DDD2     2
#define  DDD1     1
#define  DDD0     0

#define  PIND7    7
#define  PIND6    6
#define  PIND5    5
#define  PIND4    4
#define  PIND3    3
#define  PIND2    2
#define  PIND1    1
#define  PIND0    0

/* Port E bits */
#define  PORTE7   7
#define  PORTE6   6
#define  PORTE5   5
#define  PORTE4   4
#define  PORTE3   3
#define  PORTE2   2
#define  PORTE1   1
#define  PORTE0   0
#define  PE7      7
#define  PE6      6
#define  PE5      5
#define  PE4      4
#define  PE3      3
#define  PE2      2
#define  PE1      1
#define  PE0      0

#define  DDE7     7
#define  DDE6     6
#define  DDE5     5
#define  DDE4     4
#define  DDE3     3
#define  DDE2     2
#define  DDE1     1
#define  DDE0     0

#define  PINE7    7
#define  PINE6    6
#define  PINE5    5
#define  PINE4    4
#define  PINE3    3
#define  PINE2    2
#define  PINE1    1
#define  PINE0    0

/* Port F bits */
#define  PORTF7   7
#define  PORTF6   6
#define  PORTF5   5
#define  PORTF4   4
#define  PORTF3   3
#define  PORTF2   2
#define  PORTF1   1
#define  PORTF0   0
#define  PF7      7
#define  PF6      6
#define  PF5      5
#define  PF4      4
#define  PF3      3
#define  PF2      2
#define  PF1      1
#define  PF0      0

#define  DDF7     7
#define  DDF6     6
#define  DDF5     5
#define  DDF4     4
#define  DDF3     3
#define  DDF2     2
#define  DDF1     1
#define  DDF0     0

#define  PINF7    7
#define  PINF6    6
#define  PINF5    5
#define  PINF4    4
#define  PINF3    3
#define  PINF2    2
#define  PINF1    1
#define  PINF0    0

/* Port G bits */
#define  PORTG4   4
#define  PORTG3   3
#define  PORTG2   2
#define  PORTG1   1
#define  PORTG0   0
#define  PG4      4
#define  PG3      3
#define  PG2      2
#define  PG1      1
#define  PG0      0

#define  DDG4     4
#define  DDG3     3
#define  DDG2     2
#define  DDG1     1
#define  DDG0     0

#define  PING4    4
#define  PING3    3
#define  PING2    2
#define  PING1    1
#define  PING0    0


/* Lock and Fuse Bits with LPM/SPM instructions */

/* lock bits */
#define  BLB12    5
#define  BLB11    4
#define  BLB02    3
#define  BLB01    2
#define  LB2      1
#define  LB1      0

/* fuses low bits */
#define  BODLEVEL 7
#define  BODEN    6
#define  SUT1     5
#define  SUT0     4
#define  CKSEL3   3
#define  CKSEL2   2
#define  CKSEL1   1
#define  CKSEL0   0

/* fuses high bits */
#define  OCDEN    7
#define  JTAGEN   6
#define  SPIEN    5
#define  CKOPT    4
#define  EESAVE   3
#define  BOOTSZ1  2
#define  BOOTSZ0  1
#define  BOOTRST  0

/* extended fuses */
#define  M103C    1
#define  WDTON    0


#endif



#ifdef _MEGA128_INCLUDED_

/* ADC */
//#define ADC 	
//#define ADCL	
//#define ADCH	
//#define ADCSRA	
#define  ADEN     7
#define  ADSC     6
#define  ADFR     5
#define  ADATE    5
#define  ADIF     4
#define  ADIE     3
#define  ADPS2    2
#define  ADPS1    1
#define  ADPS0    0
//#define ADMUX	
#define  REFS1    7
#define  REFS0    6
#define  ADLAR    5
#define  MUX4     4
#define  MUX3     3
#define  MUX2     2
#define  MUX1     1
#define  MUX0     0

/* Analog Comparator Control and Status Register */
//#define ACSR	
#define  ACD      7
#define  ACBG     6
#define  ACO      5
#define  ACI      4
#define  ACIE     3
#define  ACIC     2
#define  ACIS1    1
#define  ACIS0    0

/* USART0 */
//#define UBRR0H	
//#define UBRR0L	
//#define UCSR0C	
#define  UMSEL0   6
#define  UPM01    5
#define  UPM00    4
#define  USBS0    3
#define  UCSZ01   2
#define  UCSZ00   1
#define  UCPOL0   0
//#define UCSR0B	
#define  RXCIE0   7
#define  TXCIE0   6
#define  UDRIE0   5
#define  RXEN0    4
#define  TXEN0    3
#define  UCSZ02   2
#define  RXB80    1
#define  TXB80    0
//#define UCSR0A	
#define  RXC0     7
#define  TXC0     6
#define  UDRE0    5
#define  FE0      4
#define  DOR0     3
#define  UPE0     2
#define  U2X0     1
#define  MPCM0    0
//#define UDR0	

/* USART1 */
//#define UBRR1H	
//#define UBRR1L	
//#define UCSR1C	
#define  UMSEL1   6
#define  UPM11    5
#define  UPM10    4
#define  USBS1    3
#define  UCSZ11   2
#define  UCSZ10   1
#define  UCPOL1   0
//#define UCSR1B	
#define  RXCIE1   7
#define  TXCIE1   6
#define  UDRIE1   5
#define  RXEN1    4
#define  TXEN1    3
#define  UCSZ12   2
#define  RXB81    1
#define  TXB81    0
//#define UCSR1A	
#define  RXC1     7
#define  TXC1     6
#define  UDRE1    5
#define  FE1      4
#define  DOR1     3
#define  UPE1     2
#define  U2X1     1
#define  MPCM1    0


/* 2-wire SI */
//#define TWBR	
//#define TWSR	
#define  TWPS1    1
#define  TWPS0    0
//#define TWAR	
#define  TWGCE    0
//#define TWDR	
//#define TWCR	
#define  TWINT    7
#define  TWEA     6
#define  TWSTA    5
#define  TWSTO    4
#define  TWWC     3
#define  TWEN     2
#define  TWIE     0

/* SPI */
//#define SPCR	
#define  SPIE     7
#define  SPE      6
#define  DORD     5
#define  MSTR     4
#define  CPOL     3
#define  CPHA     2
#define  SPR1     1
#define  SPR0     0
//#define SPSR	
#define  SPIF     7
#define  WCOL     6
#define  SPI2X    0
//#define SPDR	

/* EEPROM */
//#define EECR	
#define  EERIE    3
#define  EEMWE    2
#define  EEWE     1
#define  EERE     0
//#define EEDR	
//#define EEAR	
//#define EEARL	
//#define EEARH	

/* Special Function IO Register */
//#define SFIOR	
#define  TSM      7
#define  ADHSM    4
#define  ACME     3
#define  PUD      2
#define  PSR0     1
#define  PSR321   0

/* Watchdog Timer Control Register */
//#define WDTCR	
#define  WDCE     4
#define  WDE      3
#define  WDP2     2
#define  WDP1     1
#define  WDP0     0

/* OCDR */
//#define OCDR	
#define  IDRD     7

/* Timer/Counter3 */

#define  FOC3A    7
#define  FOC3B    6
#define  FOC3C    5
//#define TCCR3B	
#define  ICNC3    7
#define  ICES3    6
#define  WGM33    4
#define  WGM32    3
#define  CS32     2
#define  CS31     1
#define  CS30     0
//#define TCCR3A	
#define  COM3A1   7
#define  COM3A0   6
#define  COM3B1   5
#define  COM3B0   4
#define  COM3C1   3
#define  COM3C0   2
#define  WGM31    1
#define  WGM30    0

/* Timer/Counter2 */
//#define OCR2	
//#define TCNT2	
//#define TCCR2	
#define  FOC2     7
#define  WGM20    6
#define  COM21    5
#define  COM20    4
#define  WGM21    3
#define  CS22     2
#define  CS21     1
#define  CS20     0

/* Timer/Counter1 */

#define  FOC1A    7
#define  FOC1B    6
#define  FOC1C    5
//#define TCCR1B	
#define  ICNC1    7
#define  ICES1    6
#define  WGM13    4
#define  WGM12    3
#define  CS12     2
#define  CS11     1
#define  CS10     0
//#define TCCR1A	
#define  COM1A1   7
#define  COM1A0   6
#define  COM1B1   5
#define  COM1B0   4
#define  COM1C1   3
#define  COM1C0   2
#define  WGM11    1
#define  WGM10    0

/* Timer/Counter 0 */
//#define ASSR	
#define  AS0      3
#define  TCN0UB   2
#define  OCR0UB   1
#define  TCR0UB   0
//#define OCR0	
//#define TCNT0	
//#define TCCR0	
#define  FOC0     7
#define  WGM00    6
#define  COM01    5
#define  COM00    4
#define  WGM01    3
#define  CS02     2
#define  CS01     1
#define  CS00     0




/* MCU */
//#define MCUSR	
//#define MCUCSR	
#define  JTD      7
#define  JTRF     4
#define  WDRF     3
#define  BORF     2
#define  EXTRF    1
#define  PORF     0
//#define MCUCR	
#define  SRE      7
#define  SRW10    6
#define  SE       5
#define  SM1      4
#define  SM0      3
#define  SM2      2
#define  IVSEL    1
#define  IVCE     0

/* SPM Control and Status Register */
//#define SPMCSR	
#define  SPMIE    7
#define  RWWSB    6
#define  RWWSRE   4
#define  BLBSET   3
#define  PGWRT    2
#define  PGERS    1
#define  SPMEN    0

/* Timer/Counter Interrupts */
//#define TIFR	
#define  OCF2     7
#define  TOV2     6
#define  ICF1     5
#define  OCF1A    4
#define  OCF1B    3
#define  TOV1     2
#define  OCF0     1
#define  TOV0     0
//#define TIMSK	
#define  OCIE2    7
#define  TOIE2    6
#define  TICIE1   5
#define  OCIE1A   4
#define  OCIE1B   3
#define  TOIE1    2
#define  OCIE0    1
#define  TOIE0    0
//#define ETIFR	
#define  ICF3     5
#define  OCF3A    4
#define  OCF3B    3
#define  TOV3     2
#define  OCF3C    1
#define  OCF1C    0
//#define ETIMSK	
#define  TICIE3   5
#define  OCIE3A   4
#define  OCIE3B   3
#define  TOIE3    2
#define  OCIE3C   1
#define  OCIE1C   0

/* Иxternal Interrupts */
//#define EIFR	
#define  INTF7    7
#define  INTF6    6
#define  INTF5    5
#define  INTF4    4
#define  INTF3    3
#define  INTF2    2
#define  INTF1    1
#define  INTF0    0
//#define EIMSK	
#define  INT7     7
#define  INT6     6
#define  INT5     5
#define  INT4     4
#define  INT3     3
#define  INT2     2
#define  INT1     1
#define  INT0     0
//#define EICRB	
#define  ISC71    7
#define  ISC70    6
#define  ISC61    5
#define  ISC60    4
#define  ISC51    3
#define  ISC50    2
#define  ISC41    1
#define  ISC40    0
//#define EICRA	
#define  ISC31    7
#define  ISC30    6
#define  ISC21    5
#define  ISC20    4
#define  ISC11    3
#define  ISC10    2
#define  ISC01    1
#define  ISC00    0



/* XDIV Divide control register */
//#define XDIV	
#define  XDIVEN   7



/* eXternal Memory Control Register */
//#define XMCRB	
#define  XMBK     7
#define  XMM2     2
#define  XMM1     1
#define  XMM0     0
//#define XMCRA	
#define  SRL2     6
#define  SRL1     5
#define  SRL0     4
#define  SRW01    3
#define  SRW00    2
#define  SRW11    1


/* Port A bits */
#define  PORTA7   7
#define  PORTA6   6
#define  PORTA5   5
#define  PORTA4   4
#define  PORTA3   3
#define  PORTA2   2
#define  PORTA1   1
#define  PORTA0   0
#define  PA7      7
#define  PA6      6
#define  PA5      5
#define  PA4      4
#define  PA3      3
#define  PA2      2
#define  PA1      1
#define  PA0      0

#define  DDA7     7
#define  DDA6     6
#define  DDA5     5
#define  DDA4     4
#define  DDA3     3
#define  DDA2     2
#define  DDA1     1
#define  DDA0     0

#define  PINA7    7
#define  PINA6    6
#define  PINA5    5
#define  PINA4    4
#define  PINA3    3
#define  PINA2    2
#define  PINA1    1
#define  PINA0    0

/* Port B bits */
#define  PORTB7   7
#define  PORTB6   6
#define  PORTB5   5
#define  PORTB4   4
#define  PORTB3   3
#define  PORTB2   2
#define  PORTB1   1
#define  PORTB0   0
#define  PB7      7
#define  PB6      6
#define  PB5      5
#define  PB4      4
#define  PB3      3
#define  PB2      2
#define  PB1      1
#define  PB0      0

#define  DDB7     7
#define  DDB6     6
#define  DDB5     5
#define  DDB4     4
#define  DDB3     3
#define  DDB2     2
#define  DDB1     1
#define  DDB0     0

#define  PINB7    7
#define  PINB6    6
#define  PINB5    5
#define  PINB4    4
#define  PINB3    3
#define  PINB2    2
#define  PINB1    1
#define  PINB0    0

/* Port C bits */
#define  PORTC7   7
#define  PORTC6   6
#define  PORTC5   5
#define  PORTC4   4
#define  PORTC3   3
#define  PORTC2   2
#define  PORTC1   1
#define  PORTC0   0
#define  PC7      7
#define  PC6      6
#define  PC5      5
#define  PC4      4
#define  PC3      3
#define  PC2      2
#define  PC1      1
#define  PC0      0

#define  DDC7     7
#define  DDC6     6
#define  DDC5     5
#define  DDC4     4
#define  DDC3     3
#define  DDC2     2
#define  DDC1     1
#define  DDC0     0

#define  PINC7    7
#define  PINC6    6
#define  PINC5    5
#define  PINC4    4
#define  PINC3    3
#define  PINC2    2
#define  PINC1    1
#define  PINC0    0

/* Port D bits */
#define  PORTD7   7
#define  PORTD6   6
#define  PORTD5   5
#define  PORTD4   4
#define  PORTD3   3
#define  PORTD2   2
#define  PORTD1   1
#define  PORTD0   0
#define  PD7      7
#define  PD6      6
#define  PD5      5
#define  PD4      4
#define  PD3      3
#define  PD2      2
#define  PD1      1
#define  PD0      0

#define  DDD7     7
#define  DDD6     6
#define  DDD5     5
#define  DDD4     4
#define  DDD3     3
#define  DDD2     2
#define  DDD1     1
#define  DDD0     0

#define  PIND7    7
#define  PIND6    6
#define  PIND5    5
#define  PIND4    4
#define  PIND3    3
#define  PIND2    2
#define  PIND1    1
#define  PIND0    0

/* Port E bits */
#define  PORTE7   7
#define  PORTE6   6
#define  PORTE5   5
#define  PORTE4   4
#define  PORTE3   3
#define  PORTE2   2
#define  PORTE1   1
#define  PORTE0   0
#define  PE7      7
#define  PE6      6
#define  PE5      5
#define  PE4      4
#define  PE3      3
#define  PE2      2
#define  PE1      1
#define  PE0      0

#define  DDE7     7
#define  DDE6     6
#define  DDE5     5
#define  DDE4     4
#define  DDE3     3
#define  DDE2     2
#define  DDE1     1
#define  DDE0     0

#define  PINE7    7
#define  PINE6    6
#define  PINE5    5
#define  PINE4    4
#define  PINE3    3
#define  PINE2    2
#define  PINE1    1
#define  PINE0    0

/* Port F bits */
#define  PORTF7   7
#define  PORTF6   6
#define  PORTF5   5
#define  PORTF4   4
#define  PORTF3   3
#define  PORTF2   2
#define  PORTF1   1
#define  PORTF0   0
#define  PF7      7
#define  PF6      6
#define  PF5      5
#define  PF4      4
#define  PF3      3
#define  PF2      2
#define  PF1      1
#define  PF0      0

#define  DDF7     7
#define  DDF6     6
#define  DDF5     5
#define  DDF4     4
#define  DDF3     3
#define  DDF2     2
#define  DDF1     1
#define  DDF0     0

#define  PINF7    7
#define  PINF6    6
#define  PINF5    5
#define  PINF4    4
#define  PINF3    3
#define  PINF2    2
#define  PINF1    1
#define  PINF0    0

/* Port G bits */
#define  PORTG4   4
#define  PORTG3   3
#define  PORTG2   2
#define  PORTG1   1
#define  PORTG0   0
#define  PG4      4
#define  PG3      3
#define  PG2      2
#define  PG1      1
#define  PG0      0

#define  DDG4     4
#define  DDG3     3
#define  DDG2     2
#define  DDG1     1
#define  DDG0     0

#define  PING4    4
#define  PING3    3
#define  PING2    2
#define  PING1    1
#define  PING0    0


/* Lock and Fuse Bits with LPM/SPM instructions */

/* lock bits */
#define  BLB12    5
#define  BLB11    4
#define  BLB02    3
#define  BLB01    2
#define  LB2      1
#define  LB1      0

/* fuses low bits */
#define  BODLEVEL 7
#define  BODEN    6
#define  SUT1     5
#define  SUT0     4
#define  CKSEL3   3
#define  CKSEL2   2
#define  CKSEL1   1
#define  CKSEL0   0

/* fuses high bits */
#define  OCDEN    7
#define  JTAGEN   6
#define  SPIEN    5
#define  CKOPT    4
#define  EESAVE   3
#define  BOOTSZ1  2
#define  BOOTSZ0  1
#define  BOOTRST  0

/* extended fuses */
#define  M103C    1
#define  WDTON    0


#endif








// avr123.nm.ru  
 
// After #include <this file>   you can  
// use b_1010_1100 isted of 0b10101100 
 
#define b_0000_0000 0 
#define b_0000_0001 1 
#define b_0000_0010 2 
#define b_0000_0011 3 
#define b_0000_0100 4 
#define b_0000_0101 5 
#define b_0000_0110 6 
#define b_0000_0111 7 
#define b_0000_1000 8 
#define b_0000_1001 9 
#define b_0000_1010 10 
#define b_0000_1011 11 
#define b_0000_1100 12 
#define b_0000_1101 13 
#define b_0000_1110 14 
#define b_0000_1111 15 
#define b_0001_0000 16 
#define b_0001_0001 17 
#define b_0001_0010 18 
#define b_0001_0011 19 
#define b_0001_0100 20 
#define b_0001_0101 21 
#define b_0001_0110 22 
#define b_0001_0111 23 
#define b_0001_1000 24 
#define b_0001_1001 25 
#define b_0001_1010 26 
#define b_0001_1011 27 
#define b_0001_1100 28 
#define b_0001_1101 29 
#define b_0001_1110 30 
#define b_0001_1111 31 
#define b_0010_0000 32 
#define b_0010_0001 33 
#define b_0010_0010 34 
#define b_0010_0011 35 
#define b_0010_0100 36 
#define b_0010_0101 37 
#define b_0010_0110 38 
#define b_0010_0111 39 
#define b_0010_1000 40 
#define b_0010_1001 41 
#define b_0010_1010 42 
#define b_0010_1011 43 
#define b_0010_1100 44 
#define b_0010_1101 45 
#define b_0010_1110 46 
#define b_0010_1111 47 
#define b_0011_0000 48 
#define b_0011_0001 49 
#define b_0011_0010 50 
#define b_0011_0011 51 
#define b_0011_0100 52 
#define b_0011_0101 53 
#define b_0011_0110 54 
#define b_0011_0111 55 
#define b_0011_1000 56 
#define b_0011_1001 57 
#define b_0011_1010 58 
#define b_0011_1011 59 
#define b_0011_1100 60 
#define b_0011_1101 61 
#define b_0011_1110 62 
#define b_0011_1111 63 
#define b_0100_0000 64 
#define b_0100_0001 65 
#define b_0100_0010 66 
#define b_0100_0011 67 
#define b_0100_0100 68 
#define b_0100_0101 69 
#define b_0100_0110 70 
#define b_0100_0111 71 
#define b_0100_1000 72 
#define b_0100_1001 73 
#define b_0100_1010 74 
#define b_0100_1011 75 
#define b_0100_1100 76 
#define b_0100_1101 77 
#define b_0100_1110 78 
#define b_0100_1111 79 
#define b_0101_0000 80 
#define b_0101_0001 81 
#define b_0101_0010 82 
#define b_0101_0011 83 
#define b_0101_0100 84 
#define b_0101_0101 85 
#define b_0101_0110 86 
#define b_0101_0111 87 
#define b_0101_1000 88 
#define b_0101_1001 89 
#define b_0101_1010 90 
#define b_0101_1011 91 
#define b_0101_1100 92 
#define b_0101_1101 93 
#define b_0101_1110 94 
#define b_0101_1111 95 
#define b_0110_0000 96 
#define b_0110_0001 97 
#define b_0110_0010 98 
#define b_0110_0011 99 
#define b_0110_0100 100 
#define b_0110_0101 101 
#define b_0110_0110 102 
#define b_0110_0111 103 
#define b_0110_1000 104 
#define b_0110_1001 105 
#define b_0110_1010 106 
#define b_0110_1011 107 
#define b_0110_1100 108 
#define b_0110_1101 109 
#define b_0110_1110 110 
#define b_0110_1111 111 
#define b_0111_0000 112 
#define b_0111_0001 113 
#define b_0111_0010 114 
#define b_0111_0011 115 
#define b_0111_0100 116 
#define b_0111_0101 117 
#define b_0111_0110 118 
#define b_0111_0111 119 
#define b_0111_1000 120 
#define b_0111_1001 121 
#define b_0111_1010 122 
#define b_0111_1011 123 
#define b_0111_1100 124 
#define b_0111_1101 125 
#define b_0111_1110 126 
#define b_0111_1111 127 
#define b_1000_0000 128 
#define b_1000_0001 129 
#define b_1000_0010 130 
#define b_1000_0011 131 
#define b_1000_0100 132 
#define b_1000_0101 133 
#define b_1000_0110 134 
#define b_1000_0111 135 
#define b_1000_1000 136 
#define b_1000_1001 137 
#define b_1000_1010 138 
#define b_1000_1011 139 
#define b_1000_1100 140 
#define b_1000_1101 141 
#define b_1000_1110 142 
#define b_1000_1111 143 
#define b_1001_0000 144 
#define b_1001_0001 145 
#define b_1001_0010 146 
#define b_1001_0011 147 
#define b_1001_0100 148 
#define b_1001_0101 149 
#define b_1001_0110 150 
#define b_1001_0111 151 
#define b_1001_1000 152 
#define b_1001_1001 153 
#define b_1001_1010 154 
#define b_1001_1011 155 
#define b_1001_1100 156 
#define b_1001_1101 157 
#define b_1001_1110 158 
#define b_1001_1111 159 
#define b_1010_0000 160 
#define b_1010_0001 161 
#define b_1010_0010 162 
#define b_1010_0011 163 
#define b_1010_0100 164 
#define b_1010_0101 165 
#define b_1010_0110 166 
#define b_1010_0111 167 
#define b_1010_1000 168 
#define b_1010_1001 169 
#define b_1010_1010 170 
#define b_1010_1011 171 
#define b_1010_1100 172 
#define b_1010_1101 173 
#define b_1010_1110 174 
#define b_1010_1111 175 
#define b_1011_0000 176 
#define b_1011_0001 177 
#define b_1011_0010 178 
#define b_1011_0011 179 
#define b_1011_0100 180 
#define b_1011_0101 181 
#define b_1011_0110 182 
#define b_1011_0111 183 
#define b_1011_1000 184 
#define b_1011_1001 185 
#define b_1011_1010 186 
#define b_1011_1011 187 
#define b_1011_1100 188 
#define b_1011_1101 189 
#define b_1011_1110 190 
#define b_1011_1111 191 
#define b_1100_0000 192 
#define b_1100_0001 193 
#define b_1100_0010 194 
#define b_1100_0011 195 
#define b_1100_0100 196 
#define b_1100_0101 197 
#define b_1100_0110 198 
#define b_1100_0111 199 
#define b_1100_1000 200 
#define b_1100_1001 201 
#define b_1100_1010 202 
#define b_1100_1011 203 
#define b_1100_1100 204 
#define b_1100_1101 205 
#define b_1100_1110 206 
#define b_1100_1111 207 
#define b_1101_0000 208 
#define b_1101_0001 209 
#define b_1101_0010 210 
#define b_1101_0011 211 
#define b_1101_0100 212 
#define b_1101_0101 213 
#define b_1101_0110 214 
#define b_1101_0111 215 
#define b_1101_1000 216 
#define b_1101_1001 217 
#define b_1101_1010 218 
#define b_1101_1011 219 
#define b_1101_1100 220 
#define b_1101_1101 221 
#define b_1101_1110 222 
#define b_1101_1111 223 
#define b_1110_0000 224 
#define b_1110_0001 225 
#define b_1110_0010 226 
#define b_1110_0011 227 
#define b_1110_0100 228 
#define b_1110_0101 229 
#define b_1110_0110 230 
#define b_1110_0111 231 
#define b_1110_1000 232 
#define b_1110_1001 233 
#define b_1110_1010 234 
#define b_1110_1011 235 
#define b_1110_1100 236 
#define b_1110_1101 237 
#define b_1110_1110 238 
#define b_1110_1111 239 
#define b_1111_0000 240 
#define b_1111_0001 241 
#define b_1111_0010 242 
#define b_1111_0011 243 
#define b_1111_0100 244 
#define b_1111_0101 245 
#define b_1111_0110 246 
#define b_1111_0111 247 
#define b_1111_1000 248 
#define b_1111_1001 249 
#define b_1111_1010 250 
#define b_1111_1011 251 
#define b_1111_1100 252 
#define b_1111_1101 253 
#define b_1111_1110 254 
#define b_1111_1111 255 
