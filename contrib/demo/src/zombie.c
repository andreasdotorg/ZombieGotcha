#include "term.h"

#include "zsprites.h"
#include "fbuffer.h"

#include "zgame.h"

void zombiesetup51(){
  // Set the system clock source to HS XOSC and max CPU speed,
  // ref. [clk]=>[clk_xosc.c]
  SLEEP &= ~SLEEP_OSC_PD;
  while( !(SLEEP & SLEEP_XOSC_S) );
  CLKCON = (CLKCON & ~(CLKCON_CLKSPD | CLKCON_OSC)) | CLKSPD_DIV_1;
  while (CLKCON & CLKCON_OSC);
  SLEEP |= SLEEP_OSC_PD;
  
  //Taken from zombietextplash()
  //Disable WDT
  IEN2&=~IEN2_WDTIE;
  IEN0&=~EA;
  
  xtalClock(); // fastest speed
  setIOPorts();
  configureSPI();
  LCDReset();
  setDisplayStart(0);
  
}

//Draw the local and remote sprites.
void zombiedraw(){
  if(localpet.drawable)
    fb_bitblt(localpet.sprite,
	      localpet.x,localpet.y,
	      localpet.frame);
  if(remotepet.drawable)
    fb_bitblt(remotepet.sprite,
	      remotepet.x,remotepet.y,
	      remotepet.frame);
}



Pet localpet, remotepet;
u8 framectr=0;

//! Initializes a new pet.
void zombieinit(Pet *pet){
  pet->type=HUMAN;
  pet->gender=FEMALE;
  pet->health=5;
  pet->sprite=(__xdata u8*) zGirlPix;
  strncpy(pet->name,"Tammy",7);
}

//! Creates a pet, zombie or girl.
void zombiecreate(Pet *pet){
  zombieinit(pet);
  
}

//! Render the local pet as the game idles.
void zombieidle(){
  fb_blank();
  
  fb_bitblt((__xdata u8*) localpet.sprite,32,32,(framectr>>2)%2);
  
  //Draw the health bar.
  if((framectr)&1) 
    fb_horizline(0,0,40);
  else
    fb_horizline(0,0,localpet.health<<2);
  
  
  fb_flush();
  
  //FIXME move this to the framebuffer.
  /*
  SSN=LOW;
  drawstr(0,0,localpet.name);
  SSN=HIGH;
  sleepMillis(500);
  */
}

//! ZombieGotcha main loop.
void zombiemain(){
  zombieidle();
}

//! ZombieGotcha entry point.
void zombiegotcha(){
  zombiesetup51();
  
  zombiesplash();
  zombiecreate(&localpet);
  
  while(1){
    framectr++;
    zombiemain();
  }
}
