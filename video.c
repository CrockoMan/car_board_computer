// Проверка установки первого бита if((Var&0b00000001)!=0)     if(!(PINC & (1 << n))) где n - номер бита
//#define SetBit(x)    |= (1<<x) 
//#define ClearBit(x)  &=~(1<<x) 
//#define InvertBit(x) ^=(1<<x) 
// x - номер бита в регистре
// использование:
//PORTB SetBit   (5);  // "установить"  бит5
//PORTB ClearBit (2);  // "очистить"  бит2
//PORTB InvertBit(6);  // инвертировать бит6

 
//Генерация видео и звука
//D.5 is sync:1000 ohm + diode to 75 ohm resistor
//D.6 is video:330 ohm + diode to 75 ohm resistor  
//B.3 is sound  10k resistor to GND

#pragma regalloc-    //Ручной выбор хранения переменных в регистрах
#pragma optsize-     //Оптимизация для скорости
                    
#include <Mega32.h>   
#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include <delay.h>   
#include <m8_128.h>
#include <dh.h>


//-------------------------------------------------------------------------------------------
//#define LCDDEBUG
//-------------------------------------------------------------------------------------------



// DS1302 Для RTC
#asm
   .equ __ds1302_port=0x18 ;PORTB
   .equ __ds1302_io=1
   .equ __ds1302_sclk=0
   .equ __ds1302_rst=2
#endasm
#include <ds1302.h>

// I2C Bus functions
#asm
   .equ __i2c_port=0x18 ;PORTB
   .equ __sda_bit=3
   .equ __scl_bit=4
#endasm
#include <i2c.h>

#ifdef LCDDEBUG
        // Alphanumeric LCD Module functions
        #asm
           .equ __lcd_port=0x15 ;PORTC
        #endasm
        #include <lcd.h>
#endif


// DS1621 Thermometer/Thermostat functions
#include <ds1621.h>




//Циклы = 63.625 * 16      NTSC = 63.55 
//Полукадр периодичностью 1/60 sec
#define lineTime 1018
 
#define ScreenTop 30
#define ScreenBot 230
#define ADCChannels 3
#define MaxADC 10
#define LITERS 70
#define LITERSADC   90          // Длина масива для округления ADC по Fuel

#ifdef LCDDEBUG
   #define USTART     111          // Напряжение, которое считается в тестовом режиме.
#else
   #define USTART     133          // Напряжение, которое считается при запущенном генераторе.
#endif


//v1 - v8 и i должны быть в регистрах 
register char v1 @4; 
register char v2 @5;
register char v3 @6;
register char v4 @7;
register char v5 @8;
register char v6 @9;
register char v7 @10;
register char v8 @11; 
register int i @12;

#pragma regalloc+ 

char syncON, syncOFF,ADCType,cPWM=0; 
unsigned char LightOn=0,EEYear=0,EEMonth=0,EEDay=0,EEHour=0,EEMin=0;
unsigned char Hour=0,Min=0,Sec=0,TempDay=0,YearSummer,YearWinter;
unsigned int cU[50],dU;
int LineCount;
int time;
//int Temperature[2][MaxADC];
unsigned int aFuel[LITERSADC];
long int Fuel=0; 

//Анимация
char x, y, vx, vy;              // s,

char screen[1600], t, ts[10],ts2[2]; 
//char cu1[]="DIE HARD"; 
//char cu2[]="30.01.2007";    


// Таблица перевода результата ADC в литры
flash int aFuelValue[LITERS][2]={1,857,
                                 2,850,
                                 3,847,
                                 4,845,
                                 5,843,
                                 6,840,
                                 7,833,
                                 8,818,
                                 9,797,
                                 10,772,
                                 11,756,
                                 12,727,
                                 13,720,
                                 14,711,
                                 15,686,
                                 16,681,
                                 17,667,
                                 18,680,
                                 19,660,
                                 20,637,
                                 21,625,
                                 22,623,
                                 23,621,
                                 24,617,
                                 25,610,
                                 26,585,
                                 27,583,
                                 28,578,
                                 29,575,
                                 30,550,
                                 31,547,
                                 32,484,
                                 33,464,
                                 34,458,
                                 35,440,
                                 36,434,
                                 37,427,
                                 38,420,
                                 39,406,
                                 40,401,
                                 41,383,
                                 42,365,
                                 43,363,
                                 44,347,
                                 45,340,
                                 46,333,
                                 47,326,
                                 48,319,
                                 49,312,
                                 50,305,
                                 51,298,
                                 52,291,
                                 53,275,
                                 54,259,
                                 55,243,
                                 56,227,
                                 57,212,
                                 58,196,
                                 59,242,
                                 60,164,
                                 61,149,
                                 62,132,
                                 63,117,
                                 64,102,
                                 65,1,
                                 66,1,
                                 67,1,
                                 68,1,
                                 69,1,
                                 70,1};


//Ноты
//До средняя + 1 октава
flash char notes[] = {239,213,189,179,159,142,126,
		120,106,94,90,80,71,63,60,0,0,0,0};  
char note, musicT;
                 			
//Таблица отрисовки одной точки
//Однобитовая маска
flash char pos[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};			

//Таблица символов
//Шрифт 5x7
flash char bitmap[68][7]={ 
	//0
	0b01110000,
	0b10001000,
	0b10011000,
	0b10101000,
	0b11001000,
	0b10001000,
	0b01110000,
	//1
	0b00100000,
	0b01100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b01110000,  
	//2
	0b01110000,
	0b10001000,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b11111000,
        //3
	0b11111000,
	0b00010000,
	0b00100000,
	0b00010000,
	0b00001000,
	0b10001000,
	0b01110000,
	//4
	0b00010000,
	0b00110000,
	0b01010000,
	0b10010000,
	0b11111000,
	0b00010000,
	0b00010000,
	//5
	0b11111000,
	0b10000000,
	0b11110000,
	0b00001000,
	0b00001000,
	0b10001000,
	0b01110000,
	//6
	0b01000000,
	0b10000000,
	0b10000000,
	0b11110000,
	0b10001000,
	0b10001000,
	0b01110000,
	//7
	0b11111000,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000,
	0b10000000,
	//8
	0b01110000,
	0b10001000,
	0b10001000,
	0b01110000,
	0b10001000,
	0b10001000,
	0b01110000,
	//9
	0b01110000,
	0b10001000,
	0b10001000,
	0b01111000,
	0b00001000,
	0b00001000,
	0b00010000,  
	//A
	0b01110000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b11111000,
	0b10001000,
	0b10001000,
	//B
	0b11110000,
	0b10001000,
	0b10001000,
	0b11110000,
	0b10001000,
	0b10001000,
	0b11110000,
	//C
	0b01110000,
	0b10001000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10001000,
	0b01110000,
	//D
	0b11110000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b11110000,
	//E
	0b11111000,
	0b10000000,
	0b10000000,
	0b11111000,
	0b10000000,
	0b10000000,
	0b11111000,
	//F
	0b11111000,
	0b10000000,
	0b10000000,
	0b11111000,
	0b10000000,
	0b10000000,
	0b10000000,
	//G
	0b01110000,
	0b10001000,
	0b10000000,
	0b10011000,
	0b10001000,
	0b10001000,
	0b01110000,
	//H
	0b10001000,
	0b10001000,
	0b10001000,
	0b11111000,
	0b10001000,
	0b10001000,
	0b10001000,
	//I
	0b01110000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b01110000,
	//J
	0b00111000,
	0b00010000,
	0b00010000,
	0b00010000,
	0b00010000,
	0b10010000,
	0b01100000,
	//K
	0b10001000,
	0b10010000,
	0b10100000,
	0b11000000,
	0b10100000,
	0b10010000,
	0b10001000,
	//L
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b11111000,
	//M
	0b10001000,
	0b11011000,
	0b10101000,
	0b10101000,
	0b10001000,
	0b10001000,
	0b10001000,
	//N
	0b10001000,
	0b10001000,
	0b11001000,
	0b10101000,
	0b10011000,
	0b10001000,
	0b10001000,
	//O
	0b01110000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b01110000,
	//P
	0b11110000,
	0b10001000,
	0b10001000,
	0b11110000,
	0b10000000,
	0b10000000,
	0b10000000,
	//Q
	0b01110000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10101000,
	0b10010000,
	0b01101000,
	//R
	0b11110000,
	0b10001000,
	0b10001000,
	0b11110000,
	0b10100000,
	0b10010000,
	0b10001000,
	//S
	0b01111000,
	0b10000000,
	0b10000000,
	0b01110000,
	0b00001000,
	0b00001000,
	0b11110000,
	//T
	0b11111000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	//U
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b01110000,
	//V
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b01010000,
	0b00100000,
	//W
	0b10001000,
	0b10001000,
	0b10001000,
	0b10101000,
	0b10101000,
	0b10101000,
	0b01010000,
	//X
	0b10001000,
	0b10001000,
	0b01010000,
	0b00100000,
	0b01010000,
	0b10001000,
	0b10001000,
	//Y
	0b10001000,
	0b10001000,
	0b10001000,
	0b01010000,
	0b00100000,
	0b00100000,
	0b00100000,
	//Z
	0b11111000,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000,
	0b11111000,
	//знак градуса C
	0b01000000,
	0b10100000,
	0b01000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// :
	0b00000000,
	0b00000000,
	0b00100000,
	0b00000000,
	0b00100000,
	0b00000000,
	0b00000000,
	//Space
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	//Dot
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11000000,
	0b11000000,
	//Тире
	0b00000000,
	0b00000000,
	0b00000000,
	0b01110000,
	0b00000000,
	0b00000000,
	0b00000000,
	//a
	0b00000000,
	0b00000000,
	0b01111000,
	0b00000100,
	0b00110100,
	0b01000100,
	0b00111010,
	//b
	0b00000000,
	0b01000000,
	0b11000000,
	0b01111000,
	0b01000010,
	0b01000010,
	0b01111000,
	//c
	0b00000000,
	0b00000000,
	0b01111100,
	0b10000000,
	0b10000000,
	0b10000000,
	0b01111100,
	//d
	0b00000000,
	0b00000100,
	0b00000110,
	0b01111100,
	0b10000100,
	0b10000100,
	0b01111100,
	//e
	0b00000000,
	0b00000000,
	0b01111000,
	0b10000100,
	0b11111100,
	0b10000000,
	0b01111100,
	//f
	0b00000000,
	0b00000000,
	0b00011100,
	0b00100000,
	0b11111000,
	0b00100000,
	0b00100000,
	//g
	0b00000000,
	0b00000000,
	0b00111110,
	0b01000010,
	0b00111110,
	0b00000010,
	0b01111100,
	//h
	0b00000000,
	0b10000000,
	0b10000000,
	0b11110000,
	0b10000100,
	0b10000100,
	0b10000100,
	//i
	0b00000000,
	0b00010000,
	0b00000000,
	0b00110000,
	0b00010000,
	0b00010000,
	0b00111000,
	//j
	0b00000000,
	0b00001000,
	0b00000000,
	0b00011000,
	0b00001000,
	0b10001000,
	0b01110000,
	//k
	0b00000000,
	0b01000000,
	0b01001000,
	0b01010000,
	0b01100000,
	0b01010000,
	0b01001000,
	//l
	0b00000000,
	0b01100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b01110000,
	//m
	0b00000000,
	0b00000000,
	0b11001100,
	0b10010010,
	0b10010010,
	0b10010010,
	0b10010010,
	//n
	0b00000000,
	0b00000000,
	0b01011000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b01000100,
	//o
	0b00000000,
	0b00000000,
	0b00011000,
	0b01000010,
	0b01000010,
	0b01000010,
	0b00111000,
	//p
	0b00000000,
	0b00000000,
	0b11111000,
	0b10000100,
	0b10000100,
	0b11111000,
	0b10000000,
	//q
	0b00000000,
	0b01110100,
	0b10000100,
	0b10000100,
	0b01111100,
	0b00000100,
	0b00000110,
	//r
	0b00000000,
	0b00000000,
	0b01011100,
	0b01100010,
	0b01000000,
	0b01000000,
	0b01000000,
	//s
	0b00000000,
	0b00000000,
	0b00011100,
	0b01000000,
	0b00111000,
	0b00000010,
	0b00111100,
	//t
	0b00000000,
	0b00100000,
	0b00100000,
	0b01110000,
	0b00100000,
	0b00100010,
	0b00011000, 
	//u
	0b00000000,
	0b00000000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b01000100,
	0b00110010, 
	//v
	0b00000000,
	0b00000000,
	0b01000100,
	0b01000100,
	0b01000100,
	0b00101000,
	0b00010000,
	//w
	0b00000000,
	0b00000000,
	0b10010010,
	0b10010010,
	0b10010010,
	0b10010010,
	0b01001000,
	//x
	0b00000000,
	0b00000000,
	0b10000010,
	0b01000100,
	0b00111000,
	0b01000100,
	0b10000010,
	//y
	0b00000000,
	0b00000000,
	0b01000010,
	0b01000010,
	0b00111110,
	0b00000010,
	0b01111000,
	//z
	0b00000000,
	0b00000000,
	0b11111110,
	0b00000110,
	0b00011000,
	0b01100000,
	0b11111110,
	//+ 
	0b00000000,
	0b00100000,
	0b00100000,
	0b11111000,
	0b00100000,
	0b00100000,
	0b00000000	};


//================================ 
//Шрифт 3x5
//Выводится на экран в x-координате, деленной на 4
flash char smallbitmap[41][5]={ 
	//0
        0b11101110,
	0b10101010,
	0b10101010,
	0b10101010,
	0b11101110,
	//1
	0b01000100,
	0b11001100,
	0b01000100,
	0b01000100,
	0b11101110,
	//2
	0b11101110,
	0b00100010,
	0b11101110,
	0b10001000,
	0b11101110,
	//3
	0b11101110,
	0b00100010,
	0b11101110,
	0b00100010,
	0b11101110,
	//4
	0b10101010,
	0b10101010,
	0b11101110,
	0b00100010,
	0b00100010,
	//5
	0b11101110,
	0b10001000,
	0b11101110,
	0b00100010,
	0b11101110,
	//6
	0b11001100,
	0b10001000,
	0b11101110,
	0b10101010,
	0b11101110,
	//7
	0b11101110,
	0b00100010,
	0b01000100,
	0b10001000,
	0b10001000,
	//8
	0b11101110,
	0b10101010,
	0b11101110,
	0b10101010,
	0b11101110,
	//9
	0b11101110,
	0b10101010,
	0b11101110,
	0b00100010,
	0b01100110,
	//:
	0b00000000,
	0b01000100,
	0b00000000,
	0b01000100,
	0b00000000,
	//=
	0b00000000,
	0b11101110,
	0b00000000,
	0b11101110,
	0b00000000,
	//blank
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	//A
	0b11101110,
	0b10101010,
	0b11101110,
	0b10101010,
	0b10101010,
	//B
	0b11001100,
	0b10101010,
	0b11101110,
	0b10101010,
	0b11001100,
	//C
	0b11101110,
	0b10001000,
	0b10001000,
	0b10001000,
	0b11101110,
	//D
	0b11001100,
	0b10101010,
	0b10101010,
	0b10101010,
	0b11001100,
	//E
	0b11101110,
	0b10001000,
	0b11101110,
	0b10001000,
	0b11101110,
	//F
	0b11101110,
	0b10001000,
	0b11101110,
	0b10001000,
	0b10001000,
	//G
	0b11101110,
	0b10001000,
	0b10001000,
	0b10101010,
	0b11101110,
	//H
	0b10101010,
	0b10101010,
	0b11101110,
	0b10101010,
	0b10101010,
	//I
	0b11101110,
	0b01000100,
	0b01000100,
	0b01000100,
	0b11101110,
	//J
	0b00100010,
	0b00100010,
	0b00100010,
	0b10101010,
	0b11101110,
	//K
	0b10001000,
	0b10101010,
	0b11001100,
	0b11001100,
	0b10101010,
	//L
	0b10001000,
	0b10001000,
	0b10001000,
	0b10001000,
	0b11101110,
	//M
	0b10101010,
	0b11101110,
	0b11101110,
	0b10101010,
	0b10101010,
	//N
	0b00000000,
	0b11001100,
	0b10101010,
	0b10101010,
	0b10101010,
	//O
	0b01000100,
	0b10101010,
	0b10101010,
	0b10101010,
	0b01000100,
	//P
	0b11101110,
	0b10101010,
	0b11101110,
	0b10001000,
	0b10001000,
	//Q
	0b01000100,
	0b10101010,
	0b10101010,
	0b11101110,
	0b01100110,
	//R
	0b11101110,
	0b10101010,
	0b11001100,
	0b11101110,
	0b10101010,
	//S
	0b11101110,
	0b10001000,
	0b11101110,
	0b00100010,
	0b11101110,
	//T
	0b11101110,
	0b01000100,
	0b01000100,
	0b01000100,
	0b01000100, 
	//U
	0b10101010,
	0b10101010,
	0b10101010,
	0b10101010,
	0b11101110, 
	//V
	0b10101010,
	0b10101010,
	0b10101010,
	0b10101010,
	0b01000100,
	//W
	0b10101010,
	0b10101010,
	0b11101110,
	0b11101110,
	0b10101010,
	//X
	0b00000000,
	0b10101010,
	0b01000100,
	0b01000100,
	0b10101010,
	//Y
	0b10101010,
	0b10101010,
	0b01000100,
	0b01000100,
	0b01000100,
	//Z
	0b11101110,
	0b00100010,
	0b01000100,
	0b10001000,
	0b11101110,
	// Точка
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b10001000,
	// Тире
	0b00000000,
	0b00000000,
	0b11001100,
	0b00000000,
	0b00000000  };
	
//==================================
//Генератор синхроимульсов и растра
#pragma warn-
interrupt [TIM1_COMPA] void t1_cmpA(void)  
{
  //Старт горизонтального синхроимпульса
  PORTD = syncON;     
  //Номер линии для вывода на экран
  LineCount ++ ;   
  //Вертикальная синхронизация после строки 247
  if (LineCount==248)
  {
    syncON = 0b00100000;
    syncOFF = 0;
  }
  // 0.33v для синхронизации после линии  250
  if (LineCount==251)	
  {
    syncON = 0;
    syncOFF = 0b00100000;
  }
  //Следующий полукадр
  if (LineCount==263) 
  {
     LineCount = 1;
  }  
  
  delay_us(2); // 5 us пульсы
  //Конец синхроимпульса
  PORTD = syncOFF;   
  
  if (LineCount<ScreenBot && LineCount>=ScreenTop) 
    {
       
       //Расчет индекса байта для следующей линии
       //left-shift 4 would be individual lines
       // <<3 means line-double the pixels 
       //The 0xfff8 truncates the odd line bit
       //i=(LineCount-ScreenTop)<<3 & 0xfff8; //
       
       #asm
       push r16
       lds   r12, _LineCount
       lds   r13, _Linecount+1
       ldi   r16, 30
       sub  r12, r16 
       ldi  r16,0
       sbc  r13, r16 
       lsl  r12
       rol  r13
       lsl  r12
       rol  r13
       lsl  r12    
       rol  r13
       mov  r16,r12
       andi r16,0xf0
       mov  r12,r16
       pop r16 
       #endasm
        
       //Загрузка 16 регистров
       #asm
       push r14
       push r15
       push r16
       push r17
       push r18 
       push r19 
       push r26
       push r27
       
       ldi  r26,low(_screen)   ;Базовый адрес экрана
       ldi  r27,high(_screen)   
       add  r26,r12            ;Смещение экрана
       adc  r27,r13
       ld   r4,x+   	       ;Загрузка 16 registers and inc указателя
       ld   r5,x+
       ld   r6,x+  
       ld   r7,x+
       ld   r8,x+ 
       ld   r9,x+
       ld   r10,x+  
       ld   r11,x+
       ld   r12,x+ 
       ld   r13,x+
       ld   r14,x+  
       ld   r15,x+
       ld   r16,x+   
       ld   r17,x+  
       ld   r18,x+
       ld   r19,x 
       
       pop  r27
       pop  r26
       #endasm  

       delay_us(4);  //Задержка для центровки изображения
       
       //Выгрузка 16 байтов на экран
       #asm
       ;but first a macro to make the code shorter  
       ;the macro takes a register number as a parameter
       ;and dumps its bits serially to portD.6   
       ;the nop can be eliminated to make the display narrower
       .macro videobits ;regnum
        BST  @0,7
	IN   R30,0x12
	BLD  R30,6
	nop
	OUT  0x12,R30  
	
	BST  @0,6
	IN   R30,0x12
	BLD  R30,6
	nop
	OUT  0x12,R30 
	
	BST  @0,5
	IN   R30,0x12
	BLD  R30,6 
	nop
	OUT  0x12,R30 
	
	BST  @0,4
	IN   R30,0x12
	BLD  R30,6
	nop
	OUT  0x12,R30 
	
	BST  @0,3
	IN   R30,0x12
	BLD  R30,6
	nop
	OUT  0x12,R30 
	
	BST  @0,2
	IN   R30,0x12
	BLD  R30,6
	nop
	OUT  0x12,R30 
	
	BST  @0,1
	IN   R30,0x12
	BLD  R30,6 
	nop
	OUT  0x12,R30 
	
	BST  @0,0
	IN   R30,0x12
	BLD  R30,6
	nop
	OUT  0x12,R30 
       .endm     
        
	videobits r4 ;video line -- byte 1
        videobits r5 ;byte 2  
        videobits r6 ;byte 3
        videobits r7 ;byte 4
        videobits r8 ;byte 5
        videobits r9 ;byte 6
        videobits r10 ;byte 7
        videobits r11 ;byte 8 
        videobits r12 ;byte 9
        videobits r13 ;byte 10  
        videobits r14 ;byte 11
        videobits r15 ;byte 12
        videobits r16 ;byte 13
        videobits r17 ;byte 14
        videobits r18 ;byte 15
        videobits r19 ;byte 16
	clt   ;clear video after the last pixel on the line
	IN   R30,0x12
	BLD  R30,6
	OUT  0x12,R30
								
       pop r19
       pop r18
       pop r17 
       pop r16  
       pop r15
       pop r14
       #endasm
              
    }
  // Старт формирования программного ШИМ на PA2
//  PORTA.2=1;
  if(LightOn==1)
  {
          PORTA.2=1;
//          if(cPWM==0 || cPWM==1)  PORTA.2=1;
//          if(cPWM==2 || cPWM==3 || cPWM==4 || cPWM==5  || cPWM==6  || cPWM==7)  PORTA.2=0;
          cPWM++;
          if(cPWM==7)   cPWM=0;
  }
  else
  {
     cPWM=0;
     PORTA.2=0;
  }
  // Стоп формирования программного ШИМ на PA2
//  PORTA.2=0;
  
}
#pragma warn+

//==================================
//Отрисовка точки
//в x,y с цветом 1=белый 0=черный 2=инверсия
#pragma warn-
void video_pt(char x, char y, char c)
{
	
	#asm
	;  i=(x>>3) + ((int)y<<4) ;   the byte with the pixel in it

	push r16
	ldd r30,y+2 		;get x
	lsr r30
	lsr r30
	lsr r30     		;divide x by 8
	ldd r12,y+1 		;get y
       	lsl r12     		;mult y by 16
       	clr r13
	lsl r12
	rol r13
	lsl r12
	rol r13
	lsl r12
	rol r13
	add r12, r30     	;add in x/8
	
	;v2 = screen[i];   r5
        ;v3 = pos[x & 7];  r6
	;v4 = c            r7
	ldi r30,low(_screen)
	ldi r31,high(_screen)
	add r30, r12
	adc r31, r13
	ld r5,Z  		;get screen byte
	ldd r26,y+2 		;get x
	ldi r27,0
	andi r26,0x07           ;form x & 7 
	ldi r30,low(_pos*2)  
	ldi r31,high(_pos*2)
	add r30,r26
	adc r31,r27
	lpm r6,Z
	ld r16,y 		;get c 
       
       ;if (v4==1) screen[i] = v2 | v3 ; 
       ;if (v4==0) screen[i] = v2 & ~v3; 
       ;if (v4==2) screen[i] = v2 ^ v3 ; 
       
       cpi r16,1
       brne tst0
       or  r5,r6
       tst0:
       cpi r16,0
       brne tst2 
       com r6
       and r5,r6
       tst2:
       cpi r16,2
       brne writescrn
       eor r5,r6
       writescrn:
       	ldi r30,low(_screen)
	ldi r31,high(_screen)
	add r30, r12
	adc r31, r13
	st Z, r5        	;write the byte back to the screen
	
	pop r16
	#endasm
       
}
#pragma warn+



//==================================
// Запись маленького символа в переменную, эмелирующую видеопамять
// x-координаната должна быть поделена на 4 
// c индех в таблице символов
void video_smallchar(char x, char y, char c)  
{
	char mask;
	i=((int)x>>3) + ((int)y<<4) ;
	if (x == (x & 0xf8)) mask = 0x0f;     //f8
	else mask = 0xf0;
	
	screen[i] =    (screen[i] & mask) | (smallbitmap[c][0] & ~mask); 
   	screen[i+16] = (screen[i+16] & mask) | (smallbitmap[c][1] & ~mask);
        screen[i+32] = (screen[i+32] & mask) | (smallbitmap[c][2] & ~mask);
        screen[i+48] = (screen[i+48] & mask) | (smallbitmap[c][3] & ~mask);
   	screen[i+64] = (screen[i+64] & mask) | (smallbitmap[c][4] & ~mask); 
}

//==================================
// Загрузка строки прописных символов в видеопамять
// Координата х должна делиться на 4
void video_putsmalls(char x, char y, char *str)
{
	char i ;
	for (i=0; str[i]!=0; i++)
	{  
	   if(str[i]!=0x20 && str[i]!=0x3A && str[i]!=0x3D && str[i]!=0x2E && str[i]!=0x2D)
	   {
		if (str[i]>=0x30 && str[i]<=0x3a) 
			video_smallchar(x,y,str[i]-0x30);
		else video_smallchar(x,y,str[i]-0x40+12);
	    }
	   if(str[i]==0x20)     video_smallchar(x,y,12);                  // Пробел
	   if(str[i]==0x3A)     video_smallchar(x,y,10);                  // Двоеточие :
	   if(str[i]==0x3D)     video_smallchar(x,y,11);                  // Равно
	   if(str[i]==0x2E)     video_smallchar(x,y,39);                  // Точка
	   if(str[i]==0x2D)     video_smallchar(x,y,40);                  // Тире
	    x = x+4;	
	}
}
   




//==================================
// Загрузка прописного символа в видеопамять
// c индекс в таблице символов
void video_putchar(char x, char y, char c)  
{
    v7 = x;
    for (v6=0;v6<7;v6++) 
    {
        v1 = bitmap[c][v6]; 
        v8 = y+v6;
        video_pt(v7,   v8, (v1 & 0x80)==0x80);  
        video_pt(v7+1, v8, (v1 & 0x40)==0x40); 
        video_pt(v7+2, v8, (v1 & 0x20)==0x20);
        video_pt(v7+3, v8, (v1 & 0x10)==0x10);
        video_pt(v7+4, v8, (v1 & 0x08)==0x08);
    }
}

//==================================
// Подготовка к загрузке прописного символа в видеопамять
void video_puts(char x, char y, char *str)
{
	char i,j;
	for (i=0; str[i]!=0; i++)
	{
	   if(str[i]!=0x20 && str[i]!=0x2D && str[i]!=0x2E && str[i]!=0x5C && str[i]!=0x3A && str[i]!=0x2B)
	   {
//	        NextChar=str[i];
		if (str[i]>=0x30 && str[i]<=0x3a) 
			video_putchar(x,y,str[i]-0x30);
		else 
		{
		    if (str[i]>=0x61 && str[i]<=0x7a)
		    {
		       video_putchar(x,y,str[i]-55);    // маленькие буквы
		       j=str[i]-55;
		    }
		    else        video_putchar(x,y,str[i]-0x40+9); // большие буквы
		}
	   }
	   if(str[i]==0x20)     video_putchar(x,y,38);                  // Пробел
	   if(str[i]==0x2E)     video_putchar(x,y,39);                  // Точка
	   if(str[i]==0x2D)     video_putchar(x,y,40);                  // Тире
	   if(str[i]==0x5C)     video_putchar(x,y,36);                  // знак градуса
	   if(str[i]==0x3A)     video_putchar(x,y,37);                  // Двоеточие
	   if(str[i]==0x2B)     video_putchar(x,y,67);                  // Плюс
	   x = x+6;	
	}
}
      
    
//==================================
//Отрисовка линии с координатами  x1,y1 до x2,y2 с цветом 1=белый 0=черный 2=инверсный
void video_line(char x1, char y1, char x2, char y2, char c)
{
	int e;
	signed char dx,dy,j, temp;
	signed char s1,s2, xchange;
        signed char x,y;
        
	x = x1;
	y = y1;
	dx = cabs(x2-x1);
	dy = cabs(y2-y1);
	s1 = csign(x2-x1);
	s2 = csign(y2-y1);
	xchange = 0;   
	if (dy>dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		xchange = 1;
	}
	e = ((int)dy<<1) - dx;   
	for (j=0; j<=dx; j++)
	{
		video_pt(x,y,c) ; 
		if (e>=0)
		{
			if (xchange==1) x = x + s1;
			else y = y + s2;
			e = e - ((int)dx<<1);
		}
		if (xchange==1) y = y + s2;
		else x = x + s1;
		e = e + ((int)dy<<1);
	}
}

//==================================
//Возврат значения точки в x,y с цветом nonzero=белый 0=черный
char video_set(char x, char y)
{
	//The following construction 
  	//detects exactly one bit at the x,y location
	i=((int)x>>3) + ((int)y<<4) ;  
    return ( screen[i] & 1<<(7-(x & 0x7)));   	
}







//==================================
// set up the ports and timers
void main(void)
{
// unsigned int ADCVal[ADCChannels];
 int Tin=0,Tout=0,PowerADC=0,nTemp;             //Tin1=0,Tout1=0,
 char rtcHour=18,rtcMin=88,rtcSec=88,rtcDay=88,rtcMonth=88,rtcYear=88;
 char cText1[]="T OUT",cText2[]="T IN",cText3[]="POWER", cText4[]="FUEL", cText5[]="LIGHT";
 unsigned char Liters=0,i,j,AjustTime=0;



 
  //Инициализация портов
  DDRD = 0xf0;		//video out and switches
  //D.5 is sync:1000 ohm + diode to 75 ohm resistor
  //D.6 is video:330 ohm + diode to 75 ohm resistor

  PORTA=0b00000000;  // PA1-PA0 - вход для АЦП  PA7 PA6 PA5 выход светодиода
  DDRA= 0b11111100;

  PORTD=0b10000000;  // PA1-PA0 - вход для АЦП  PA7 PA6 PA5 выход светодиода
  DDRD= 0b01111111;

//  PORTB=0b00000000;  // PA3 PA4 - PullUp резисторы включить
//  DDRB= 0b00011000;

 
  
  #ifdef LCDDEBUG
     delay_us(20);
     lcd_init(16);
 
     lcd_gotoxy(0,0);
     lcd_putsf("Initializing...");
  #endif


  
  // ADC
  ADMUX=0b00000011;
  ADCSRA=0x87;


//  PORTA=0x00;  

// Старт АЦП для заполнения массива Fuel 
// до начала отрисовки и вычисления среднего значения
  ADMUX=0b00000000;  //ADC на PA0
  ADCSRA.6 = 1;   // Начать ADC

  

  
  
  //Инициализация констант синхронизации
  LineCount = 1;
  syncON = 0b00000000;
  syncOFF = 0b00100000;  
  ADCType=0;

  //Print "DIEHARD" 
//  video_puts(13,3,cu1);
//  Print "31 01 2007" 
//  video_puts(65,3,cu2); 
//  video_puts(55,45,cu3);

  // cText1[]  T OUT
  video_puts(13,15,cText1); 
  sprintf(ts,"\\");
  video_puts(103,15,ts); 
  // cText2[]  T IN
  video_puts(13,30,cText2); 
  video_puts(103,30,ts); 
  // cText3[]  POWER
  video_puts(13,45,cText3); 
  sprintf(ts,"V");
  video_puts(103,45,ts); 
  // cText3[]  ENGINE
  video_puts(13,60,cText4); 
  sprintf(ts,"L");
  video_puts(103,60,ts); 

  // cText5[]  LIGHT
  video_puts(13,75,cText5); 
  sprintf(ts,"OFF");
  video_puts(90,75,ts); 

  
  //side lines 
  #define width 126
//  video_line(0,0,0,99,1);
//  video_line(width,0,width,99,1);
  
  //Верхняя линия и нижняя линия
  video_line(0,6,width,6,1);    // Верх
  video_line(0,92,width,92,1);  // Низ
//  video_line(0,99,width,99,1);  // Низ
//  video_line(0,11,width,11,1);
    
  //Инициализация программного таймера
  t=0;
  time=0;  
  
  //Инициализация анимации
  x = 64; 
  y=50;
  vx=1;
  vy=1;
  //video_pt(x,y,1);   
  
  //Инициализация звука
  note = 0;
  musicT = 0;
  //use OC0 (pin B.3) for music  
  DDRB.3 = 1 ;     

//  delay_ms(100);
  PORTA=0xFF;
  delay_ms(500);

//goto loop;


  // Инициализация RTC
  rtc_init(0,0,0);

   // Инициализация I2C 
   i2c_init();
   PORTA.5=0;

   // DS1621 Thermometer/Thermostat initialization
   // tlow: 50°C
   // thigh: 70°C
   // Tout polarity: 0
#ifndef LCDDEBUG                // В рабочей версии включить нулевой датчик
   ds1621_init(0,50,70,0);      // нулевой адрес устройства
#endif
   PORTA.4=0;
   delay_ms(200);

   ds1621_init(1,50,70,0);       // первый адрес устройства
   PORTA.3=0;
   delay_ms(200);


  // Инициализация RTC
  rtc_init(0,0,0);

//  PORTA.4=0;
//  rtc_set_date(17, 05, 07);
//  rtc_set_time(14, 42, 00);
  rtc_get_date(&rtcDay,&rtcMonth,&rtcYear);
  rtc_get_time(&rtcHour,&rtcMin,&rtcSec);
  if(rtcSec>59)
  {
     rtc_set_time(rtcHour,rtcMin,00);
  }


// АЦП для заполнения массива Fuel окончено
// заполнение массива aFuel полученным значением
  if((ADCSRA & (1 << 4))!=0)            // ADC окончено
  {
      Fuel=ADCW;
      aFuel[0]=ADCW;
      for(i=0;i<LITERSADC;i++)   aFuel[i]=Fuel;
   }


  PORTA=0xFF;
  DDRA= 0b11111100;


  #ifdef LCDDEBUG
     lcd_clear();
     lcd_gotoxy(0,0);

     sprintf(ts,"Power:");
     lcd_puts(ts);
     lcd_gotoxy(0,1);

     sprintf(ts,"Fuel :");
     lcd_puts(ts);
     delay_ms(500);

     lcd_gotoxy(7,0);
     sprintf(ts,"%4d ",nTemp);
     lcd_puts(ts);
     delay_ms(500);

     lcd_gotoxy(7,1);
     sprintf(ts,"%4d ",Fuel);
     lcd_puts(ts);
     delay_ms(500);
   #endif


//loop:
  EEYear =EEPromRead(0x00);
  EEMonth=EEPromRead(0x01);
  EEDay  =EEPromRead(0x02);
  EEHour =EEPromRead(0x03);
  EEMin  =EEPromRead(0x04);

  TempDay=EEPromRead(0x05);
  Hour   =EEPromRead(0x06);
  Min    =EEPromRead(0x07);
  Sec    =EEPromRead(0x08);
  
  YearSummer=EEPromRead(0x09);
  YearWinter=EEPromRead(0x0A);
  if(YearSummer==0xFF)
  {
        YearSummer=0;
        EEPromWrite(0x09,0);
  }

  if(YearWinter==0xFF)
  {
        YearWinter=0;
        EEPromWrite(0x0A,0);
  }
  
  if(EEYear==0xFF || EEMonth==0xFF || EEDay==0xFF || EEHour==0xFF || EEMin==0xFF || TempDay==0xFF || Hour==0xFF || Min==0xFF || Sec==0xFF )
  {
     EEYear =0;
     EEMonth=0;
     EEDay  =0;
     EEHour =0;
     EEMin  =0;
     TempDay=0;
     Hour=0;
     Min =0;
     Sec =0;



     EEPromWrite(0,0);
     EEPromWrite(1,0);
     EEPromWrite(2,0);
     EEPromWrite(3,0);
     EEPromWrite(4,0);
     EEPromWrite(5,0);
     EEPromWrite(6,0);
     EEPromWrite(7,0);
     EEPromWrite(8,0);
  }



  //Timer 1 для генерации синхронизации
  OCR1A = lineTime; 	//One NTSC line
  TCCR1B = 9; 		//full speed; clear-on-match
  TCCR1A = 0x00;	//turn off pwm and oc lines
  TIMSK = 0x10;		//enable interrupt T1 cmp 





  //Разрешение спящего режима
  MCUCR = 0b10000000;
  #asm ("sei");
  

  //The following loop executes once/video line during lines
  //1-230, then does all of the frame-end processing
  while(1)
  {
    #asm ("sleep"); 


    //Перерисовка экрана осуществляется в следующем порядке
    // 60 Строк x 63.5 uSec/строку x 8 циклов/uSec 
    if (LineCount==231)
    {
// Старт ADC
           if(t==0 || t==30)
           {
                  // Для старта АЦП    ADCSRA.6=1
                  // При окончании АЦП ADCSRA.6 станет =0
                  // Окночание АЦП показывает установленный бит 4 ADIF
                   ADMUX=0b00000001;  //ADC на PA1
                   ADCSRA.6 = 1;   // Начать ADC
                   for(i=49;i>0;i--)    cU[i]=cU[i-1];
           }


           if(t==15 || t==45)
           {
                   ADMUX=0b00000000;  //ADC на PA0
                   ADCSRA.6 = 1;   // Начать ADC
           }

           
           

           if( t==10)   sprintf(ts,"\\");
           
// Отрисовка T Out
           if( t==11)
           {
              i=abs(Tout%10);
              while(i>9)        i=i/10;
              sprintf(ts2,"%3d.%1d ",Tout/10,i);

              video_puts(70,15,ts2); 
              video_puts(103,15,ts); 


            }

// Отрисовка T In
           if( t==12)
           {
              i=abs(Tin%10);
              while(i>9)        i=i/10;
              sprintf(ts2,"%3d.%1d ",Tin/10,i);

              video_puts(70,30,ts2); 
              video_puts(103,30,ts); 
           }   


// Отрисовка Power           
           if( t==13 || t==31 )
           {

//                 PowerADC=(PowerADC/50.169492)*10;
                 PowerADC=(PowerADC/44.862745)*10;
//                 PowerADC=((PowerADC*11,79)/566)*10;
                 sprintf(ts,"%3d.%1d",PowerADC/10,PowerADC%10);
                 video_puts(70,45,ts);
                 cU[0]=PowerADC;
                 
                 dU=0;
                 for(i=0;i<50;i++)    dU=dU+cU[i];
                 dU=dU/50;
                 
           }
           
           if(t==14)
           {
               if(PIND.7==1)    // Включены габариты PWM Off
               {
                                sprintf(ts,"- -");
                                video_puts(90,75,ts); 
                                LightOn=0;
               }
               else             // Выключены габариты.
               {
                       if(dU>=USTART)  // Напряжение больше 13.2v PWM On
                       {
                                sprintf(ts,"ON ");
                                video_puts(90,75,ts); 
                                LightOn=1;
                       }
                       else         // Напряжение меньше 13v PWM Off
                       {
                                sprintf(ts,"OFF");
                                video_puts(90,75,ts); 
                                LightOn=0;
                       }
               }
           }

/*           if( t==14 || t==32 )
           {
                 sprintf(ts,"%4d",nTemp);
                 video_putsmalls(12,84,ts);
           }
*/

// Сдвиг массива Fuel с подготовкой первого элемента к принятию ADC
           if(t==15 || t==45)
           {
               j=LITERSADC-1;
               for(i=j;i>0;i--)   aFuel[i]=aFuel[i-1];
               aFuel[0]=0;
               
           }
           
  

// Массив aFuel[0...LITERS] результат ADC по Fuel
           if(t==16 || t==46)
           {  
              Fuel=0;
              for(i=0;i<LITERSADC;i++)       Fuel=Fuel+aFuel[i];
              Fuel=Fuel/LITERSADC;

              Liters=0;                           
              j=0;
              for(i=0;i<LITERS;i++)
              {                 
                  if(Fuel<=aFuelValue[i][1])
                  {
                     j=i;
                     Liters=aFuelValue[i][0];
                  }
              }
              
           }
// Отрисовка FUEL
           if(t==17 || t==47)
           {
             if(Fuel<50)       sprintf(ts," - - ");
             else              sprintf(ts,"%5d",Liters);
              video_puts(70,60,ts); 
           }
// Отрисовка Fuel
           if(t==18)
           {
              sprintf(ts,"%4d",aFuel[0]);
              video_putsmalls(112,0,ts); 
           }
           

           if(t==6)
           {  
              sprintf(ts,"%02d-%02d-%02d",EEDay,EEMonth,EEYear);
              video_putsmalls(52,94,ts); 
           }

           if(t==7)
           {  
              sprintf(ts,"%02d:%02d",EEHour,EEMin);
              video_putsmalls(12,94,ts); 
           }

           
// Чтение RTC
           if(t==0)
           {
                          rtc_get_time(&rtcHour,&rtcMin,&rtcSec);
                          if(rtcSec>59)                                 // Часы остановлены
                          {
                                rtc_set_time(rtcHour,rtcMin,00);        // Запускаю часы
                          }
           }


// Отрисовка RTC
           if(t==1)
           {  
              sprintf(ts,"%02d:%02d.%02d",rtcHour,rtcMin,rtcSec);
              video_putsmalls(12,0,ts);
           }


           if(Sec==0 || Sec==5 || Sec==10 || Sec==15 || Sec==20 || Sec==25 || Sec==30 || Sec==35 || Sec==40 || Sec==45 || Sec==50 || Sec==55)
           {
// Чтение датчика температуры   T in
             if(t==2)    
             {  
               Tin=ds1621_temperature_10(0);
             }
// Чтение датчика температуры   T out
             if(t==3)
             {  
                Tout=ds1621_temperature_10(1);
             }
           }
           


           #ifdef LCDDEBUG
              if(t==6 || t==36)
              {  

                   lcd_clear();
                   sprintf(ts,"Power: %4d",nTemp);
                   lcd_puts(ts);
              }
           #endif


           if(t==4)                 rtc_get_date(&rtcDay,&rtcMonth,&rtcYear);


           if(t==30)
           {  
              sprintf(ts,"%02d %02d",rtcHour,rtcMin);
              video_putsmalls(12,0,ts);
           }
           if(t==51)
           {  
              sprintf(ts,"%02d-%02d-%02d",rtcDay,rtcMonth,rtcYear);
              video_putsmalls(52,0,ts);
           }

           if(t==57 && AjustTime==0 )                               // Переход на летнее время
           {  
              if(YearSummer!=rtcYear)
              {
                      if( rtcDay>=30 && rtcMonth==3 && rtcYear==8 )     AjustTime=1;
                      if( rtcMonth>3 && rtcYear==8 )                    AjustTime=1;
                      if( rtcDay>=29 && rtcMonth==3 && rtcYear==9 )     AjustTime=1;
                      if( rtcMonth>3 && rtcYear==9 )                    AjustTime=1;
                      if( rtcDay>=28 && rtcMonth==3 && rtcYear==10 )    AjustTime=1;
                      if( rtcMonth>3 && rtcYear==10 )                   AjustTime=1;
                      if( rtcDay>=27 && rtcMonth==3 && rtcYear==11 )    AjustTime=1;
                      if( rtcMonth>3 && rtcYear==11 )                   AjustTime=1;
                      if( rtcDay>=25 && rtcMonth==3 && rtcYear==12 )    AjustTime=1;
                      if( rtcMonth>3 && rtcYear==12 )                   AjustTime=1;
                      if( rtcDay>=31 && rtcMonth==3 && rtcYear==13 )    AjustTime=1;
                      if( rtcMonth>3 && rtcYear==13 )                   AjustTime=1;
                      if( rtcDay>=30 && rtcMonth==3 && rtcYear==14 )    AjustTime=1;
                      if( rtcMonth>3 && rtcYear==14 )                   AjustTime=1;
                      if( rtcDay>=29 && rtcMonth==3 && rtcYear==15 )    AjustTime=1;
                      if( rtcMonth>3 && rtcYear==15 )                   AjustTime=1;
              }
           }
           if(t==58 && AjustTime==0 )                               // Переход на зимнее время
           {  
              if(YearWinter!=rtcYear)
              {
                      if( rtcDay>=25 && rtcMonth==10 && rtcYear==15 )    AjustTime=2;
                      if( rtcMonth>10 && rtcYear==15 )                   AjustTime=2;
                      if( rtcDay>=26 && rtcMonth==10 && rtcYear==14 )    AjustTime=2;
                      if( rtcMonth>10 && rtcYear==14 )                   AjustTime=2;
                      if( rtcDay>=27 && rtcMonth==10 && rtcYear==13 )    AjustTime=2;
                      if( rtcMonth>10 && rtcYear==13 )                   AjustTime=2;
                      if( rtcDay>=28 && rtcMonth==10 && rtcYear==12 )    AjustTime=2;
                      if( rtcMonth>10 && rtcYear==12 )                   AjustTime=2;
                      if( rtcDay>=30 && rtcMonth==10 && rtcYear==11 )    AjustTime=2;
                      if( rtcMonth>10 && rtcYear==11 )                   AjustTime=2;
                      if( rtcDay>=31 && rtcMonth==10 && rtcYear==10 )    AjustTime=2;
                      if( rtcMonth>10 && rtcYear==10 )                   AjustTime=2;
                      if( rtcDay>=25 && rtcMonth==10 && rtcYear==9 )     AjustTime=2;
                      if( rtcMonth>10 && rtcYear==9 )                    AjustTime=2;
                      if( rtcDay>=26 && rtcMonth==10 && rtcYear==8 )     AjustTime=2;
                      if( rtcMonth>10 && rtcYear==8 )                    AjustTime=2;
                      if( rtcDay>=28 && rtcMonth==10 && rtcYear==7 )     AjustTime=2;
                      if( rtcMonth>10 && rtcYear==7 )                    AjustTime=2;
              }
           }
           if(t==39)     // Перевод часов на зимнее/летнее время время
           {
                if(AjustTime==1)
                {
                  if(rtcHour>=2 )                rtc_set_time(rtcHour+1, rtcMin, rtcSec);
                  AjustTime=AjustTime+10;
                }
                if(AjustTime==2)
                {
                  if(rtcHour>=2 )                rtc_set_time(rtcHour-1, rtcMin, rtcSec);
                  AjustTime=AjustTime+10;
                }
                
           }
           if(t==41)     // Перевод часов на зимнее/летнее время время (Запись обработанного года)
           {
                if(AjustTime==11)
                {
                        YearSummer=rtcYear;
                        EEPromWrite(0x09,rtcYear);
                }

                if(AjustTime==12)
                {
                        YearWinter=rtcYear;
                        EEPromWrite(0x0A,rtcYear);
                }
                AjustTime=0;
           }
           

// Проверка окончания ADC
           if(t==0 || t==30)
           {
                if((ADCSRA & (1 << 4))!=0)            // ADC окончен
                {
                   PowerADC=ADCW;
                   if(PowerADC>42)      PowerADC=PowerADC-42;
                   else                 PowerADC=0;
                   nTemp=PowerADC;

                 }  
           }
           if(t==15 || t==45)
           {
                if((ADCSRA & (1 << 4))!=0)            // ADC окончено
                {
                   Fuel=ADCW;
                   aFuel[0]=ADCW;
                }
           }

           if(t==9)
           {
              #ifdef LCDDEBUG
                 sprintf(ts,"%02d-%02d",TempDay,rtcDay);
                 video_putsmalls(88,0,ts); 
              #endif              
           }
           
           if( t==41 )
           {
                if( (TempDay!=rtcDay))
                {
                        Min=0;
                        Hour=0;
                        EEPromWrite(6,Hour);
                }
           }
           if( t==42 )
           {
                if( (TempDay!=rtcDay))
                {
                        Min=0;
                        Hour=0;
                        EEPromWrite(7,Min);
                }
           }
           if( t==43 )
           {
                if( (TempDay!=rtcDay))
                {
                        Min=0;
                        Hour=0;
                        TempDay=rtcDay;
                        EEPromWrite(5,rtcDay);
                }
           }


           if( (dU>=USTART) || (PowerADC>=USTART) )
           {  
             if(Min==0||Min==5||Min==10||Min==15||Min==20||Min==25||Min==30||Min==35||Min==40||Min==45||Min==50||Min==55)
             {
                if  ( t==44&&Sec==0 )                EEPromWrite(8,Sec);
                if  ( t==46&&Sec==0 )                EEPromWrite(6,Hour);
                if  ( t==47&&Sec==0 )                EEPromWrite(7,Min);


                if  ( t==48&&Sec==0 )                EEPromWrite(0,EEYear);
                if  ( t==52&&Sec==0 )                EEPromWrite(1,EEMonth);
                if  ( t==53&&Sec==0 )                EEPromWrite(2,EEDay);
                if  ( t==54&&Sec==0 )                EEPromWrite(3,EEHour);
                if  ( t==56&&Sec==0 )                EEPromWrite(4,EEMin);
             }
           }
         

        // Прошла секунда. Расчет времени (часов и минут)
        if (++t>59)
        {
           t=0;
           time = time + 1;

           if( (dU>=USTART) || (PowerADC>=USTART) )
           {  
                   Sec=Sec+1;
                   if(Sec>59)
                   { 
                        Sec=0; 
                        Min=Min+1;
                   }
                   
                   
                   if(Min>59)
                   { 
                        Min=0; 
                        Hour=Hour+1;
                   }
           
           
                   if(Sec==0)
                   {
                        EEMin++;
                        if(EEMin>59)
                        {
                                EEMin=0;
                                EEHour++;
                                if(EEHour>23)
                                {
                                        EEHour=0;
                                        EEDay++;
                                        if(EEDay>31)
                                        {
                                                EEDay=0;
                                                EEMonth++;
                                                if(EEMonth>12)
                                                {
                                                        EEMonth=0;
                                                        EEYear++;
                                                }
                                        }
                                }
                        }
                   }
           }

           sprintf(ts,"%02d:%02d:%02d",Hour,Min,Sec);
           video_putsmalls(92,94,ts);
        }
        
     }  // LineCount==231

  }  // while (1)
}  // main




void EEPromWrite(unsigned int uiAddress, unsigned char ucData)
{
 while(EECR & (1<<EEWE));
 EEAR=uiAddress;
 EEDR=ucData;
 EECR |=(1<<EEMWE);
 EECR|=(1<<EEWE);
}

unsigned char EEPromRead(unsigned int uiAddress)
{
  while(EECR & (1<<EEWE));
  EEAR=uiAddress;
  EECR |=(1<<EERE);
  return EEDR;
}
