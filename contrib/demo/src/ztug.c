#include "term.h"

#include "ztug.h"
#include "zombie.h"
#include "fbuffer.h"

__xdata u16 lscore, rscore;

//! Draw the tug of war game.
void zombietugdraw(){
  //Situate the pets.
  localpet.x=10;
  localpet.y=32;
  remotepet.x=80;
  remotepet.y=32;
  localpet.drawable=1;
  remotepet.drawable=1;
  
}

//! Zombie Tug of War
void zombietug(){
  
}
