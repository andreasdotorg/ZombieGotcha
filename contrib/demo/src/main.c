


#include "term.h"


//globals

void fail(char *msg){
  u8 i=0;
  
  LED_RED=LOW;
  SSN = LOW;
  erasescreen();
  drawstr(1,2,"FATAL ERROR:");
  drawstr(2,2,msg);
  SSN = HIGH;
  for(i=0;i<5;i++)
    sleepMillis(1000);
  //reset();
}



void main(void) {
  //Disable WDT
  IEN2&=~IEN2_WDTIE;
  IEN0&=~EA;
  
  xtalClock(); // fastest speed
  setIOPorts();
  configureSPI();
  LCDReset();
  setDisplayStart(0);
  
  //Start the game right-off.
  zombiegotcha();
}
