#include "term.h"

void setIOPorts() {
  //No need to set PERCFG or P2DIR as default values on reset are fine
  P0SEL |= (BIT5 | BIT3 ); // set SCK and MOSI as peripheral outputs
  P0DIR |= BIT4 | BIT2; // set SSN and A0 as outputs
  P1DIR |= BIT1; // set LCDRst as output
  P2DIR = BIT3 | BIT4; // set LEDs  as outputs
  //LED_GREEN = LOW; // Turn the Green LED on (LEDs driven by reverse logic: 0 is ON)
}

void configureSPI() {
  U0CSR = 0;  //Set SPI Master operation
  U0BAUD =  SPI_BAUD_M; // set Mantissa
  U0GCR = U0GCR_ORDER | SPI_BAUD_E; // set clock on 1st edge, -ve clock polarity, MSB first, and exponent
}
void tx(unsigned char ch) {
  U0DBUF = ch;
  while(!(U0CSR & U0CSR_TX_BYTE)); // wait for byte to be transmitted
  U0CSR &= ~U0CSR_TX_BYTE;         // Clear transmit byte status
}

void txData(unsigned char ch) {
  A0 = HIGH;
  tx(ch);
}

void txCtl(unsigned char ch){
  A0 = LOW;
  tx(ch);
}

void LCDReset(void) {
  LCDRst = LOW; // hold down the RESET line to reset the display
  sleepMillis(1);
  LCDRst = HIGH;
  SSN = LOW;
  // send the initialisation commands to the LCD display
  txCtl(0xe2); // RESET cmd
  txCtl(0x24); // set internal resistor ratio
  txCtl(0x81); // set Vol Control
  txCtl(0x60); // set Vol Control - ctd
  txCtl(0xe6); // ?? -- don't know what this command is
  txCtl(0x00); // ?? -- don't know what this command is
  txCtl(0x2f); // set internal PSU operating mode
  txCtl(0xa1); // LCD bias set
  txCtl(0xaf); // Display ON
  txCtl(0xa4); // Normal (not all pixels) mode.
  setNormalReverse(0); //Non-inverted screen.
  SSN = HIGH;
}

void LCDPowerSave() { // not tested yet; taken from spi trace
  txCtl(0xac); // static indicator off cmd
  txCtl(0xae); // LCD off
  txCtl(0xa5); // Display all Points on cmd = Power Save when following LCD off
}

void setCursor(unsigned char row, unsigned char col) {
  txCtl(0xb0 + row); // set cursor row
  txCtl(0x00 + (col & 0x0f)); // set cursor col low
  txCtl(0x10 + ( (col>>4) & 0x0f)); // set cursor col high
}

void setDisplayStart(unsigned char start) {
  txCtl(0x40 | (start & 0x3f)); // set Display start address
}

void setNormalReverse(unsigned char normal) {  // 0 = Normal, 1 = Reverse
  txCtl(0xa6 | (normal & 0x01) );
}

void eraserow(u8 row){  
  u8 i;//column
  setCursor(row, 0);
  for (i=0; i<132; i++) { // clear every column on the line
    txData(0x00);
  };
}

void erasescreen(){
  u8 row;
  for(row=0;row<9;row++)
    eraserow(row);
}
  
void drawstr(u8 row, u8 col, char *str){
  u8 len=strlen(str);
  
  if (row >8) return;
  setCursor(row, col*6);
  
  while (len--)
    putch(*(str++));
}
void drawint(u8 row, u8 col, u16 val){
  u8 len=5;
  //FIXME prints backward.
  if (row >8) return;
  setCursor(row, col*6);
  
  while (len--){
    putch('0'+(val%10));
    val/=10;
  }
}
void drawhex(u8 row, u8 col, u16 val){
  u8 len=4;
  u16 nibble;
  if (row >8) return;
  setCursor(row, col*6);
  
  while (len--){
    nibble=(val&0xF000)>>12;
    if(nibble<10)
      putch('0'+nibble);
    else
      putch('A'+nibble-0xA);
    val<<=4;
  }
}
