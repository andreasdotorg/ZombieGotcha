
#include "term.h"

//! Sleep for some milliseconds.
void sleepMillis(int ms) {
  int j;
  while (--ms > 0) { 
    for (j=0; j<1200;j++); // about 1 millisecond
  };
}

//! Set system clock source to 26 Mhz
void xtalClock() { 
  SLEEP &= ~SLEEP_OSC_PD; // Turn both high speed oscillators on
  while( !(SLEEP & SLEEP_XOSC_S) ); // Wait until xtal oscillator is stable
  CLKCON = (CLKCON & ~(CLKCON_CLKSPD | CLKCON_OSC)) | CLKSPD_DIV_1; // Select xtal osc, 26 MHz
  while (CLKCON & CLKCON_OSC); // Wait for change to take effect
  SLEEP |= SLEEP_OSC_PD; // Turn off the other high speed oscillator (the RC osc)
}
