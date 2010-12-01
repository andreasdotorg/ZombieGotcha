#include "zgame.h"


#include "zsprites.h"
#include "fbuffer.h"
#include "term.h"

//! ZombieGotcha Splash Screen
void zombiesplash(){
  u16 girlx, titley, i;


  girlx=0;
  titley=0;
    
  //Girl runs to Zombie.
  while(girlx<80){
    //sleepMillis(15);
    fb_blank();
      
    fb_bitblt((__xdata u8*) zTitleText,16,0,0);
    fb_bitblt((__xdata u8*) zGirlPix,girlx,32,girlx);
    fb_bitblt((__xdata u8*) zZombiePix,96,32,girlx/3);
    girlx+=4;
      
    fb_flush();
  }
  
  //Zombie dies.
  for(i=0;i<4;i++){
    //sleepMillis(15);
    fb_blank();
      
    fb_bitblt((__xdata u8*) zTitleText,16,titley,0);
    fb_bitblt((__xdata u8*) zGirlPix,girlx,32,2);
    fb_bitblt((__xdata u8*) zZombieDeadPix,96,32,i>>1);
    
      
    fb_flush();
  }
  
    
  //Zombie disappears, title lowers."
  while(titley<24){
    //sleepMillis(15);
    fb_blank();
      
    fb_bitblt((__xdata u8*) zTitleText,16,titley++,0);
    fb_bitblt((__xdata u8*) zGirlPix,girlx,32,(girlx/3)%2);
    //fb_bitblt((__xdata u8*) zZombiePix,96,32,girlx/3);
    girlx+=1;
      
    fb_flush();
  }
    
  SSN=LOW;
  drawstr(0,0,"Travis Goodspeed");
  drawstr(1,0,"Eli Skipp");
  drawstr(7,0,"Press SPACE.");
  SSN=HIGH;
    
  while(keyscan()!=' ');

}

