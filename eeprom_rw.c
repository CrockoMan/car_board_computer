//#include <m8_128.h>



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


/*






                   if(Sec == 0) 
                   {
                      EETime[3]=EETime[3]+1;
                      if(EETime[3]>59)
                      {
                          EETime[3]=0;
                          EETime[2]=EETime[2]+1;
                          if(EETime[2]>23)
                          {
                             EETime[2]=0;
                             if(EETime[1]!=0xFF)         EETime[1]=EETime[1]+1;
                             else                   {    EETime[1]=0;   EETime[0]=EETime[0]+1;  }
                          }
                      }
                   
                      EEDay =EETime[1];
                      EEHour=EETime[2];
                      EEMin =EETime[3];
                      
                      EEPromWrite(0,EETime[0]);
                      EEPromWrite(1,EETime[1]);
                      EEPromWrite(2,EETime[2]);
                      EEPromWrite(3,EETime[3]);
                   }
*/
